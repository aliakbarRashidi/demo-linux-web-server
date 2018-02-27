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
#include <memory>
#include <system_error>

#include <pthread.h>

class Thread
{
    pthread_t m_thread;
    bool m_detached;

public:
    template <class F>
    explicit Thread(F &&f)
      : m_thread(0)
      , m_detached(false)
    {
        std::unique_ptr<F> function(new F(std::move(f)));

        int error = ::pthread_create(&m_thread, nullptr, Thread::thunk<F>, function.get());

        if (error)
        {
            throw std::system_error(error, std::generic_category(),
                "failed to create a thread");
        }

        function.release();
    }

    ~Thread()
    {
        if (!m_detached)
        {
            std::cerr << "destroying a non-detached a thread" << std::endl;
        }
    }

    void detach()
    {
        int error = ::pthread_detach(m_thread);

        if (error)
        {
            throw std::system_error(error, std::generic_category(),
                "failed to detach a thread");
        }

        m_detached = true;
    }

private:
    template <class F>
    static void* thunk(void *arg)
    {
        std::unique_ptr<F> function(reinterpret_cast<F*>(arg));

        (*function)();

        return nullptr;
    }
};
