#include "BuddyAllocator.h"
#include <iostream>

void TEST_02() {
    BuddyAllocator allocator(10); // 1KB内存池（2^10=1024字节）

    // 测试分配
    void* p1 = allocator.allocate(60);  // 需要64字节（order=6）
    void* p2 = allocator.allocate(128); // 需要128字节（order=7）
    std::cout << "After allocation:\n";
    allocator.debug_print();

    // 测试释放
    allocator.deallocate(p1);
    allocator.deallocate(p2);
    std::cout << "\nAfter deallocation:\n";
    allocator.debug_print();

    // 测试内存合并
    void* p3 = allocator.allocate(8);   // order=3
    void* p4 = allocator.allocate(8);   // order=3
    std::cout << "\nBefore merging:\n";
    allocator.debug_print();
    
    allocator.deallocate(p3);
    allocator.deallocate(p4);
    std::cout << "\nAfter merging:\n";
    allocator.debug_print();

}