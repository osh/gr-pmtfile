#!/usr/bin/env python
# 
# Copyright 2012 <+YOU OR YOUR COMPANY+>.
# 
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 
#

from gnuradio import gr, gr_unittest
try:
    import pmtfile_swig as pmtfile
except:
    import pmtfile
from gruel import pmt;

class qa_sink (gr_unittest.TestCase):

    def setUp (self):
        pass

    def tearDown (self):
        pass

    def test_001_t (self):

        # set up fg
        src = gr.file_source(1, "/dev/urandom");
        ann = gr.annotator_raw(1);
        head = gr.head(1, 100000);
        snk = pmtfile.sink("testfile.pf", pmtfile.pmtfile.RI8);
        tb = gr.top_block();

        # connections
        tb.connect(src,ann,head,snk);

        # add a test tag via the annotator
        ann.add_tag(0,pmt.pmt_string_to_symbol("test"), pmt.pmt_string_to_symbol("testval"));
        
        # run the graph
        tb.run ()

        # check data


if __name__ == '__main__':
    gr_unittest.main ()
