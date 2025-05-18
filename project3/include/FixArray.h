#ifndef FA_H
#define FA_H

// 非类型模板参数
// 默认模板参数
template<class T = int, int N = 5>
class FixArray {
    T a[N];

public:
    T& operator[](int n) {
        return a[n];
    }
};

template<int N>
class FixArray<const char*, N> {
    const char* a[N]{"Jan", "Feb", "Mar", "Apr", "May"};
public:
    void printItself() {
        for (int i = 0; i < N; i++) {
            std::cout << a[i] << " ";
        }
        std::cout << std::endl;
    }
    const char* operator[](int n) {
        return a[n];
    }

};




#endif