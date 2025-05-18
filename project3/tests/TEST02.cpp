#include "TemplateClass.h"
#include "fmt/core.h"
#include <string>

void TEST02() {
    {
        Stack<int> iStack;
        iStack.Push(2);
        iStack.Push(4);
        iStack.Push(1);
        iStack.Watch();
    }

    {
        using std::string;
        Stack<string> sStack;
        sStack.Push("Wed");
        sStack.Push("Oct");
        sStack.Push("Nov");
        sStack.Pop();
        sStack.Push("Dec");
        sStack.Watch();
    }

}