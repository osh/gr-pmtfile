#!/usr/bin/env python


from gnuradio import gr;
import pmtfile;

src = gr.vector_source_b(range(0,10));
snk = pmtfile.sink("output.pf", pmtfile.pmtfile.CF64);

tb = gr.top_block();
tb.connect(src,snk);






