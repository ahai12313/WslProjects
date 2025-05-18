#ifndef TR_H
#define TR_H

#include <iostream>

namespace tr
{
    template <typename T>
    void print(T t)
    {
        if constexpr (std::is_pointer_v<T>) {
            std::cout << *t << std::endl;
        } else {
            std::cout << t << std::endl;
        }
        
    };
}

#endif