#include "TypeList.h"
#include "fmt/core.h"

template <typename T>
struct AddPointer {
    using type = T*;
};

void TEST01() {
    {
        TypeList<int, float> tl;
        fmt::print("列表长度 {}\n", tl.size());
    }

    {
        TypeList<> tl;
        fmt::print("包含float? {}\n", Contains<TypeList<>, float>::value);

        TypeList<int, float> tl2;
        fmt::print("包含float? {}\n", Contains<TypeList<int, float>, int>::value);

        TypeList<int, int> tl3;
        fmt::print("包含float? {}\n", Contains<decltype(tl3), float>::value);
    }

    {
        TypeList<int, float> tl;
        using filterTypeList = Filter<decltype(tl), std::is_integral>::type;
    }

    {
        // 定义映射器：将类型转换为指针
        using OriginalList = TypeList<int, float, std::string>;
        using TransformedList = Transform<OriginalList, AddPointer>::type;
        // TransformedList = TypeList<int*, float*, std::string*>
    }

    {
        using tl1 = TypeList<int, float>;
        using tl2 = TypeList<long, double>;
        using tmerged = Concat<tl1, tl2>;
    }

    {
        fmt::print("{}\n", TypeListToString<TypeList<int, float>>().value());
        fmt::print("{}\n", TypeListToString<TypeList<double, long, std::string>>().value());
        fmt::print("{}\n", TypeListToString<TypeList<>>().value());
    }
}
