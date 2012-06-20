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
#include <pmtfile_sink.h>
#include <sstream>
#include <iostream>

pmtfile_sink_sptr
pmtfile_make_sink (std::string filename, pmtfile::datatype_t datatype)
{
	return pmtfile_sink_sptr (new pmtfile_sink (filename,datatype));
}


pmtfile_sink::pmtfile_sink (std::string filename, pmtfile::datatype_t datatype)
	: pmtfile(filename, datatype),
      gr_sync_block ("sink",
		gr_make_io_signature (1, 1, itemsize),
		gr_make_io_signature (0, 0, 0))
{
    format = datatype;
}


pmtfile_sink::~pmtfile_sink ()
{
}


int
pmtfile_sink::work (int noutput_items,
			gr_vector_const_void_star &input_items,
			gr_vector_void_star &output_items)
{

    pmt::pmt_t tag_list(pmt::PMT_NIL);

    // for now we only support tags at the beginning of the stream
    if(nitems_read(0) == 0){
        std::vector<gr_tag_t> all_tags;
        // TODO: get all tags? for now we only grab the ones at the start of the stream
        get_tags_in_range(all_tags, 0, nitems_read(0),nitems_read(0)+noutput_items);
        std::sort(all_tags.begin(), all_tags.end(), gr_tag_t::offset_compare);


        // set a format tag to store
        pmt::pmt_t fmt_pmt = pmt::pmt_cons( pmt::pmt_from_uint64( 0 ), 
            pmt::pmt_cons( pmt::pmt_string_to_symbol("format"),
            pmt::pmt_string_to_symbol(datatype_str(format)) ) );
        tag_list = pmt::pmt_list1( fmt_pmt );

        // iterate over tags adding them to our list
        for(int i=0; i<all_tags.size(); i++){
            gr_tag_t* tag = &all_tags[i];

//            pmt::pmt_print( tag->key );
//            pmt::pmt_print( tag->value );

            // add key if it is not a prior format tag ( we regenerate those )
            if( pmt::pmt_symbol_to_string(tag->key).compare("format") != 0){
                // TAG = ( time, ( key, val ) )
                pmt::pmt_t tag_pmt = pmt::pmt_cons( pmt::pmt_from_uint64( tag->offset ), 
                            pmt::pmt_cons( tag->key, tag->value ) );
                tag_list = pmt::pmt_list_add(tag_list, tag_pmt);
            }
        }

        // write out serialized tags
        set_header(tag_list);       
//        print_header();
        write_header();
    }

    fs.write( (const char*)input_items[0], noutput_items );
	return noutput_items;
}

