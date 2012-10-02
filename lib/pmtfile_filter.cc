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
#include <pmtfile_filter.h>


pmtfile_filter_sptr
pmtfile_make_filter (int itemsize, std::vector<std::string> keylist, bool invert)
{
	return pmtfile_filter_sptr (new pmtfile_filter (itemsize, keylist, invert));
}


pmtfile_filter::pmtfile_filter (int itemsize, std::vector<std::string> keylist, bool invert)
	: gr_sync_block ("filter",
		gr_make_io_signature (1, 1, itemsize),
		gr_make_io_signature (1, 1, itemsize)),
    d_itemsize(itemsize),
    d_invert(invert),
    d_keylist(keylist)
{
    set_tag_propagation_policy(TPP_DONT);
    
    std::cout << "keylist: [";
    for(int i=0; i<d_keylist.size(); i++){
        std::cout << d_keylist[i] << ", ";
    }
    std::cout << "]\n";
}


pmtfile_filter::~pmtfile_filter ()
{
}

bool pmtfile_filter::key_in_list(pmt::pmt_t k){
    if(!pmt::pmt_is_symbol(k)){ return false; }
    std::string kv(pmt::pmt_symbol_to_string(k));
    std::cout << "key_in_list --> " << k << "\n";
    for(int i=0; i<d_keylist.size(); i++){
        std::cout << "mathcing: " << d_keylist[i] << "\n";
        if(d_keylist[i].compare(kv)==0){ return true; }
    }
    return false;
}

int
pmtfile_filter::work (int noutput_items,
			gr_vector_const_void_star &input_items,
			gr_vector_void_star &output_items)
{
	const void *in = input_items[0];
	void *out = output_items[0];
    
    std::vector<gr_tag_t> all_tags;
    get_tags_in_range(all_tags, 0,  nitems_read(0),  nitems_read(0) + noutput_items);
    std::vector<gr_tag_t>::iterator itr;
    for(itr = all_tags.begin(); itr != all_tags.end(); itr++) {
        if( key_in_list(itr->key)^d_invert ){
            add_item_tag(0, itr->offset, itr->key, itr->value, itr->srcid);
        }
    }

    memcpy(out, in, noutput_items * d_itemsize);
	return noutput_items;
}

