#ifndef SHAREPTR_H
#define SHAREPTR_H

#include <cstddef>
#include <atomic>
#include <utility>
#include "fmt/color.h"

template<typename T>
class SharedPtr {
public:
    SharedPtr() {
        fmt::print("default construct.\n");
    }
    explicit SharedPtr(T* raw_ptr): ptr(raw_ptr), ref_cnt(new std::atomic<size_t>(1)) {
        fmt::print("raw ptr construct.\n");
    }
    SharedPtr(const SharedPtr& other): ptr(other.ptr), ref_cnt(other.ref_cnt) {
        fmt::print("copy construct.\n");
        if (ref_cnt) ref_cnt->fetch_add(1, std::memory_order_relaxed);
    }
    SharedPtr(SharedPtr&& other) noexcept
        : ptr(std::exchange(other.ptr, nullptr)), ref_cnt(std::exchange(other.ref_cnt, nullptr)) {
        fmt::print("move construct.\n");
    }
    SharedPtr& operator=(SharedPtr& other) {
        fmt::print("copy assign.\n");
        if (this != &other) {
            release();
            this->ptr = other.ptr;
            this->ref_cnt = other.ref_cnt;
            if (ref_cnt) ref_cnt->fetch_add(1, std::memory_order_relaxed);
        }
        return *this;
    }
    SharedPtr& operator=(SharedPtr&& other) {
        fmt::print("move assign.\n");
        if (this != &other) {
            release();
            ptr = std::exchange(other.ptr, nullptr);
            ref_cnt = std::exchange(other.ref_cnt, nullptr);
        }
        return *this;
    }

    ~SharedPtr() {
        fmt::print("destruct.\n");
        release();
    }

    void Count() {
        fmt::print("ref cnt {}\n", ref_cnt ? ref_cnt->load() : 0);
    }

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

    T* get() const {
        return ptr;
    }

    size_t use_cnt() const {
        return ref_cnt ? ref_cnt->load() : 0;
    }

private:
    void release() {
        if (ref_cnt) {
            if ((ref_cnt->fetch_sub(1, std::memory_order_acq_rel)) == 1) {
                delete ptr;
                delete ref_cnt;
            }
        }
    }

    T* ptr = nullptr;
    std::atomic<size_t> *ref_cnt = nullptr;

};

#endif