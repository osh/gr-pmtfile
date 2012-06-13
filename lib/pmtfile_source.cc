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
pmtfile_make_source (std::string filename)
{
	return pmtfile_source_sptr (new pmtfile_source (filename));
}


pmtfile_source::pmtfile_source (std::string filename)
	: 
    pmtfile("pmtfile.test"),
    gr_sync_block ("source",
		gr_make_io_signature (0, 0, 0),
		gr_make_io_signature (1, 1, itemsize))
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
	return noutput_items;
}

