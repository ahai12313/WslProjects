#include "Exercise.h"
#include "fmt/core.h"
#include <unistd.h>

void TEST02() {
    {
        CounterThread t1, t2;
        try
        {
            t1.start();
            t2.start();

            t1.join();
            t2.join();
        }
        catch(const ThreadException& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
}