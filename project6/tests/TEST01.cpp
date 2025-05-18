#include <stdexcept>
#include <cstdlib>
#include <memory>
#include "Valgrind.h"
#include "fmt/core.h"

namespace
{
    void f() {
        new int(3);
        return;
    }

    void risky_operation() {
        int *arr = new int[50];
        throw std::runtime_error("Error");
        delete[] arr;
    }

    class A {
        public:
        std::shared_ptr<A> next;
    };
} 



void TEST01()
{
    {
        // 未释放动态分配的内存​
        fmt::print("未释放动态分配的内存​\n");
        int *p = new int(4);
        delete (p);
    }

    {
        // 提前返回导致未释放内存
        fmt::print("提前返回导致未释放内存\n");
        auto f = [](int a)
        { return a + *(new int(3)); };
        fmt::print("{}\n", f(1));

        ::f();
    }

    {
        // 异常导致未释放内存
        fmt::print("异常导致未释放内存\n");
        try {
            risky_operation();
        } catch(...) {
            fmt::print("catched\n");
        }

    }

    {
        // 二维数组未完全释放​
        fmt::print("二维数组未完全释放​\n");
        int** matrix = (int**)malloc(3 * sizeof(int*));
        for (int i = 0; i < 3; i++) {
            matrix[i] = (int *)malloc(5 * sizeof(int));
        }
        free(matrix);
    }

    {
        // 循环引用导致智能指针泄漏
        fmt::print("循环引用导致智能指针泄漏\n");
        std::shared_ptr<A> p1 = std::make_shared<A>();
        std::shared_ptr<A> p2 = std::make_shared<A>();
        p1->next = p2;
        p2->next = p1;
    }
}
