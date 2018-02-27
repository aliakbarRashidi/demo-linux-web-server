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

#include <iostream>
#include <memory>
#include <system_error>

#include "addrinfo.hpp"
#include "file.hpp"
#include "http.hpp"
#include "mime.hpp"
#include "thread.hpp"

/// Maximum number of pending unaccepted connections.
static const int kDefaultConnectionBacklog = 10;

static const std::string kDefaultPath = "/index.html";

static void parse_address_string(const std::string &address, std::string &host, std::string &port)
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
    std::cout << "listening on " << m_socket.getsockname() << std::endl;

    m_socket.listen(kDefaultConnectionBacklog);
}

void WebServer::serve()
{
    while (true)
    {
        auto connection = m_socket.accept();

        std::cout << "accepted a new connection from " << connection.getpeername() << std::endl;

        Thread thread(std::bind([](Socket &connection, std::string basedir)
        {
            try
            {
                auto request = connection.read();
                auto request_path = get_request_path(request);
                auto full_path = basedir + ((request_path == "/") ? kDefaultPath : request_path);
                auto mime_type = file_mime_type(full_path);

                std::cout << "sending " << mime_type << " \"" << full_path << "\"" << std::endl;

                try
                {
                    File file(full_path);
                    auto size = file.size();

                    connection.write(success_header_200(mime_type, size));
                    connection.sendfile(file, size);
                }
                catch (const std::system_error &e)
                {
                    if (e.code().value() == ENOENT)
                    {
                        connection.write(error_message_404(request_path));
                    }
                    else
                    {
                        throw;
                    }
                }
            }
            catch (const std::exception &e)
            {
                connection.write(error_message_500(e.what()));
            }

            connection.shutdown();
        }, std::move(connection), m_basedir));

        thread.detach();
    }
}
