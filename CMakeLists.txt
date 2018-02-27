# Copyright (c) 2018, Apriorit, Inc.
#
# Demo: Linux Web Server
#
# Licensed under MIT license (see LICENSE in the root directory). This file
# may be copied, distributed, and modified only in accordance with the terms
# specified by the license.

cmake_minimum_required(VERSION 3.2)

project(DemoWebServer
    VERSION 0.1.0
    LANGUAGES C CXX
)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

add_subdirectory(src)
