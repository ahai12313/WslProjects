#ifndef CONDITION_VARIABLE_H
#define CONDITION_VARIABLE_H

#include "pthread.h"
#include "Mutex.h"
#include "ThreadException.h"

class ConditionVariable {
public:
    ConditionVariable() {
        if (pthread_cond_init(&m_cv, nullptr) != 0) {
            throw ThreadException("condition variable init failed");
        }
    }
    ~ConditionVariable() {
        pthread_cond_destroy(&m_cv);
    }

    void wait(Mutex& mutex) {
        if (pthread_cond_wait(&m_cv, &mutex.m_mutex) != 0) {
            throw ThreadException("Condition wait failed");
        }
    }

    void notify_one() {
        if (pthread_cond_signal(&m_cv) != 0) {
            throw ThreadException("Condition notify one failed");
        }
    }

    void notify_all() {
        if (pthread_cond_broadcast(&m_cv) != 0) {
            throw ThreadException("Condition notify all failed");
        }
    }


private:
    pthread_cond_t m_cv;
    ConditionVariable(ConditionVariable&) = delete;
    ConditionVariable& operator=(ConditionVariable&) = delete;

};

#endif