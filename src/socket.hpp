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

#include <sys/types.h>
#include <sys/socket.h>

#include <string>

namespace demo_web_server
{

/**
 * RAII wrapper over raw socket descriptors.
 */
struct Socket
{
public:
    /**
     * Make a new socket with specified domain, type, protocol.
     */
    explicit Socket(int domain, int type, int protocol);

    /**
     * Move other socket into this one.
     */
    Socket(Socket&& other);

    /**
     * Move other socket into this one.
     */
    Socket& operator=(Socket&& other);

    /**
     * Close this socket.
     */
    ~Socket();

    /**
     * Bind an address to the socket.
     */
    void bind(const struct sockaddr *addr, socklen_t len);

    /**
     * Get address bound to the socket (as string).
     */
    std::string getsockname() const;

private:
    int m_fd;
};

} // namespace demo_web_server