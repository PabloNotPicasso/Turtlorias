#pragma once

#include <iterator>

namespace Structures::STL {

template<typename T>
class BaseArrayIterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = int32_t;

    using value_type = T;
    using pointer = T*;
    using reference = T&;

public:
    BaseArrayIterator() { }

    BaseArrayIterator(T* element)
        : _element(element)
    {
    }

    BaseArrayIterator& operator++()
    {
        ++_element;
        return *this;
    }
    BaseArrayIterator operator++(difference_type /*dummy*/)
    {
        BaseArrayIterator toReturn = *this;
        ++_element;
        return toReturn;
    }
    BaseArrayIterator& operator--()
    {
        --_element;
        return *this;
    }
    BaseArrayIterator operator--(difference_type /*dummy*/)
    {
        BaseArrayIterator toReturn = *this;
        --_element;
        return toReturn;
    }

    BaseArrayIterator operator+=(difference_type shift)
    {
        _element += shift;
        return *this;
    }
    BaseArrayIterator operator-=(difference_type shift)
    {
        _element -= shift;
        return *this;
    }

    template<typename U>
    friend BaseArrayIterator<U> operator+(
        BaseArrayIterator<U> iterator, typename BaseArrayIterator<U>::difference_type shift);
    template<typename U>
    friend BaseArrayIterator<U> operator-(
        BaseArrayIterator<U> iterator, typename BaseArrayIterator<U>::difference_type shift);

    template<typename U>
    friend bool operator==(BaseArrayIterator<U> lhs, BaseArrayIterator<U> rhs);
    template<typename U>
    friend bool operator!=(BaseArrayIterator<U> lhs, BaseArrayIterator<U> rhs);

    template<typename U>
    friend bool operator<(BaseArrayIterator<U> lhs, BaseArrayIterator<U> rhs);
    template<typename U>
    friend bool operator<=(BaseArrayIterator<U> lhs, BaseArrayIterator<U> rhs);

    template<typename U>
    friend bool operator>(BaseArrayIterator<U> lhs, BaseArrayIterator<U> rhs);
    template<typename U>
    friend bool operator>=(BaseArrayIterator<U> lhs, BaseArrayIterator<U> rhs);

protected:
    T* _element;
};

template<typename U>
BaseArrayIterator<U> operator+(
    BaseArrayIterator<U> iterator, typename BaseArrayIterator<U>::difference_type shift)
{
    return BaseArrayIterator<U>(iterator._element + shift);
}

template<typename U>
BaseArrayIterator<U> operator-(
    BaseArrayIterator<U> iterator, typename BaseArrayIterator<U>::difference_type shift)
{
    return BaseArrayIterator<U>(iterator._element - shift);
}

template<typename T>
bool operator==(BaseArrayIterator<T> lhs, BaseArrayIterator<T> rhs)
{
    return lhs._element == rhs._element;
}

template<typename T>
bool operator!=(BaseArrayIterator<T> lhs, BaseArrayIterator<T> rhs)
{
    return lhs._element != rhs._element;
}

template<typename U>
bool operator<(BaseArrayIterator<U> lhs, BaseArrayIterator<U> rhs)
{
    return lhs._element < rhs._element;
}
template<typename U>
bool operator<=(BaseArrayIterator<U> lhs, BaseArrayIterator<U> rhs)
{
    return lhs._element <= rhs._element;
}

template<typename U>
bool operator>(BaseArrayIterator<U> lhs, BaseArrayIterator<U> rhs)
{
    return lhs._element > rhs._element;
}
template<typename U>
bool operator>=(BaseArrayIterator<U> lhs, BaseArrayIterator<U> rhs)
{
    return lhs._element >= rhs._element;
}

} // namespace Structures::STL