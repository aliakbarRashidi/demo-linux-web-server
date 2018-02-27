/*
 * Copyright (c) 2018, Apriorit, Inc.
 *
 * Demo: Linux Web Server
 *
 * Licensed under MIT license (see LICENSE in the root directory). This file
 * may be copied, distributed, and modified only in accordance with the terms
 * specified by the license.
 */

#include "signal.hpp"

#include <atomic>
#include <system_error>

#include <errno.h>
#include <signal.h>
#include <string.h>

static std::atomic_bool g_termination_signal_received;

static void termination_signal_handler(int)
{
    g_termination_signal_received = true;
}

static void set_signal_handler(int signum, void(*handler)(int))
{
    struct sigaction action;

    memset(&action, 0, sizeof(action));
    action.sa_handler = handler;
    action.sa_flags = 0;

    if (sigaction(signum, &action, nullptr) < 0)
    {
        throw std::system_error(errno, std::generic_category(),
            "failed to set signal handler");
    }
}

void install_signal_handlers()
{
    set_signal_handler(SIGINT, termination_signal_handler);
    set_signal_handler(SIGTERM, termination_signal_handler);
    set_signal_handler(SIGPIPE, SIG_IGN);
}

bool termination_signal_received()
{
    return g_termination_signal_received;
}
