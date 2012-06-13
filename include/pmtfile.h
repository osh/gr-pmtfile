#ifndef PMTFILE_H
#define PMTFILE_H

#include <string>
#include <pmtfile_api.h>
#include <stdio.h>

/*
*  PMT File Specification
*  
*
*/

class PMTFILE_API pmtfile {
    
    public:
        typedef enum { CF64=0, RF32=1, RI32=2, RI16=3, RI8=4 } datatype_t;
        
        static const int datatype_size(datatype_t type){
            const int sizes[] = {8,4,4,2,1}; //corresponding byte sizes
            return sizes[(int)type];
        }

        static const char* datatype_str(datatype_t type){
            const char* types[] = {"CF64","RF32","RI32","RI16","RI8"};
            return types[type];
        }

        // read only source constructor
        pmtfile(std::string filename);

        // writable sink constructor
        pmtfile(std::string filename, datatype_t datatype);

        // internals
        datatype_t format;
        int itemsize;
        FILE* fd;

};

#endif
