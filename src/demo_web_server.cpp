/*
 * Copyright (c) 2018, Apriorit, Inc.
 *
 * Demo: Linux Web Server
 *
 * Licensed under MIT license (see LICENSE in the root directory). This file
 * may be copied, distributed, and modified only in accordance with the terms
 * specified by the license.
 */

#include <getopt.h>
#include <iostream>
#include <stdexcept>

#include "web_server.hpp"
#include "version.hpp"

static const struct option long_options[] = {
    { "help",       0, nullptr, 'h' },
    { "version",    0, nullptr, 'v' },
    { "listen",     1, nullptr, 'a' },
    { nullptr },
};

static void show_version()
{
    std::cout << "Demo: Linux Web Server v" PROJECT_VERSION "\n";
}

static void show_usage(const char *program)
{
    std::cout << "Usage:\n"
                 "\n"
                 "  " << program << " [--listen <address>] <www-directory>\n"
                 "\n"
                 "Options:\n"
                 "  -h, --help      show this help and exit\n"
                 "  -v, --version   show version and exit\n"
                 "  -a, --listen    set address:port to listen to (defaults to :::80)\n"
                 "\n"
                 "Arguments:\n"
                 "  www-directory   the directory with content to host, defaults to /var/www\n";
}

int main(int argc, char *argv[])
{
    int opt;
    std::string listen_address = ":::80";
    std::string www_directory = "/var/www";

    while ((opt = getopt_long(argc, argv, "hva:", long_options, nullptr)) != -1)
    {
        switch (opt)
        {
        case 'h':
            show_usage(argv[0]);
            return 0;

        case 'v':
            show_version();
            return 0;

        case 'a':
            listen_address = optarg;
            break;

        default:
            show_usage(argv[0]);
            return 1;
        }
    }

    if (argc > optind)
    {
        www_directory = argv[optind];

        if (argc > optind + 1)
        {
            std::cerr << argv[0] << ": only one www-directory can be specified\n";
            show_usage(argv[0]);
            return 1;
        }
    }

    try
    {
        WebServer server(listen_address, www_directory);

        try
        {
            server.serve();
        }
        catch (const std::exception &e)
        {
            std::cerr << "fatal error: " << e.what() << "\n";
            return 3;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "fatal startup error: " << e.what() << "\n";
        return 2;
    }
}
