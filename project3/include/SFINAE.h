#ifndef SF_H
#define SF_H

#include <iostream>

namespace sf
{
    template <typename T>
    auto print(T value) -> decltype(std::cout << value, void())
    {
        std::cout << value << "\n";
    }

    void print(...)
    {
        std::cout << "[unprintable]" << "\n";
    }
}

namespace sf1
{
    template <typename T, typename = void>
    struct has_size_member : std::false_type
    {
    };

    template <typename T>
    struct has_size_member<T, std::void_t<decltype(std::declval<T>().size())>> : std::true_type
    {
    };
}

namespace sf2
{
    template <typename T>
    auto print_if_integer(T v) -> std::enable_if_t<std::is_integral_v<T>>
    {
        std::cout << v << std::endl;
    }
}

namespace sf3
{

    template <typename T, typename V>
    auto safe_divide(T t, V v) -> std::enable_if_t<
        std::is_arithmetic_v<T> && 
        std::is_arithmetic_v<V>, 
        std::common_type_t<T, V>>
    {
        // static_assert(!std::is_same_v<V, decltype(v+0)>, "除数为0禁止编译");
        return t / v;
    }
}

#endif