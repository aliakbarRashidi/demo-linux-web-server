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

class Socket;

class File
{
public:
    explicit File(const std::string &path);

    ~File();

    size_t size() const;

private:
    friend class Socket;

    int m_fd;
};
