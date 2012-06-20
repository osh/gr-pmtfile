#include <pmtfile.h>
#include <map>
#include <stdio.h>


// open an existing pmt file
pmtfile::pmtfile(std::string filename) : fs(filename.c_str(), std::ios_base::in|std::ios::binary), sb(fs.rdbuf()), d_filename(filename){
    // read tags in file 
    // make sure we have a d_itemsize
    stat( d_filename.c_str(), &filestatus );
    read_header();
    if(!pmt::pmt_is_pair(header)){
        printf("not a valid pmt file.\n");
        exit(-1);
    }
    pmt::pmt_t ident = pmt::pmt_car(header);
    if(!pmt::pmt_is_integer(ident)){
        printf("not a valid pmt file.\n");
        exit(-1);
    }
    if( pmt_to_long(ident) != 0x124D10FF ){
        printf("not a valid pmt file.\n");
        exit(-1);
    }
    // FILE type ok!

    itemsize = -1; 

    // extract all the tags from the file
    pmt::pmt_t taglist = pmt::pmt_car(pmt::pmt_cdr(header));
    pmt::pmt_t iter = taglist;
    while( pmt::pmt_is_pair( iter ) ){

        pmt::pmt_t car = pmt::pmt_car(iter);
        pmt::pmt_t cdr = pmt::pmt_cdr(iter);

        //pmt::pmt_t sampletime = pmt::pmt_car(car);
        pmt::pmt_t kv = pmt::pmt_cdr(car);
        
        pmt::pmt_t k = pmt::pmt_car(kv);
        pmt::pmt_t v = pmt::pmt_cdr(kv);
    
        if(pmt::pmt_symbol_to_string(k).compare("format")==0){
            const pmtfile::datatype_t types[] = {CF64, RF32, RI32, RI16, RI8, CI32};
            for(int i=0; i<num_datatypes; i++){
                if(pmt::pmt_symbol_to_string(v).compare(datatype_str(types[i]))==0){
                    itemsize = datatype_size(types[i]);
                }
            }
        }

        iter = cdr;   
    
        }

    if(itemsize == -1){
        printf("file did not specify a sample format!\n");
        exit(-1);
    }

}   

// open a new pmt file
pmtfile::pmtfile(std::string filename, datatype_t datatype) : fs(filename.c_str(), std::ios_base::out|std::ios::binary){
    // set datatype tag to be written with header
    itemsize = datatype_size(datatype);
    header = pmt::PMT_NIL;
}

void pmtfile::set_header(pmt::pmt_t hdr){
    header = pmt::pmt_list1( pmt::pmt_from_long( 0x124D10FF ) );
    header = pmt::pmt_list_add( header, hdr );
}

void pmtfile::write_header(){
    // make sure the header has been defined
    if(pmt::pmt_is_null(header)){
        printf("Header is undefined! not writing header!\n");
        return;
        }

    // serialize the header structure for writing
    std::stringbuf sb;
    pmt::pmt_serialize(header, sb);
 
    // write header to output 
    fs << sb.str();
}

void pmtfile::print_header(){
    pmt::pmt_t taglist = pmt::pmt_car(pmt::pmt_cdr(header));
    pmt::pmt_t iter = taglist;
    while( pmt::pmt_is_pair( iter ) ){

        pmt::pmt_t car = pmt::pmt_car(iter);
        pmt::pmt_t cdr = pmt::pmt_cdr(iter);

        //pmt::pmt_t sampletime = pmt::pmt_car(car);
        pmt::pmt_t kv = pmt::pmt_cdr(car);

        pmt::pmt_t k = pmt::pmt_car(kv);
        pmt::pmt_t v = pmt::pmt_cdr(kv);


        std::string ks( pmt::pmt_write_string( k ) );
        std::string vs( pmt::pmt_write_string( v ) );

        std::cout << ks << ":   \t" << vs << "\n";

        iter = cdr;

        }

}

void pmtfile::print_fileinfo(){
    std::cout << "--------------------------------------\n";
    std::cout << "Showing info for " << d_filename << "\n";
    std::cout << "--------------------------------------\n";
    std::cout << "File size: \t" << filestatus.st_size/1e6 << " MB\n";

    // this assumes this is called with the pointer at the beginning of the data
    std::cout << "Itemsize: \t" << itemsize << " bytes\n";
    int num_samp =  (filestatus.st_size - fs.tellg())/itemsize;
    std::cout << "Num Samples: \t" << num_samp << "\n";
    std::cout << "--------------------------------------\n";
       
}

void pmtfile::read_header(){
    fs.seekg(0);       
    header = pmt::pmt_deserialize(*sb);
//    pmt::pmt_print(header);
}
