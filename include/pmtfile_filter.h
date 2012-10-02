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

#ifndef INCLUDED_PMTFILE_FILTER_H
#define INCLUDED_PMTFILE_FILTER_H

#include <pmtfile_api.h>
#include <gr_sync_block.h>

class pmtfile_filter;
typedef boost::shared_ptr<pmtfile_filter> pmtfile_filter_sptr;

PMTFILE_API pmtfile_filter_sptr pmtfile_make_filter (int itemsize, std::vector<std::string> keylist, bool invert=false);

/*!
 * \brief <+description+>
 *
 */
class PMTFILE_API pmtfile_filter : public gr_sync_block
{
	friend PMTFILE_API pmtfile_filter_sptr pmtfile_make_filter (int itemsize, std::vector<std::string> keylist, bool invert);

	pmtfile_filter (int itemsize, std::vector<std::string> keylist, bool invert = false);
    int d_itemsize;
    bool d_invert;
    std::vector<std::string> d_keylist;
    bool key_in_list(pmt::pmt_t k);

 public:
	~pmtfile_filter ();
	int work (int noutput_items,
		gr_vector_const_void_star &input_items,
		gr_vector_void_star &output_items);
};

#endif /* INCLUDED_PMTFILE_FILTER_H */

