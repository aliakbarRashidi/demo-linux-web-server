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
#include <netdb.h>

#include <string>

namespace demo_web_server
{

/**
 * RAII wrapper over `struct addrinfo`.
 */
class AddrInfo
{
public:
    explicit AddrInfo(struct addrinfo *info);
    ~AddrInfo();

    operator const struct addrinfo*() const
    {
        return m_info;
    }

private:
    struct addrinfo *m_info;
};

AddrInfo getaddrinfo(const std::string &name, const std::string &service);

} // namespace demo_web_server
