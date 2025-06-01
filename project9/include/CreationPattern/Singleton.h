#ifndef SINGLETON_H
#define SINGLETON_H

class Singleton {
public:
    // 0、饿汉模式（类加载时就初始化）
    // 1、删除拷贝构造和拷贝赋值
    // 2、实例必须在类外初始化 Singleton Singleton::instance(3);
    // 3、通过引用方式创建实例 Singleton& ins = Singleton::getInstance();
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton& getInstance() {
        return instance;
    }

    Singleton(int v): val(v) {}

    int val = 1;

private:
    static Singleton instance;
    Singleton() = default;
};

Singleton Singleton::instance(2);

class Singleton2 {
public:
    Singleton2(Singleton2&) = delete;
    Singleton2& operator=(Singleton2&) = delete;
    static Singleton2& getInstance() {
        static Singleton2 instance;
        return instance;
    }
    int val;

private:
    Singleton2() = default;

};



#endif