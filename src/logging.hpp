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

#include <iostream>

//! Some convenience macros to make output of journald-compatible messages more readable.

#define LOG_EMERGENCY   std::cout << "<0>"
#define LOG_ALERT       std::cout << "<1>"
#define LOG_CRITICAL    std::cout << "<2>"
#define LOG_ERROR       std::cout << "<3>"
#define LOG_WARNING     std::cout << "<4>"
#define LOG_NOTICE      std::cout << "<5>"
#define LOG_INFO        std::cout << "<6>"
#define LOG_DEBUG       std::cout << "<7>"
