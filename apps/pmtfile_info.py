#!/usr/bin/env python
import pmtfile;
import sys;

if(len(sys.argv) < 2):
    print "usage: %s <filename>"%(sys.argv[0]);
    sys.exit(-1);

for f in sys.argv[1:]:
    pf = pmtfile.pmtfile(f);
    pf.print_fileinfo();
    pf.print_header();

