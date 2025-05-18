#ifndef TRAITS_H
#define TRAITS_H

#include "fmt/core.h"
#include <type_traits>

template<typename T>
struct PrintT {

    static void print() {
        fmt::print("this is a value.\n");
    }
    
};

template<typename T>
struct PrintT<T*>
{
    static void print() {
        fmt::print("this is a pointer.\n");
    }
};

template<typename T>
void Print() {
    PrintT<T>::print();
}

// ​​类型判断​​：检测类型特征
template<typename T>
struct is_pointer
{
    static const bool value = false;
};

template<typename T>
struct is_pointer<T*>
{
    static const bool value = true;
};

// 类型转换​​：添加/移除类型修饰符
template<typename T>
struct remove_const
{
    using type = T;
};

template<typename T>
struct remove_const<const T>
{
    using type = T;
};

// 类型关系​​：判断类型间关系
template<typename Base, typename Derived>
struct is_base_of
{
    static inline const bool value = __is_base_of(Base, Derived);
};



#endif