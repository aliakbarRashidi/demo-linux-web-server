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

#include <memory>
#include <system_error>

#include <pthread.h>

#include "logging.hpp"

namespace demo_web_server
{

/**
 * A thread of execution.
 */
class Thread
{
    pthread_t m_thread;
    bool m_detached;

public:
    /**
     * Create and launch a thread executing a provided function.
     */
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

    /**
     * Destroy a thread.
     *
     * You may not destroy threads which were not joined or detached.
     */
    ~Thread()
    {
        if (!m_detached)
        {
            LOG_WARNING << "destroying a non-detached a thread" << std::endl;
        }
    }

    /**
     * Detach the thread.
     */
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

} // namespace demo_web_server
