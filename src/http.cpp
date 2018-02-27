/*
 * Copyright (c) 2018, Apriorit, Inc.
 *
 * Demo: Linux Web Server
 *
 * Licensed under MIT license (see LICENSE in the root directory). This file
 * may be copied, distributed, and modified only in accordance with the terms
 * specified by the license.
 */

#include "http.hpp"

#include <regex>
#include <stdexcept>

std::string get_request_path(const std::string &request)
{
    std::regex get_request("^GET (/[^ ]*) ", std::regex_constants::icase);

    std::smatch match;

    if (!std::regex_search(request, match, get_request))
    {
        throw std::runtime_error("invalid request: " + request);
    }

    return match[1];
}

std::string success_header_200(const std::string &mime, size_t size)
{
    std::string result;
    result += "HTTP/1.1 200 OK\r\n";
    result += "Server: DemoWebServer (Linux)\r\n";
    result += "Content-Type:";
    result += mime;
    result += "\r\n";
    result += "Content-Length: ";
    result += std::to_string(size);
    result += "\r\n";
    result += "Connection: closed\r\n";
    result += "\r\n";
    return result;
}

static std::string error_message(const std::string &code, const std::string &body)
{
    std::string result;
    result += "HTTP/1.1 ";
    result += code;
    result += "\r\n";
    result += "Server: DemoWebServer (Linux)\r\n";
    result += "Content-Type: text/html\r\n";
    result += "Content-Length: ";
    result += std::to_string(body.length());
    result += "\r\n";
    result += "Connection: closed\r\n";
    result += "\r\n";
    result += body;
    return result;
}

std::string error_message_404(const std::string &path)
{
    std::string message;

    message += "<h1>404 File Not Found</h1>";
    message += "<p>These are not the droids you are looking for:</p>";
    message += "<pre>";
    message += path;
    message += "</pre>";
    message += "<hr><p><i>DemoWebServer</i></p>";

    return error_message("404 File Not Found", message);
}

std::string error_message_500(const std::string &error_text)
{
    std::string message;

    message += "<h1>500 Internal Server Error</h1>";
    message += "<p>I'm sorry, something went wrong:</p>";
    message += "<pre>";
    message += error_text;
    message += "</pre>";
    message += "<hr><p><i>DemoWebServer</i></p>";

    return error_message("500 Internal Server Error", message);
}
