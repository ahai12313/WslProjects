#ifndef EXERCISE_H
#define EXERCISE_H

#include <type_traits>
#include <vector>
#include <list>
#include "fmt/core.h"

// 实现 is_void 类型萃取类，判断类型是否为 void
template<typename T>
struct is_void
{
    static constexpr bool value = false;
};

template<>
struct is_void<void>
{
    static constexpr bool value = true;
};

template<typename T>
inline constexpr bool is_void_v = is_void<T>::value;

// 实现 add_pointer 类型萃取类，为任意类型添加指针修饰符
template<typename T>
struct add_pointer
{
    using type = T*;
};

template<typename T>
struct add_pointer<T&>
{
    using type = T*;
};

template<typename T>
struct add_pointer<T&&>
{
    using type = T*;
};

template<typename T>
using add_pointer_t = typename add_pointer<T>::type;

// 实现 is_same 类型萃取类，判断两个类型是否完全相同
template<typename T, typename U>
struct is_same
{
    static constexpr bool value = false;
};

template<typename T>
struct is_same<T, T>
{
    static constexpr bool value = true;
};

template<typename T, typename U>
inline constexpr bool is_same_v = is_same<T, U>::value;

// 实现 is_stl_container 类型萃取，检测类型是否为STL容器（需识别 vector/list 等）
template<typename T>
struct is_stl_container : std::false_type
{
};

template<typename T, typename A>
struct is_stl_container<std::vector<T, A>> : std::true_type
{
    /* data */
};

template<typename T, typename A>
struct is_stl_container<std::list<T, A>> : std::true_type
{
    /* data */
};

template<typename T>
inline constexpr bool is_stl_container_v = is_stl_container<T>::value;


// 实现 remove_all_pointers 类型萃取，递归移除多级指针（如 int**** → int）
template<typename T>
struct remove_all_pointers
{
    using type = T;
};

template<typename T>
struct remove_all_pointers<T*>
{
    using type = typename remove_all_pointers<T>::type;
};

template<typename T>
using remove_all_pointers_t = typename remove_all_pointers<T>::type;


// 实现 is_callable 类型萃取，判断类型是否可调用（函数、函数对象、lambda）
template<typename T, typename = void>
struct is_callable : std::false_type
{
    /* data */
};

template<typename T>
struct is_callable<T, std::void_t<decltype(std::declval<T&>()())>> : std::true_type
{
    /* data */
};

#endif