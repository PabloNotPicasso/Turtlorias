#pragma once

#include "Logger/LoggerApi.h"
#include "iterator/ArrayIterator.h"

namespace Structures::STL {

using Size = size_t;

template<typename T, Size N>
class Array {
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = size_t;

    using iterator = ArrayIterator<T, NonConstTag>;
    using const_iterator = ArrayIterator<T, ConstTag>;

public:
    constexpr Array() { }

    explicit Array(const T (&initializerArray)[N])
    {
        for (size_t i = 0; i != N; ++i) {
            _data[i] = initializerArray[i];
        }
    }

    template<typename... Args>
    explicit Array(Args... args)
        : _data{std::forward<Args>(args)...}
    {
    }

    Array& operator=(const Array& toCopy)
    {
        for (size_t i = 0; i != N; ++i) {
            _data[i] = toCopy[i];
        }
        return *this;
    }

    Array& operator=(Array&& toMove)
    {
        swap(toMove);
        return *this;
    }

    constexpr bool empty() const
    {
        return N == 0;
    }

    constexpr size_type size() const noexcept
    {
        return N;
    }

    T& operator[](size_type idx)
    {
        return _data[idx];
    }
    const T& operator[](size_type idx) const
    {
        return _data[idx];
    }

    T& at(size_type idx)
    {
        if (idx >= N) {
            throw "out_of_scope exception";
        }
        return _data[idx];
    }

    const T& at(size_type idx) const
    {
        if (idx >= N) {
            throw "out_of_scope exception";
        }
        return _data[idx];
    }

    T& front()
    {
        return _data[0];
    }
    const T& front() const
    {
        return _data[0];
    }

    T& back()
    {
        static_assert(N > 0);
        return _data[N - 1];
    }
    const T& back() const
    {
        static_assert(N > 0);
        return _data[N - 1];
    }

    T* data()
    {
        return _data;
    }
    const T* data() const
    {
        return _data;
    }

    iterator begin()
    {
        return iterator(_data);
    }
    const_iterator begin() const
    {
        return const_iterator(_data);
    }
    const_iterator cbegin() const
    {
        return const_iterator(_data);
    }

    iterator end()
    {
        return iterator(_data + N);
    }
    const_iterator end() const
    {
        return const_iterator(_data + N);
    }
    const_iterator cend() const
    {
        return const_iterator(_data + N);
    }

    /**
     * @brief Swap all data members to \p toSwap
     *
     * @param toSwap
     */
    void swap(Array& toSwap) noexcept
    {
        std::swap(this->_data, toSwap._data);
    }

private:
    T _data[N];
};

template<typename T, Size N, Size M>
bool operator==(const Array<T, N>& lhs, const Array<T, M>& rhs)
{
    return false;
}

template<typename T, Size N>
bool operator==(const Array<T, N>& lhs, const Array<T, N>& rhs)
{
    auto lhsIt = lhs.cbegin();
    auto rhsIt = rhs.cbegin();

    while (rhsIt != rhs.cend() && *lhsIt == *rhsIt) {
        ++lhsIt;
        ++rhsIt;
    }

    return rhsIt == rhs.cend();
}

template<typename T, Size N, Size M>
bool operator!=(const Array<T, N>& lhs, const Array<T, M>& rhs)
{
    return !(lhs == rhs);
}

} // namespace Structures::STL