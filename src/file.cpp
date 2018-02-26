/*
 * Copyright (c) 2018, Apriorit, Inc.
 *
 * Demo: Linux Web Server
 *
 * Licensed under MIT license (see LICENSE in the root directory). This file
 * may be copied, distributed, and modified only in accordance with the terms
 * specified by the license.
 */

#include "file.hpp"

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <system_error>

#include "logging.hpp"

namespace demo_web_server
{

File::File(const std::string &path)
  : m_fd(-1)
{
    m_fd = ::open(path.c_str(), O_RDONLY);

    if (m_fd < 0)
    {
        throw std::system_error(errno, std::generic_category(),
            "failed to open a file");
    }
}

File::~File()
{
    if (::close(m_fd) < 0)
    {
        LOG_WARNING << "failed to close a file: "
                    << std::error_code(errno, std::generic_category()).message()
                    << std::endl;
    }
}

size_t File::size() const
{
    struct stat buf;

    if (::fstat(m_fd, &buf) < 0)
    {
        throw std::system_error(errno, std::generic_category(),
            "failed to stat a file");
    }

    return buf.st_size;
}

} // namespace demo_web_server
