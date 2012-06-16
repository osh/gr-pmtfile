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

#ifndef INCLUDED_PMTFILE_SOURCE_H
#define INCLUDED_PMTFILE_SOURCE_H

#include <pmtfile.h>
#include <pmtfile_api.h>
#include <gr_sync_block.h>

class pmtfile_source;
typedef boost::shared_ptr<pmtfile_source> pmtfile_source_sptr;

PMTFILE_API pmtfile_source_sptr pmtfile_make_source (std::string filename, bool repeat=false);

/*!
 * \brief PMTFile Source - reads in pmt-tagged data files
 *
 */
class PMTFILE_API pmtfile_source : public pmtfile, public gr_sync_block
{
	friend PMTFILE_API pmtfile_source_sptr pmtfile_make_source (std::string filename, bool repeat);

	pmtfile_source (std::string filename, bool repeat=false);

 public:
	~pmtfile_source ();

    bool d_repeat;
    int d_datastart;
	int work (int noutput_items,
		gr_vector_const_void_star &input_items,
		gr_vector_void_star &output_items);
};

#endif /* INCLUDED_PMTFILE_SOURCE_H */

