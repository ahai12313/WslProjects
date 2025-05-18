#ifndef MPS_H
#define MPS_H

#include <cstddef>
#include <memory>

struct MemoryBlock
{
    struct MemoryBlock *next;
};

template <typename T>
class FixedMemoryPool
{
public:
    explicit FixedMemoryPool(size_t bn)
        : blockSize(CalBlockSize()),
          blockNum(bn),
          memoryStart(std::make_unique<std::byte[]>(blockSize * bn)),
          freeList(InitFreeList())

    {
    }

    FixedMemoryPool(const FixedMemoryPool &) = delete;
    FixedMemoryPool &operator=(const FixedMemoryPool &) = delete;

    T *Allocate()
    {
        if (!freeList)
        {
            throw std::bad_alloc();
        }

        MemoryBlock *block = freeList;
        freeList = freeList->next;

        return reinterpret_cast<T *>(
            reinterpret_cast<std::byte *>(block) + (blockSize - sizeof(T)));
    }

    void Deallocate(T *ptr)
    {
        auto *block = reinterpret_cast<MemoryBlock *>(
            reinterpret_cast<std::byte *>(ptr) - (blockSize - sizeof(T)));

        block->next = freeList;
        freeList = block;
    }

private:
    static constexpr size_t CalBlockSize()
    {
        constexpr size_t metaSize = sizeof(MemoryBlock);
        constexpr size_t dataSize = sizeof(T);
        constexpr size_t align = std::alignment_of_v<T>;
        return ((metaSize + align - 1) & ~(align - 1)) + dataSize;
    }

    MemoryBlock *InitFreeList()
    {
        std::byte *raw = memoryStart.get();
        MemoryBlock *head = nullptr;

        for (size_t i = 0; i < blockNum; i++)
        {
            auto *current = reinterpret_cast<MemoryBlock *>(raw + i * blockSize);
            current->next = head;
            head = current;
        }

        return head;
    }

    size_t blockSize;
    size_t blockNum;
    std::unique_ptr<std::byte[]> memoryStart;
    MemoryBlock *freeList;
};

#endif