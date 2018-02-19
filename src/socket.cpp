/*
 * Copyright (c) 2018, Apriorit, Inc.
 *
 * Demo: Linux Web Server
 *
 * Licensed under MIT license (see LICENSE in the root directory). This file
 * may be copied, distributed, and modified only in accordance with the terms
 * specified by the license.
 */

#include "socket.hpp"

#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include <system_error>

#include "logging.hpp"

namespace demo_web_server
{

Socket::Socket(int domain, int type, int protocol)
  : m_fd(-1)
{
    m_fd = ::socket(domain, type, protocol);

    if (m_fd < 0)
    {
        throw std::system_error(errno, std::generic_category(),
            "failed to create a socket");
    }
}

Socket::Socket(Socket&& other)
{
    m_fd = other.m_fd;
    other.m_fd = -1;
}

Socket& Socket::operator=(Socket&& other)
{
    if (this != &other)
    {
        m_fd = other.m_fd;
        other.m_fd = -1;
    }
    return *this;
}

Socket::~Socket()
{
    if (m_fd < 0)
    {
        return;
    }

    if (::close(m_fd) < 0)
    {
        LOG_WARNING << "failed to close a socket: "
                    << std::error_code(errno, std::generic_category()).message()
                    << "\n";
    }
}

void Socket::bind(const sockaddr *addr, socklen_t len)
{
    if (::bind(m_fd, addr, len))
    {
        throw std::system_error(errno, std::generic_category(),
            "failed to bind a socket");
    }
}

std::string Socket::getsockname() const
{
    struct sockaddr_storage addr;
    socklen_t len = sizeof(addr);

    if (::getsockname(m_fd, reinterpret_cast<struct sockaddr*>(&addr), &len) < 0)
    {
        throw std::system_error(errno, std::generic_category(),
            "failed to get socket name");
    }

    char host[NI_MAXHOST];
    char port[NI_MAXSERV];
    int err = ::getnameinfo(reinterpret_cast<struct sockaddr*>(&addr), len,
                            host, sizeof(host), port, sizeof(port), 0);

    if (err)
    {
        throw std::runtime_error(std::string("failed to get socket name: ") + gai_strerror(err));
    }

    std::string result;
    result += host;
    result += ":";
    result += port;
    return result;
}

} // namespace demo_web_server
