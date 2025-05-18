#include "TemplateFunc.h"
#include "TemplateClass.h"
#include "fmt/core.h"

void TEST01() {

    {
        int a = 1;
        int b = 2;
        swap<int>(a, b);
        fmt::print("{} {} \n", a, b);
    }

    {
        float a = 2.1;
        float b = 3.3;
        swap<float>(a, b);
        fmt::print("{} {} \n", a, b);
    }
    

}