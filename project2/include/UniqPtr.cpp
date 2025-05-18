#include <utility>
#include <memory>
#include <iostream>

namespace ah
{

    // 辅助模板：根据 T 是否为数组类型选择默认删除器
    template <typename T>
    struct DefaultDeleter
    {
        using type = std::default_delete<T>;
    };

    template <typename T>
    struct DefaultDeleter<T[]>
    {
        using type = std::default_delete<T[]>;
    };

    template <typename T, typename Deleter = typename DefaultDeleter<T>::type>
    class UniqPtr
    {

    public:
        explicit UniqPtr(T *ptr = nullptr) : rawPtr(ptr) {}

        UniqPtr(const UniqPtr &other) = delete;
        UniqPtr &operator=(const UniqPtr &other) = delete;

        UniqPtr(UniqPtr &&other) noexcept
            : rawPtr(other.rawPtr), deleter(other.deleter)
        {
            other.rawPtr = nullptr;
        }
        UniqPtr &operator=(UniqPtr &&other) noexcept
        {
            if (this != &other)
            {
                if (rawPtr)
                {
                    deleter(rawPtr);
                }
                rawPtr = other.rawPtr;
                deleter = std::move(other.deleter);
                other.rawPtr = nullptr;
            }
            return *this;
        }

        ~UniqPtr()
        {
            if (rawPtr)
            {
                deleter(rawPtr);
            }
        }

        // 访问接口
        T &operator*() const
        {
            return *rawPtr;
        }
        T *operator->() const
        {
            return rawPtr;
        }
        T *get() const
        {
            return rawPtr;
        }

        // 资源管理
        T *release()
        {
            T *tmp = rawPtr;
            rawPtr = nullptr;
            return tmp;
        }
        void reset(T *ptr = nullptr)
        {
            if (rawPtr != ptr)
            {
                if (rawPtr)
                {
                    deleter(rawPtr);
                }
                rawPtr = ptr;
            }
        }

    private:
        T *rawPtr;
        Deleter deleter;
    };

    // 数组特化版本
    template <typename T, typename Deleter>
    class UniqPtr<T[], Deleter>
    {
    private:
        T *rawPtr = nullptr;
        Deleter deleter;

    public:
        explicit UniqPtr(T *arrayPtr = nullptr) : rawPtr(arrayPtr) {}
        UniqPtr(T *arrayPtr, Deleter d) : rawPtr(arrayPtr), deleter(std::move(d)) {}

        UniqPtr(const UniqPtr &) = delete;
        UniqPtr &operator=(const UniqPtr &) = delete;

        UniqPtr(UniqPtr &&other) noexcept
            : rawPtr(other.rawPtr), deleter(std::move(other.deleter))
        {
            other.rawPtr = nullptr;
        }

        UniqPtr &operator=(UniqPtr &&other) noexcept
        {
            if (this != &other)
            {
                reset();
                rawPtr = other.rawPtr;
                deleter = std::move(other.deleter);
                other.rawPtr = nullptr;
            }
            return *this;
        }

        ~UniqPtr() { reset(); }

        T &operator[](size_t index) const { return rawPtr[index]; }
        T *get() const { return rawPtr; }

        T *release()
        {
            T *tmp = rawPtr;
            rawPtr = nullptr;
            return tmp;
        }

        void reset(T *arrayPtr = nullptr)
        {
            if (rawPtr != arrayPtr)
            {
                if (rawPtr)
                    deleter(rawPtr);
                rawPtr = arrayPtr;
            }
        }
    };

}