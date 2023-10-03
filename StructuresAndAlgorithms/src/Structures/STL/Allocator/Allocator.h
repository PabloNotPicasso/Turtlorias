#pragma once

#include <cstddef>
#include <cstdint>

namespace Structures::STL {

template<typename T>
class Allocator {
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = size_t;

public:
    [[nodiscard]] T* allocate(std::size_t n)
    {
        return reinterpret_cast<T*>(::operator new(n * sizeof(T)));
        return nullptr;
    }

    void deallocate(T* ptr, std::size_t n)
    {
        ::operator delete(ptr, n);
    }

    template<typename... Args>
    void construct(T* p, Args... args)
    {
        new (p) T(args...);
    }

    void destroy(T* p)
    {
        p->~T();
    }
};

} // namespace Structures::STL