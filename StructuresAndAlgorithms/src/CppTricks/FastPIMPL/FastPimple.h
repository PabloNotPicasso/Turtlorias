#pragma once

#include <unistd.h>

#include <type_traits>
#include <utility>

template<typename T, size_t Size, size_t Alignment>
class FastPimple {
public:
    template<typename... Args>
    explicit FastPimple(Args&&... args)
    {
        new (Ptr()) T(std::forward<Args>(args)...);
    }

    FastPimple(FastPimple&& rhs)
    {
        *Ptr() = std::move(*rhs);
    }

    FastPimple& operator=(FastPimple&& rhs)
    {
        *Ptr() = std::move(*rhs);
        return *this;
    }

    ~FastPimple() noexcept
    {
        validate<sizeof(T), alignof(T)>();
        Ptr()->~T();
    }

    T& operator*() noexcept
    {
        return *Ptr();
    }

    const T& operator*() const noexcept
    {
        return *Ptr();
    }

    T* operator->() noexcept
    {
        return Ptr();
    }

    const T* operator->() const noexcept
    {
        return Ptr();
    }

    template<size_t SizeT, size_t AlignmentT>
    constexpr static void validate() noexcept
    {
        static_assert(SizeT == Size);
        static_assert(AlignmentT == Alignment);
    }

private:
    T* Ptr() noexcept
    {
        return reinterpret_cast<T*>(&data);
    }
    const T* Ptr() const noexcept
    {
        return reinterpret_cast<T*>(&data);
    }

    std::aligned_storage_t<Size, Alignment> data;
};