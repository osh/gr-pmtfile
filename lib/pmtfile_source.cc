/* -*- c++ -*- */
/* 
 * Copyright 2012 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gr_io_signature.h>
#include <pmtfile_source.h>


pmtfile_source_sptr
pmtfile_make_source (std::string filename, bool repeat)
{
	return pmtfile_source_sptr (new pmtfile_source (filename,repeat));
}


pmtfile_source::pmtfile_source (std::string filename, bool repeat)
	: 
    pmtfile(filename),
    gr_sync_block ("source",
		gr_make_io_signature (0, 0, 0),
		gr_make_io_signature (1, 1, itemsize)),
    d_repeat(repeat),
    d_datastart(0)
{
}


pmtfile_source::~pmtfile_source ()
{
}


int
pmtfile_source::work (int noutput_items,
			gr_vector_const_void_star &input_items,
			gr_vector_void_star &output_items)
{
    // for now we only support tags at the beginning of the stream
    if(nitems_written(0) == 0){
    // extract all the tags from the file
    // populate them as tags
    pmt::pmt_t taglist = pmt::pmt_car(pmt::pmt_cdr(header));
    pmt::pmt_t iter = taglist;
    while( pmt::pmt_is_pair( iter ) ){
        pmt::pmt_t car = pmt::pmt_car(iter);
        pmt::pmt_t cdr = pmt::pmt_cdr(iter);
        pmt::pmt_t timestamp = pmt::pmt_car(car);
        pmt::pmt_t kv = pmt::pmt_cdr(car);
        pmt::pmt_t k = pmt::pmt_car(kv);
        pmt::pmt_t v = pmt::pmt_cdr(kv);
        uint64_t ts = pmt_to_uint64(timestamp);
        add_item_tag(0, ts, k, v, pmt::pmt_intern(d_name));
        iter = cdr;
        }
    }

    // copy data samples
    char* out = (char*) output_items[0];

    // rewind if we need to
    if((fs.tellg()==filestatus.st_size) && d_repeat){
        // reset read pointer
        printf("reset read pointer to after header.\n");
        read_header();
        }

    // compute num output items and read them
    int nitems = std::min(noutput_items, ((int)filestatus.st_size)-((int)fs.tellg()));
    fs.read(out, nitems);
	return nitems;
}

