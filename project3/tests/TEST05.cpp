#include "SFINAE.h"

template <class T, typename = void>
struct has_size_number : std::false_type
{
};

void TEST05()
{
    {
#ifdef SF
        class A
        {
            int a;
        };
        sf::print(1);
        sf::print(2.3);
        sf::print("abc");
        sf::print(A());
#endif
    }

    {
        #ifdef SF1
        struct A
        {
            int size()
            {
                return 5;
            }
        };

        struct B
        {
        };

        static_assert(sf1::has_size_member<A>::value, "应有size成员");
        static_assert(!sf1::has_size_member<B>::value, "不应有size成员");
        static_assert(!sf1::has_size_member<int>::value, "基本类型不应有size");
        #endif
    }

    {
        #ifdef SF2
        sf2::print_if_integer(42);    // 应编译通过
        sf2::print_if_integer(3.14);  // 应导致编译错误
        sf2::print_if_integer("hello"); // 应导致编译错误
        #endif
    }

    {
        #define SF3
        #ifdef SF3
        auto c = sf3::safe_divide(3.2, 1); 
        std::cout << c << "\n";
        #endif
    }
}
