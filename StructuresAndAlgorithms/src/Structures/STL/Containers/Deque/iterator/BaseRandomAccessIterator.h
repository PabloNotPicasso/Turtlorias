#pragma once

#include "BaseBidirectionalIterator.h"

namespace Structures::STL {

template<typename T>
class BaseRandomAccessIterator : public BaseBidirectionalIterator<T> {
public:
    using Parent = BaseBidirectionalIterator<T>;

    using iterator_category = std::random_access_iterator_tag;

    using difference_type = typename Parent::difference_type;
    using value_type = typename Parent::value_type;
    using pointer = typename Parent::pointer;
    using reference = typename Parent::reference;

public:
    using Parent::Parent;

    BaseRandomAccessIterator& operator+=(difference_type shift)
    {
        this->_elementId += shift;
        this->_block += (this->_elementId / DequeBlockSize);
        this->_elementId = ((this->_elementId % DequeBlockSize) + DequeBlockSize) % DequeBlockSize;
        return *this;
    }
    BaseRandomAccessIterator& operator-=(difference_type shift)
    {
        this->operator+=(-shift);
        return *this;
    }

    template<typename U>
    friend BaseRandomAccessIterator<U> operator+(
        BaseRandomAccessIterator<U> iterator,
        typename BaseRandomAccessIterator<U>::difference_type shift);
    template<typename U>
    friend BaseRandomAccessIterator<U> operator-(
        BaseRandomAccessIterator<U> iterator,
        typename BaseRandomAccessIterator<U>::difference_type shift);

    template<typename U>
    friend typename BaseRandomAccessIterator<U>::difference_type operator-(
        BaseRandomAccessIterator<U> lhs, BaseRandomAccessIterator<U> rhs);

    template<typename U>
    friend bool operator<(BaseRandomAccessIterator<U> lhs, BaseRandomAccessIterator<U> rhs);
    template<typename U>
    friend bool operator<=(BaseRandomAccessIterator<U> lhs, BaseRandomAccessIterator<U> rhs);

    template<typename U>
    friend bool operator>(BaseRandomAccessIterator<U> lhs, BaseRandomAccessIterator<U> rhs);
    template<typename U>
    friend bool operator>=(BaseRandomAccessIterator<U> lhs, BaseRandomAccessIterator<U> rhs);
};

template<typename T>
BaseRandomAccessIterator<T> operator+(
    BaseRandomAccessIterator<T> iterator,
    typename BaseRandomAccessIterator<T>::difference_type shift)
{
    iterator += shift;
    return iterator;
}

template<typename T>
BaseRandomAccessIterator<T> operator-(
    BaseRandomAccessIterator<T> iterator,
    typename BaseRandomAccessIterator<T>::difference_type shift)
{
    iterator -= shift;
    return iterator;
}

template<typename T>
typename BaseRandomAccessIterator<T>::difference_type operator-(
    BaseRandomAccessIterator<T> lhs, BaseRandomAccessIterator<T> rhs)
{
    return (lhs._block - rhs._block) * DequeBlockSize + (lhs._elementId - rhs._elementId);
}

template<typename T>
bool operator<(BaseRandomAccessIterator<T> lhs, BaseRandomAccessIterator<T> rhs)
{
    return (lhs._block < rhs._block)
        || ((lhs._block == rhs._block) && (lhs._elementId < rhs._elementId));
}
template<typename T>
bool operator<=(BaseRandomAccessIterator<T> lhs, BaseRandomAccessIterator<T> rhs)
{
    return !(rhs < lhs);
}

template<typename T>
bool operator>(BaseRandomAccessIterator<T> lhs, BaseRandomAccessIterator<T> rhs)
{
    return rhs < lhs;
}
template<typename T>
bool operator>=(BaseRandomAccessIterator<T> lhs, BaseRandomAccessIterator<T> rhs)
{
    return !(lhs < rhs);
}
} // namespace Structures::STL
