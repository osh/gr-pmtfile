#include <pmtfile.h>
#include <map>
#include <stdio.h>

// open an existing pmt file
pmtfile::pmtfile(std::string filename){
    // read tags in file 
    // make sure we have a d_itemsize
    itemsize = 1; // wedged for the moment

    fd = fopen(filename.c_str(), "rb");
    if(fd == NULL){
        printf("Could not open file %s for reading!\n", filename.c_str());
    }
}   

// open a new pmt file
pmtfile::pmtfile(std::string filename, datatype_t datatype){
    // set datatype tag to be written with header

    itemsize = datatype_size(datatype);

    fd = fopen(filename.c_str(), "wb");
    if(fd == NULL){
        printf("Could not open file %s for writing!\n", filename.c_str());
    }
}


