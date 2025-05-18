#ifndef MUTEX_H
#define MUTEX_H

#include "fmt/core.h"
#include "pthread.h"
#include "ThreadException.h"


class Mutex {
public:
    Mutex() {
        if (pthread_mutex_init(&m_mutex, nullptr) != 0) {
            throw ThreadException("mutext init failed");
        }
        fmt::print("mutext inited\n");
    }
    ~Mutex() {
        pthread_mutex_destroy(&m_mutex);
        fmt::print("mutext destroied\n");
    }



    void lock() {
        if (pthread_mutex_lock(&m_mutex) != 0) {
            throw ThreadException("mutext lock failed");
        }
        fmt::print("mutext locked\n");
    }
    void unlock() {
        if (pthread_mutex_unlock(&m_mutex) != 0) {
            throw ThreadException("mutext unlock failed");
        }
        fmt::print("mutext unlocked\n");
    }

    friend class ConditionVariable;

private:
    pthread_mutex_t m_mutex;

    // 禁止拷贝
    Mutex(Mutex&) = delete;
    Mutex& operator=(const Mutex&) = delete;

};

class LockGuard {
public:

    explicit LockGuard(Mutex &mt) : m_mutex(mt) {
        m_mutex.lock();
    }
    ~LockGuard() {
        m_mutex.unlock();
    }

private:
    // LockGuard 不应拥有 Mutex 的所有权，只是管理其生命周期
    Mutex &m_mutex;
    LockGuard(const LockGuard&) = delete;
    LockGuard& operator=(const LockGuard&) = delete;
};

#endif