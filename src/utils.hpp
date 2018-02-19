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
 * Parse an address string like "some-host:42" into separate host and port parts.
 *
 * If the string does not contain a port separator then it is treated as a port with an empty host.
 *
 * @param address   address to parse
 * @param host      put hostname here
 * @param port      put port here
 */
void parse_address_string(const std::string &address, std::string &host, std::string &port);

} // namespace demo_web_server
