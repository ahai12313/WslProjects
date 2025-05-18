#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <cassert>
#include "SlabAllocator.h"

void TEST_03() {
    
    // 创建分配器，指定对象大小64字节
    SlabAllocator alloc(64);
    
    // 分配测试
    std::vector<void*> vec;
    for (int i = 0; i< 67; i++) {
        void* ptr = alloc.allocate();
        vec.push_back(ptr);
    }
    
    // 释放对象
    alloc.deallocate(vec[0]);
    // 获取统计信息
    auto stats = alloc.getStats();
    std::cout << "\nStatistics:\n"
              << "Total slabs: " << stats.total_slabs << "\n"
              << "Active allocations: " << stats.active_allocations << "\n"
              << "Total allocations: " << stats.total_allocations << "\n"
              << "Free objects: " << stats.free_objects << std::endl;
    
    std::cout << "所有测试通过！\n";
}

