#ifndef MA_H
#define MA_H

#include <iostream>

// 基例：无参数时终止递归
void printArgs(std::ostream& os) {
    os << "\n";
}

// template<class... Args>
// void printArgs(Args... args) {
//     // 折叠表达式
//     bool isFirst = true;
//     ((std::cout << (isFirst ? (isFirst = false, "") : " ") << args), ...);
//     std::cout << std::endl;
// }
template<typename T, typename ... Args>
void printArgs(std::ostream& os, const T &firts, const Args&... rest) {
    os << firts;
    if (sizeof...(rest) > 0) {
        os << " ";
    }
    printArgs(os, rest...);
}

#endif