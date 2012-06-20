#ifndef PMTFILE_H
#define PMTFILE_H

#include <string>
#include <pmtfile_api.h>
#include <stdio.h>
#include <gruel/pmt.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/*
*  PMT File Specification
*  PMT MAGIC_INT32 | PMT PMT_FORMAT | PMT_TAGS ... | DATA
*/

class PMTFILE_API pmtfile {
    
    public:
        static const int num_datatypes = 5;
        typedef enum { CF64=0, RF32=1, RI32=2, RI16=3, RI8=4, CI32=5 } datatype_t;
        
        static const int datatype_size(datatype_t type){
            const int sizes[] = {8,4,4,2,1,4}; //corresponding byte sizes
            return sizes[(int)type];
        }


        static const char* datatype_str(datatype_t type){
            const char* types[] = {"CF64","RF32","RI32","RI16","RI8","CI32"};
            return types[type];
        }

        // read only source constructor
        pmtfile(std::string filename);

        // writable sink constructor
        pmtfile(std::string filename, datatype_t datatype);

        // internals
        datatype_t format;
        int itemsize;
//        FILE* fd;

//        std::filebuf fb;
//        std::ifstream fs;
//        std::ofstream fs;

        pmt::pmt_t header;
        void set_header(pmt::pmt_t hdr);
        void write_header();
        void read_header();
        void print_header();
        void print_fileinfo();

    protected:
        std::string d_filename;
        std::fstream fs;  
        std::streambuf *sb;
        struct stat filestatus;
};

#endif
