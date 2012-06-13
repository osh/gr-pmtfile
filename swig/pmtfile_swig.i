/* -*- c++ -*- */

#define PMTFILE_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "pmtfile_swig_doc.i"

%{
#include "pmtfile_source.h"
#include "pmtfile_sink.h"
#include "pmtfile.h"
%}

GR_SWIG_BLOCK_MAGIC(pmtfile,source);
%include "pmtfile_source.h"

GR_SWIG_BLOCK_MAGIC(pmtfile,sink);
%include "pmtfile_sink.h"

%include "pmtfile.h"

#if SWIGGUILE
%scheme %{
(load-extension-global "libguile-gnuradio-pmtfile_swig" "scm_init_gnuradio_pmtfile_swig_module")
%}

%goops %{
(use-modules (gnuradio gnuradio_core_runtime))
%}
#endif
