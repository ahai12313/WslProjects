#include "MutableArgs.h"

void printAll() {
    std::cout << std::endl;
}

template<class T, typename... Args>
void printAll(T first, Args... args) {
    std::cout << first << " ";
    printAll(args...);
}

void TEST04() {
    printArgs<int, float>(std::cout , 1, 2.3);
    printAll(1, 2.3);
}