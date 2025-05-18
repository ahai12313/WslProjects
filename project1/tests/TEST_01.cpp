#include "MemoryPoolStruct.h"

#include <fmt/core.h>

class A {
public:
    int a1;
    double a2;
};

//固定内存池基本用法
void TEST_01() {
    FixedMemoryPool<A> fmp(100);

    A* o1 = fmp.Allocate();
    o1->a1 = 1;
    o1->a2 = 2.2;

    fmt::print("o1->a1 {}\n", o1->a1);
    fmt::print("o1->a2 {}\n", o1->a2);

    fmp.Deallocate(o1);

}