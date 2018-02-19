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

namespace demo_web_server
{

/**
 * Main web server loop.
 */
class WebServer
{
public:
    /**
     * Make a new web server.
     *
     * @param address   address to listen to
     * @param basedir   base directory to serve files from
     */
    explicit WebServer(const std::string &address, const std::string &basedir);

    /**
     * Start the server event loop.
     */
    void serve();
};

} // namespace demo_web_server
