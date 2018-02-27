/*
 * Copyright (c) 2018, Apriorit, Inc.
 *
 * Demo: Linux Web Server
 *
 * Licensed under MIT license (see LICENSE in the root directory). This file
 * may be copied, distributed, and modified only in accordance with the terms
 * specified by the license.
 */

#include "addrinfo.hpp"

#include <stdexcept>

AddrInfo getaddrinfo(const std::string &name, const std::string &service)
{
    struct addrinfo hints;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;
    hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;

    struct addrinfo *result = nullptr;
    int err = ::getaddrinfo(name.empty() ? NULL : name.c_str(),
                            service.empty() ? NULL : service.c_str(),
                            &hints, &result);
    if (err)
    {
        throw std::runtime_error("failed to resolve address " + name + ":" + service
                                 + ": " + gai_strerror(err));
    }

    return AddrInfo(result);
}

AddrInfo::AddrInfo(struct addrinfo *info)
  : m_info(info)
{
}

AddrInfo::~AddrInfo()
{
    freeaddrinfo(m_info);
}

AddrInfo::AddrInfo(AddrInfo &&other)
{
    m_info = other.m_info;
    other.m_info = nullptr;
}

AddrInfo& AddrInfo::operator=(AddrInfo &&other)
{
    if (this != &other)
    {
        freeaddrinfo(m_info);

        m_info = other.m_info;
        other.m_info = nullptr;
    }
    return *this;
}
