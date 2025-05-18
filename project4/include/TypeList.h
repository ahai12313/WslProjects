#ifndef TYPELIST_H
#define TYPELIST_H

#include <string>
#include <cstddef>
#include <type_traits>
#include <typeinfo>

// 1. 基础类型列表定义

template <typename... Ts>
class TypeList
{
public:
    size_t size() const
    {
        return size_;
    }

private:
    static constexpr size_t size_ = sizeof...(Ts);
};

// 2. 类型存在性检查（Contains）

template <typename List, typename T>
struct Contains : std::false_type {};

template<typename Head, typename... Tail, typename T>
struct Contains<TypeList<Head, Tail...>, T> : 
    std::conditional_t<
        std::is_same_v<Head, T>,
        std::true_type,
        Contains<TypeList<Tail...>, T>                    
    > 
{};

template<typename T>
struct Contains<TypeList<>, T> : std::false_type
{};

// 3. 类型过滤（Filter）
template<typename Acc, template <typename> class Pred, typename...>
struct FilterHelper;

template<typename Acc, template <typename> class Pred>
struct FilterHelper<Acc, Pred>
{
    using type = Acc;
};

template<typename... Acc, template <typename> class Pred, typename T, typename... Ts>
struct FilterHelper<TypeList<Acc...>, Pred, T, Ts...>
{
    using type = std::conditional_t<
        Pred<T>::value,
        typename FilterHelper<TypeList<Acc..., T>, Pred, Ts...>::type,
        typename FilterHelper<TypeList<Acc...>, Pred, Ts...>::type
    >;
};

template<typename List, template <typename> class Pred>
struct Filter;

template<template <typename...> class List, typename... Ts, template <typename> class Pred>
struct Filter<List<Ts...>, Pred>
{
    using type = typename FilterHelper<TypeList<>, Pred, Ts...>::type;
};

// 4. 类型转换（Transform）
template<typename InputList, template <typename> class Mapper, typename... Results>
struct TransformHelper;

template<template <typename> class Mapper, typename... Results>
struct TransformHelper<TypeList<>, Mapper, Results...>
{
    using type = TypeList<Results...>;
};

template<typename T, typename... Ts, template <typename> class Mapper, typename... Results>
struct TransformHelper<TypeList<T, Ts...>, Mapper, Results...>
{
    using MappedT = typename Mapper<T>::type;
    using type = typename TransformHelper<
        TypeList<Ts...>,
        Mapper,
        Results...,
        MappedT
    >::type;
};

template<typename List, template <typename> class Mapper>
struct Transform;

template<template <typename> class List, template <typename> class Mapper, typename... Ts>
struct Transform<List<Ts...>, Mapper> {
    using type = typename TransformHelper<TypeList<Ts...>, Mapper>::type;
};

// 5. 类型列表连接（Concat）
template<typename List1, typename List2>
struct Concat;

template<template <typename> class List1, typename... T1s,
        template <typename> class List2, typename... T2s>
struct Concat<List1<T1s...>, List2<T2s...>>
{
    using type = TypeList<T1s..., T2s...>;
};

// 6. 运行时类型名称生成（Debug）
template<typename List>
struct TypeListToString;

template <template <typename...> class List>
struct TypeListToString<List<>> {
    static std::string value() { return "TypeList<>"; }
};

// template<template <typename...> class List, typename... Ts>
// struct TypeListToString<List<Ts...>>
// {
//     static std::string value() {
//         std::string result = "TypeList<";
//         ((result += typeid(Ts).name() + std::string(", ")), ...);
//         if constexpr (sizeof...(Ts) > 0) result.erase(result.size()-2, 2);
//         return result += ">";
//     }
// };
template<typename List>
struct TypeListToStringHelper;

// 处理空列表
template<template <typename...> class List>
struct TypeListToStringHelper<List<>> {
    static std::string value() {
        return "";
    }
};

// 处理非空列表
template<template <typename...> class List, typename T, typename... Ts>
struct TypeListToStringHelper<List<T, Ts...>> {
private:
    static std::string processTail() {
        if constexpr (sizeof...(Ts) == 0) {
            return "";
        } else {
            return ", " + TypeListToStringHelper<List<Ts...>>::value();
        }
    }

public:
    static std::string value() {
        std::string head = typeid(T).name();
        return head + processTail();
    }
};


template<template <typename...> class List, typename T, typename... Ts>
struct TypeListToString<List<T, Ts...>>
{

    static std::string getTail() {
        if constexpr (sizeof...(Ts) == 0) {
            return "";
        } else {
            return ", " + TypeListToStringHelper<List<Ts...>>::value();
        }
    }

    static std::string value() {
        std::string head = typeid(T).name();
        return "TypeList<" + head + getTail() + ">";
    }


};

#endif