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


class qa_source (gr_unittest.TestCase):

    def setUp (self):
        pass

    def tearDown (self):
        pass

    def test_001_t (self):
        tb = gr.top_block();
        src = pmtfile.source("test1.pf");
#        op = gr.add_const_bb(1);
        snk = pmtfile.sink("test2.pf", pmtfile.pmtfile.RI8);

        tb.connect(src,snk);
        tb.run();



if __name__ == '__main__':
    gr_unittest.main ()
