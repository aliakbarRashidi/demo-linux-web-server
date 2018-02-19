/*
 * Copyright (c) 2018, Apriorit, Inc.
 *
 * Demo: Linux Web Server
 *
 * Licensed under MIT license (see LICENSE in the root directory). This file
 * may be copied, distributed, and modified only in accordance with the terms
 * specified by the license.
 */

#include "utils.hpp"

#include <stdexcept>

namespace demo_web_server
{

void parse_address_string(const std::string &address, std::string &host, std::string &port)
{
    if (address.empty())
    {
        throw std::runtime_error("empty address string");
    }

    auto port_index = address.rfind(':');

    if (port_index == std::string::npos)
    {
        host = "";
        port = address;
    }
    else
    {
        host = address.substr(0, port_index);
        port = address.substr(port_index + 1);
    }
}

} // namespace demo_web_server
