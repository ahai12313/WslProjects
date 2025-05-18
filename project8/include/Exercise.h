#ifndef EXERCISE_H
#define EXERCISE_H

#include "fmt/core.h"
#include "Thread.h"
#include "Mutex.h"
#include "unistd.h"

class CounterThread : public Thread {
protected:
    void run() override {
        static Mutex mutex;
        for (auto i = 0; i < 3 ; i++) {
            {
                LockGuard lock(mutex);
                fmt::print("Thread {} count {}\n", pthread_self(), i);
            }
            sleep(1);
        }
    }
};

#endif