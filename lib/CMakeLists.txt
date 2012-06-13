# Copyright 2011 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

########################################################################
# Setup library
########################################################################
include(GrPlatform) #define LIB_SUFFIX
add_library(gnuradio-pmtfile SHARED pmtfile_source.cc pmtfile_sink.cc pmtfile.cc)
target_link_libraries(gnuradio-pmtfile ${Boost_LIBRARIES} ${GRUEL_LIBRARIES} ${GNURADIO_CORE_LIBRARIES})
set_target_properties(gnuradio-pmtfile PROPERTIES DEFINE_SYMBOL "gnuradio_pmtfile_EXPORTS")

########################################################################
# Install built library files
########################################################################
install(TARGETS gnuradio-pmtfile
    LIBRARY DESTINATION lib${LIB_SUFFIX} # .so/.dylib file
    ARCHIVE DESTINATION lib${LIB_SUFFIX} # .lib file
    RUNTIME DESTINATION bin              # .dll file
)

########################################################################
# Build and register unit test
########################################################################
find_package(Boost COMPONENTS unit_test_framework)

include(GrTest)
set(GR_TEST_TARGET_DEPS gnuradio-pmtfile)
#turn each test cpp file into an executable with an int main() function
add_definitions(-DBOOST_TEST_DYN_LINK -DBOOST_TEST_MAIN)

add_executable(qa_pmtfile_source qa_pmtfile_source.cc)
target_link_libraries(qa_pmtfile_source gnuradio-pmtfile ${Boost_LIBRARIES})
GR_ADD_TEST(qa_pmtfile_source qa_pmtfile_source)

add_executable(qa_pmtfile_sink qa_pmtfile_sink.cc)
target_link_libraries(qa_pmtfile_sink gnuradio-pmtfile ${Boost_LIBRARIES})
GR_ADD_TEST(qa_pmtfile_sink qa_pmtfile_sink)
