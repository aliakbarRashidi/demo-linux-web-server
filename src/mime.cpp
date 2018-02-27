/*
 * Copyright (c) 2018, Apriorit, Inc.
 *
 * Demo: Linux Web Server
 *
 * Licensed under MIT license (see LICENSE in the root directory). This file
 * may be copied, distributed, and modified only in accordance with the terms
 * specified by the license.
 */

#include "mime.hpp"

#include <system_error>

#include <magic.h>

class Magic
{
public:
    explicit Magic(int flags)
    {
        m_magic = magic_open(flags);

        if (!m_magic)
        {
            throw std::system_error(errno, std::generic_category(),
                "failed to open magic library");
        }
    }

    ~Magic()
    {
        magic_close(m_magic);
    }

    operator magic_t()
    {
        return m_magic;
    }

private:
    magic_t m_magic;
};

std::string file_mime_type(const std::string &path)
{
    Magic magic(MAGIC_SYMLINK | MAGIC_MIME_TYPE);

    if (magic_load(magic, nullptr) < 0)
    {
        throw std::runtime_error(std::string("failed to load magic database: ")
                                 + magic_error(magic));
    }

    const char *mime_type = magic_file(magic, path.c_str());

    if (!mime_type)
    {
        throw std::runtime_error(std::string("failed to check MIME type: ")
                                 + magic_error(magic));
    }

    return mime_type;
}
