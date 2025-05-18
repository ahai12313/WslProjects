#include <cstddef>
#include <functional>
#include <mutex>
#include <stdexcept>
#include <iostream>

class SlabAllocator
{
public:
    using Constructor = std::function<void(void *)>;
    using Destructor = std::function<void(void *)>;

    SlabAllocator(size_t obj_size, size_t slab_size = 4096,
                  Constructor ctor = nullptr,
                  Destructor dtor = nullptr)
        : obj_size_(std::max(obj_size, sizeof(FreeListNode))),
          slab_size_(slab_size),
          constructor_(ctor),
          destructor_(dtor),
          partial_(nullptr),
          full_(nullptr),
          free_list_(nullptr)
    {
        if (obj_size < sizeof(FreeListNode))
        {
            throw std::logic_error("object size less than freelistnode.");
        }
    }

    ~SlabAllocator()
    {
        releaseSlabList(partial_);
        releaseSlabList(full_);
    }

    void *allocate()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!free_list_)
        {
            if (!grow_memory())
            {
                return nullptr;
            }
        }

        FreeListNode *node = free_list_;
        free_list_ = free_list_->next;

        SlabHeader *slab = node->slab;
        slab->used_objects++;
        total_allocations_++;
        active_allocations_++;

        if (slab->used_objects == slab->total_objects)
        {
            moveSlab(&partial_, &full_, slab);
        }

        if (constructor_)
        {
            constructor_(node);
        }

        return node;
    }

    void deallocate(void *ptr)
    {
        if (!ptr)
            throw std::runtime_error("no obj.");

        std::lock_guard<std::mutex> lock(mutex_);

        if (destructor_)
        {
            destructor_(ptr);
        }

        // 转换为空节点
        FreeListNode *node = static_cast<FreeListNode *>(ptr);
        node->next = free_list_;
        free_list_ = node;

        // 更新slab状态
        SlabHeader *slab = free_list_->slab;
        slab->used_objects--;
        active_allocations_--;

        if (slab->used_objects == slab->total_objects - 1)
        {
            moveSlab(&full_, &partial_, slab);
        }

        if (slab->used_objects == 0)
        {
            releaseEmptySlab();
        }
    }

    // 统计信息
    struct Statistics
    {
        size_t total_slabs;
        size_t active_allocations;
        size_t total_allocations;
        size_t free_objects;
    };

    Statistics getStats() const
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return {
            countSlabs(partial_) + countSlabs(full_),
            active_allocations_,
            total_allocations_,
            countFreeObj()};
    }

private:
    struct SlabHeader
    {
        int used_objects;
        int total_objects;
        SlabHeader *next;
    };

    struct FreeListNode
    {
        FreeListNode *next;
        SlabHeader *slab;
    };

    // 内存增长
    bool grow_memory()
    {
        void *memory = ::malloc(slab_size_);
        if (!memory)
            return false;
        // 初始化Slab头
        SlabHeader *header = new (memory) SlabHeader{
            0,
            static_cast<int>((slab_size_ - sizeof(SlabHeader)) / obj_size_),
            partial_};

        // 初始化空闲链表
        char *current = reinterpret_cast<char *>(memory) + sizeof(SlabHeader);
        for (int i = 0; i < header->total_objects; i++)
        {
            FreeListNode *node = new (current) FreeListNode{free_list_};
            node->slab = header;
            free_list_ = node;
            current += obj_size_;
        }
        free_list_->slab = header;
        partial_ = header;
        return true;
    }

    void releaseSlabList(SlabHeader *head)
    {
        while (head)
        {
            SlabHeader *next = head->next;
            ::free(head);
            head = next;
        }
    }

    void moveSlab(SlabHeader **from, SlabHeader **to, SlabHeader *slab)
    {
        SlabHeader **cur = from;
        while (*cur != slab)
        {
            cur = &(*cur)->next;
        }
        *cur = slab->next;

        slab->next = *to;
        *to = slab;
    }

    // 释放完全空闲的Slab
    void releaseEmptySlab()
    {
        SlabHeader **cur = &partial_;
        while (*cur)
        {
            if ((*cur)->used_objects == 0)
            {
                SlabHeader *empty = *cur;
                *cur = empty->next;
                ::free(empty);
            }
            else
            {
                cur = &(*cur)->next;
            }
        }
    }

    // 统计辅助函数
    size_t countSlabs(const SlabHeader *head) const
    {
        size_t count = 0;

        while (head)
        {
            ++count;
            head = head->next;
        }

        return count;
    }

    size_t countFreeObj() const
    {
        size_t count = 0;
        FreeListNode *node = free_list_;
        while (node)
        {
            ++count;
            node = node->next;
        }
        return count;
    }

    const size_t obj_size_;
    const size_t slab_size_;

    Constructor constructor_;
    Destructor destructor_;

    SlabHeader *partial_;
    SlabHeader *full_;
    FreeListNode *free_list_;

    size_t total_allocations_ = 0;
    size_t active_allocations_ = 0;

    mutable std::mutex mutex_;
};
