#include "SharedPtr.h"
#include "fmt/core.h"
#include <iostream>

class A {
    public:
    int a = 1;
};
void TEST02() {

    {
        int a = 1;
        int *p = new int(2);
        delete p;
        std::cout << *p << "\n";
    }

    {
        // 核心组件：原始指针、引用计数器、释放资源函数
        fmt::print("核心组件\n");
        SharedPtr<int> sp;
    }

    {
        // 拷贝构造函数
        fmt::print("拷贝构造函数\n");
        SharedPtr<int> sp;
        SharedPtr<int> sp1(sp);
        SharedPtr<int> sp3(new int(1));
        SharedPtr<int> sp5(sp3);
        auto sp6 = std::move(sp5);
    }

    {
        // 赋值构造函数
        fmt::print("赋值构造函数\n");
        SharedPtr<int> sp1(new int(2));
        SharedPtr<int> sp2;
        sp2 = sp1;
        sp2.Count();
        sp1 = std::move(sp2);
        sp1.Count();
    }

    {
        // 解引用运算符
        fmt::print("解引用运算符\n");
        SharedPtr<int> sp1(new int(2));
        fmt::print("{}\n", *sp1);
    }

    {
        // 指针运算符
        fmt::print("指针运算符\n");
        SharedPtr<A> sp1(new A());
        fmt::print("{}\n", sp1->a);
    }

    {
        // get()接口
        fmt::print("get()接口\n");
        SharedPtr<int> sp1(new int(2));
        int *p = sp1.get();
        fmt::print("{}\n", *p);
    }

    {
        // 获取引用计数
        fmt::print("获取引用计数\n");
        SharedPtr<int> sp1;
        SharedPtr<int> sp2(new int(3));
        fmt::print("{}\n", sp1.use_cnt());
        fmt::print("{}\n", sp2.use_cnt());
    }


}