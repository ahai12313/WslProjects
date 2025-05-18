#include "UniqPtr.cpp"
#include <iostream>
#include <memory>
#include <string>
#include "fmt/core.h"

void TEST01() {

    {  
        // 栈对象
        fmt::print("栈对象\n");
        int a = 2;
        // ah::UniqPtr<int> ptr(&a);
        // fmt::print("{}\n", *ptr);
    }

    {
        // 堆对象
        fmt::print("堆对象\n");
        ah::UniqPtr<int> ptr(new int(2));
        fmt::print("{}\n", *ptr);
    }

    {
        // 删除拷贝及赋值构造
        fmt::print("删除拷贝及赋值构造\n");
        // ah::UniqPtr<int> ptr1(new int(1));
        // ah::UniqPtr<int> ptr2(ptr1);
        // ah::UniqPtr<int> ptr3 = ptr1;
    }

    {
        // 移动语义
        fmt::print("移动语义\n");
        ah::UniqPtr<int> p1(new int(2));
        auto p2 = std::move(p1);
        fmt::print("{}\n", *p2);
        auto p3(std::move(p2));
        fmt::print("{}\n", *p3);
        // fmt::print("{}\n", *p1);
    }

    {
        // 访问接口
        fmt::print("访问接口\n");
        
        struct Student
        {
            int age;
            std::string name;
            Student(int a, std::string n): age(a), name(n) {}
        };

        ah::UniqPtr<Student> p(new Student(3, "xiaolu"));
        p->age = 6;
        fmt::print("name {}\n", p->name);
        fmt::print("age {}\n", (*p).age);
        
        auto pp = p.get();
        std::cout << pp << "\n";

    }
    
    {
        // 资源管理
        fmt::print("资源管理\n");
        ah::UniqPtr ptr(new int(2));
        auto p = ptr.release();
        fmt::print("{}\n", *p);
        ah::UniqPtr<int> ptr1(p);
        fmt::print("{}\n", *ptr1);
        int* a = new int(3);
        ptr1.reset(a);
        fmt::print("{}\n", *ptr1);

    }

    {
        // 数组操作
        fmt::print("数组操作\n");
        // auto arr = new int[5]{1, 2, 3, 4, 5};
        
        ah::UniqPtr<int[]> arr(new int[5]{1, 2, 3, 4, 5});
        fmt::print("{}\n", arr[0]);
        arr[2] = 4;
    }

}