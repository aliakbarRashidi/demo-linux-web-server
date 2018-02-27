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

class File;

struct Socket
{
public:
    explicit Socket(int domain, int type, int protocol);

    ~Socket();

    Socket(Socket&& other);
    Socket& operator=(Socket&& other);

    Socket accept();
    void bind(const struct sockaddr *addr, socklen_t len);
    void listen(int backlog);
    void shutdown();

    std::string getsockname() const;
    std::string getpeername() const;

    std::string read();
    void write(const std::string &message);
    void sendfile(File &file, size_t size);

private:
    explicit Socket(int fd);

private:
    int m_fd;
};
