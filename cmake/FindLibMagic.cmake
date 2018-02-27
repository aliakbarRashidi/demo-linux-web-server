# Copyright (c) 2018, Apriorit, Inc.
#
# Demo: Linux Web Server
#
# Licensed under MIT license (see LICENSE in the root directory). This file
# may be copied, distributed, and modified only in accordance with the terms
# specified by the license.

# Find libmagic header and library
#
# Use this variable if CMake has troubles finding your installation of libmagic:
#
#  LIBMAGIC_ROOT_DIR            root directory of installation (e.g., /opt/libmagic)
#
# Variables defined by this module:
#
#  LIBMAGIC_FOUND               set if libmagic has been found
#  LIBMAGIC_LIBRARIES           libmagic libraries
#  LIBMAGIC_INCLUDE_DIRS        libmagic include directories

find_library(LIBMAGIC_LIBRARIES
    NAMES magic
    HINTS LIBMAGIC_ROOT_DIR
    PATH_SUFFIXES lib
)

find_path(LIBMAGIC_INCLUDE_DIRS
    NAMES magic.h
    HINTS LIBMAGIC_ROOT_DIR
    PATH_SUFFIXES include
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LibMagic DEFAULT_MSG
    LIBMAGIC_LIBRARIES
    LIBMAGIC_INCLUDE_DIRS
)

mark_as_advanced(
    LIBMAGIC_ROOT_DIR
    LIBMAGIC_LIBRARIES
    LIBMAGIC_INCLUDE_DIRS
)
