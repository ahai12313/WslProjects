#ifndef TC_H
#define TC_H

#include <vector>
#include <iostream>

template<class T>
class Stack {
public:
    void Push(T a) {
        vec_.push_back(a);
    }

    void Pop() {
        vec_.pop_back();
    }

    T Top() {
        return vec_.back();
    }

    void Watch() {
        for (auto it = vec_.rbegin(); it != vec_.rend(); it++) {
            std::cout << *it << "\n";
        }
    }


private:
    std::vector<T> vec_;
};

#endif