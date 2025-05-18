#include "fmt/core.h"
#include "Thread.h"
#include "ThreadException.h"
#include "Mutex.h"
#include "ConditionVariable.h"

namespace
{

} 

void TEST01()
{
    {
        // 异常类​
        fmt::print("异常类​\n");
        try {
            throw ThreadException("线程错误1");
        } catch(const ThreadException &e) {
            fmt::print("{}\n", e.what());
        }
        
    }

    {
        // 互斥锁（Mutex）​
        fmt::print("互斥锁\n");
        Mutex mutex;
        mutex.lock();
        mutex.unlock();
    }

    {
        // 锁守卫
        fmt::print("锁守卫\n");
        Mutex mutex;
        LockGuard lock_guard(mutex);
    }

    {
        // 条件变量
        fmt::print("条件变量\n");
        ConditionVariable cv;
    }

    {
        // 线程基类​
        fmt::print("线程基类​\n");
        // Thread t;
    }
}
