#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>
#include <stdexcept>
#include <iostream>
#include "ThreadException.h"

class Thread {
public:
    
    Thread() : m_thread(0), m_started(false), m_joined(false) {}
    virtual ~Thread() {
        if (m_started && !m_joined) {
            pthread_detach(m_thread);
        }
    }

    void start() {
        if (m_started) return;

        int ret = pthread_create(&m_thread, nullptr, &Thread::entryPoint, this);
        if (ret != 0) {
            throw ThreadException("Thread create failed");
        }
        m_started = true;
    }

    void join() {
        if (!m_started || m_joined) return;

        int ret = pthread_join(m_thread, nullptr);
        if (ret != 0) {
            throw ThreadException("Thread joined");
        }
        m_joined = true;
    }

protected:
    virtual void run() = 0;

private:
    static void* entryPoint(void* args) {
        Thread* self = static_cast<Thread*>(args);
        try {
            self->run();
        } catch (const std::exception& e) {
            std::cerr << "Thread crash: " << e.what() << "\n";
        }
        return nullptr;
    }

    pthread_t m_thread;
    bool m_started;
    bool m_joined;

    Thread(const Thread&) = delete;
    Thread& operator=(Thread&) = delete;
};

#endif