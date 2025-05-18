#include "FixArray.h"
#include <iostream>


void TEST03() {
    {
        // 非类型模板参数
        // 默认模板参数
        FixArray<int, 5> fa;
        fa[2] = 1;
        for (int i = 0; i < 5; i++) {
            std::cout << fa[i] << " ";
        }
        std::cout << "\n";
    }

    {
        FixArray<const char*, 5> fa;
        fa.printItself();
    }
}