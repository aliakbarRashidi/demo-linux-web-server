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

class File
{
public:
    explicit File(const std::string &path);

    ~File();

    size_t size() const;

private:
    int m_fd;
};

} // namespace demo_web_server
