#include "Exercise.h"
#include "fmt/core.h"
inline void ff() {};
void TEST02() {
    {
        fmt::print("{}\n", is_void_v<void>);
    }

    {
        int a = 1;
        add_pointer<int&&>::type p = &a;
        fmt::print("{}\n", *p);
    }

    {
        fmt::print("is_same<int, int&>::value {}\n", is_same<int, int&>::value);
        fmt::print("is_same_v {}\n", is_same_v<int, int>);

    }

    {
        fmt::print("is_stl_container_v {}\n", is_stl_container_v<std::vector<int>>);
    }

    {
        fmt::print("remove_all_pointers<T>::type {}\n", typeid(remove_all_pointers<int**>::type).name());
    }

    {
        auto f = [](){};
        
        fmt::print("is callable {}\n", is_callable<decltype(ff())>::value);
    }
}