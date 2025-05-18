#include "Traits.h"
#include "fmt/core.h"

class A {};

class B : A {};

void TEST01() {
    {
        Print<int>();
        Print<int*>();
    }

    {
        remove_const<const int>::type a = 1;
        a = 2;
        fmt::print("{}\n", a);

    }

    {
        fmt::print("{}\n", is_base_of<B, A>::value);
    }
}
