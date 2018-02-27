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
#include <sys/sendfile.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>
#include <system_error>

#include "file.hpp"

static const size_t kMaxRequestSize = 4096;

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

Socket::Socket(int fd)
  : m_fd(fd)
{
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
        std::cerr << "failed to close a socket: "
                  << std::error_code(errno, std::generic_category()).message()
                  << "\n";
    }
}

Socket Socket::accept()
{
    int new_fd = ::accept(m_fd, nullptr, nullptr);

    if (new_fd < 0)
    {
        throw std::system_error(errno, std::generic_category(),
            "failed to accept a connection");
    }

    return Socket(new_fd);
}

void Socket::bind(const sockaddr *addr, socklen_t len)
{
    if (::bind(m_fd, addr, len))
    {
        throw std::system_error(errno, std::generic_category(),
            "failed to bind a socket");
    }
}

void Socket::listen(int backlog)
{
    if (::listen(m_fd, backlog))
    {
        throw std::system_error(errno, std::generic_category(),
            "failed to listen to a socket");
    }
}

void Socket::shutdown()
{
    if (::shutdown(m_fd, SHUT_RDWR))
    {
        throw std::system_error(errno, std::generic_category(),
            "failed to close the connection");
    }
}

static std::string print_sockaddr(const struct sockaddr_storage &addr, socklen_t len)
{
    char host[NI_MAXHOST];
    char port[NI_MAXSERV];
    int err = ::getnameinfo(reinterpret_cast<const struct sockaddr*>(&addr), len,
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

std::string Socket::getsockname() const
{
    struct sockaddr_storage addr;
    socklen_t len = sizeof(addr);

    if (::getsockname(m_fd, reinterpret_cast<struct sockaddr*>(&addr), &len) < 0)
    {
        throw std::system_error(errno, std::generic_category(),
            "failed to get socket name");
    }

    return print_sockaddr(addr, len);
}

std::string Socket::getpeername() const
{
    struct sockaddr_storage addr;
    socklen_t len = sizeof(addr);

    if (::getpeername(m_fd, reinterpret_cast<struct sockaddr*>(&addr), &len) < 0)
    {
        throw std::system_error(errno, std::generic_category(),
            "failed to get socket peer name");
    }

    return print_sockaddr(addr, len);
}

std::string Socket::read()
{
    char buffer[kMaxRequestSize];

    ssize_t read_bytes = ::read(m_fd, buffer, sizeof(buffer));

    if (read_bytes < 0)
    {
        throw std::system_error(errno, std::generic_category(),
            "failed to read from a socket");
    }

    return std::string(buffer, static_cast<size_t>(read_bytes));
}

void Socket::write(const std::string &message)
{
    const char *data = message.data();
    size_t left = message.length();

    while (left > 0)
    {
        ssize_t wrote_bytes = ::write(m_fd, data, left);

        if (wrote_bytes < 0)
        {
            throw std::system_error(errno, std::generic_category(),
                "failed to write to a socket");
        }

        data += static_cast<size_t>(wrote_bytes);
        left -= static_cast<size_t>(wrote_bytes);
    }
}

void Socket::sendfile(File &file, size_t size)
{
    size_t left = size;

    while (left > 0)
    {
        ssize_t sent_bytes = ::sendfile(m_fd, file.m_fd, nullptr, left);

        if (sent_bytes < 0)
        {
            throw std::system_error(errno, std::generic_category(),
                "failed to send a file");
        }

        left -= sent_bytes;
    }
}
