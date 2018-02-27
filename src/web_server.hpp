/*
 * Copyright (c) 2018, Apriorit, Inc.
 *
 * Demo: Linux Web Server
 *
 * Licensed under MIT license (see LICENSE in the root directory). This file
 * may be copied, distributed, and modified only in accordance with the terms
 * specified by the license.
 */

#pragma once

#include <string>

#include "socket.hpp"

class WebServer
{
public:
    explicit WebServer(const std::string &address, const std::string &basedir);

    void serve();

private:
    Socket m_socket;
    std::string m_basedir;
};
