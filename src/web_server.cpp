/*
 * Copyright (c) 2018, Apriorit, Inc.
 *
 * Demo: Linux Web Server
 *
 * Licensed under MIT license (see LICENSE in the root directory). This file
 * may be copied, distributed, and modified only in accordance with the terms
 * specified by the license.
 */

#include "web_server.hpp"

#include <system_error>

#include "addrinfo.hpp"
#include "logging.hpp"
#include "utils.hpp"

namespace demo_web_server
{

static Socket bind_server_address(const std::string &address)
{
    std::string host;
    std::string port;

    parse_address_string(address, host, port);

    auto addr = getaddrinfo(host, port);

    for (const struct addrinfo *info = addr; info; info = info->ai_next)
    {
        try
        {
            Socket socket(info->ai_family, info->ai_socktype, info->ai_protocol);

            socket.bind(info->ai_addr, info->ai_addrlen);

            return socket;
        }
        catch (const std::system_error &e)
        {
            if (e.code().value() == EADDRINUSE)
            {
                continue;
            }

            throw;
        }
    }

    throw std::runtime_error("failed to bind to " + address);
}

WebServer::WebServer(const std::string &address, const std::string &basedir)
  : m_socket(bind_server_address(address))
  , m_basedir(basedir)
{
    LOG_NOTICE << "listening on " << m_socket.getsockname() << "\n";
}

void WebServer::serve()
{
}

} // namespace demo_web_server
