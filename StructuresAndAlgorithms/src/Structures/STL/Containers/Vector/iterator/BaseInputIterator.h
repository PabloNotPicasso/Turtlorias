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
        : _element(nullptr)
    {
    }

    BaseInputIterator(T* element)
        : _element(element)
    {
    }

    const T& operator*() const
    {
        return *this->_element;
    }
    T& operator*()
    {
        return *this->_element;
    }

    const T* operator->() const
    {
        return this->_element;
    }
    T* operator->()
    {
        return this->_element;
    }

    template<typename U>
    friend bool operator==(BaseInputIterator<U> lhs, BaseInputIterator<U> rhs);
    template<typename U>
    friend bool operator!=(BaseInputIterator<U> lhs, BaseInputIterator<U> rhs);

protected:
    pointer _element;
};

template<typename T>
bool operator==(BaseInputIterator<T> lhs, BaseInputIterator<T> rhs)
{
    return lhs._element == rhs._element;
}

template<typename T>
bool operator!=(BaseInputIterator<T> lhs, BaseInputIterator<T> rhs)
{
    return lhs._element != rhs._element;
}

} // namespace Structures::STL
