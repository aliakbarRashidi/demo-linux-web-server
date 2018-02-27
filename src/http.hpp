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

std::string get_request_path(const std::string &request);

std::string success_header_200(const std::string &mime, size_t size);

std::string error_message_404(const std::string &path);
std::string error_message_500(const std::string &error_text);
