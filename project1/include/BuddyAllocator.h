#ifndef BA_H
#define BA_H

#include <cstddef>
#include <vector>
#include <list>
#include <unordered_map>
#include <cmath>
#include <stdexcept>
#include "fmt/core.h"

class BuddyAllocator
{

public:
    explicit BuddyAllocator(size_t max_order) : max_order(max_order), min_order(3)
    {
        freeList.resize(max_order + 1);
        size_t total_size = (1ULL << max_order);
        memoryPool = aligned_alloc(total_size, total_size);
        freeList[max_order].emplace_back(memoryPool, total_size);
    }

    ~BuddyAllocator()
    {
        free(memoryPool);
    }

    void *allocate(size_t size)
    {
        if (size == 0)
            return nullptr;

        size_t req_ord = calculate_order(size);
        if (req_ord > max_order)
            return nullptr;

        size_t found_order = req_ord;
        while (found_order <= max_order && freeList[found_order].empty())
        {
            found_order++;
        }
        if (found_order > max_order)
            return nullptr;

        BuddyBlock block = freeList[found_order].front();
        freeList[found_order].pop_front();

        while (found_order > req_ord)
        {
            --found_order;
            void *buddy_addr = get_buddy_addr(block.addr, found_order);
            freeList[found_order].emplace_back(buddy_addr, found_order);
            freeList[found_order].emplace_back(block.addr, found_order);
            block = freeList[found_order].front();
            freeList[found_order].pop_front();
        }

        usedBlock[block.addr] = block.order;
        return block.addr;
    }

    void *deallocate(void *ptr)
    {
        auto it = usedBlock.find(ptr);
        if (it == usedBlock.end())
        {
            throw std::invalid_argument("invalid deallocate");
        }

        size_t order = it->second;
        usedBlock.erase(it);

        void *current_addr = ptr;
        while (order < max_order)
        {
            void *buddy_addr = get_buddy_addr(current_addr, order);
            bool merged = false;

            auto &list = freeList[order];
            for (auto it = list.begin(); it != list.end(); ++it)
            {
                if (it->addr == buddy_addr)
                {
                    list.erase(it);
                    merged = true;
                    break;
                }
            }

            if (!merged)
                break;

            current_addr = std::min(current_addr, buddy_addr);
            ++order;
        }

        freeList[order].emplace_back(current_addr, order);
    }

    void debug_print() const
    {
        for (size_t i = 0; i <= max_order; ++i)
        {
            fmt::print("Order {} ({} bytes): {} freeblocks\n", i, (1ULL << i), freeList[i].size());
        }
    }

private:
    struct BuddyBlock
    {
        void *addr;
        size_t order;
        BuddyBlock(void *a, size_t o) : addr(a), order(o) {}
    };

    size_t max_order;
    size_t min_order;
    void *memoryPool;
    std::vector<std::list<BuddyBlock>> freeList;
    std::unordered_map<void *, size_t> usedBlock;

    size_t calculate_order(size_t size) const
    {
        size_t min_size = 1ULL << min_order;
        size_t adjust_size = std::max(min_size, size);
        return static_cast<size_t>(std::ceil(std::log2(adjust_size)));
    }

    void *get_buddy_addr(void *addr, size_t order) const
    {
        auto offset = static_cast<size_t>(static_cast<std::byte *>(addr) - static_cast<std::byte *>(memoryPool));
        size_t buddy_offset = (1ULL << order) ^ offset;
        return static_cast<std::byte *>(memoryPool) + buddy_offset;
    }
};

#endif