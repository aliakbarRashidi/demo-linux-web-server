# Copyright (c) 2018, Apriorit, Inc.
#
# Demo: Linux Web Server
#
# Licensed under MIT license (see LICENSE in the root directory). This file
# may be copied, distributed, and modified only in accordance with the terms
# specified by the license.

cmake_minimum_required(VERSION 3.2)

add_executable(demo-web-server
    demo_web_server.cpp
    addrinfo.cpp
    logging.hpp
    socket.cpp
    utils.cpp
    web_server.cpp
)

configure_file(version.hpp.in version.hpp @ONLY)
target_include_directories(demo-web-server PRIVATE ${CMAKE_CURRENT_BINARY_DIR})