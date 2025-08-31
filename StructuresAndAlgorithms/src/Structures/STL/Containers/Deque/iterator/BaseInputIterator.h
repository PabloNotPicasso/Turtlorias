#pragma once

#include <iterator>

namespace Structures::STL {

template<typename T>
class BaseInputIterator {
public:
    using iterator_category = std::input_iterator_tag;

    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;

public:
    BaseInputIterator()
        : _block(nullptr)
        , _elementId(0)
    {
    }

    BaseInputIterator(T** block, size_t elementId)
        : _block(block)
        , _elementId(elementId)
    {
    }

    const T& operator*() const
    {
        return *(*_block + _elementId);
    }
    T& operator*()
    {
        return *(*_block + _elementId);
    }

    const T* operator->() const
    {
        return (*_block + _elementId);
    }
    T* operator->()
    {
        return (*_block + _elementId);
    }

    template<typename U>
    friend bool operator==(BaseInputIterator<U> lhs, BaseInputIterator<U> rhs);
    template<typename U>
    friend bool operator!=(BaseInputIterator<U> lhs, BaseInputIterator<U> rhs);

protected:
    T** _block;
    int32_t _elementId;
};

template<typename T>
bool operator==(BaseInputIterator<T> lhs, BaseInputIterator<T> rhs)
{
    return lhs.operator->() == rhs.operator->();
}

template<typename T>
bool operator!=(BaseInputIterator<T> lhs, BaseInputIterator<T> rhs)
{
    return lhs.operator->() != rhs.operator->();
}

} // namespace Structures::STL
