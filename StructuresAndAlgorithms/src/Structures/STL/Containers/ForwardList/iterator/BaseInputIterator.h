#pragma once

#include <iterator>

namespace Structures::STL {

template<typename T, typename BaseNodeT, typename NodeT>
class BaseInputIterator {
public:
    using iterator_category = std::input_iterator_tag;

    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;

public:
    BaseInputIterator()
        : _node(nullptr)
    {
    }

    BaseInputIterator(BaseNodeT* node)
        : _node(node)
    {
    }

    T& operator*()
    {
        return static_cast<NodeT*>(this->_node)->_value;
    }
    T* operator->()
    {
        return &static_cast<NodeT*>(this->_node)->_value;
    }
    const T& operator*() const
    {
        return static_cast<NodeT*>(this->_node)->_value;
    }
    const T* operator->() const
    {
        return &static_cast<NodeT*>(this->_node)->_value;
    }

    template<typename U, typename BaseNodeU, typename NodeU>
    friend bool operator==(
        BaseInputIterator<U, BaseNodeU, NodeU> lhs, BaseInputIterator<U, BaseNodeU, NodeU> rhs);
    template<typename U, typename BaseNodeU, typename NodeU>
    friend bool operator!=(
        BaseInputIterator<U, BaseNodeU, NodeU> lhs, BaseInputIterator<U, BaseNodeU, NodeU> rhs);

protected:
    BaseNodeT* _node;
};

template<typename T, typename BaseNodeT, typename NodeT>
bool operator==(
    BaseInputIterator<T, BaseNodeT, NodeT> lhs, BaseInputIterator<T, BaseNodeT, NodeT> rhs)
{
    return lhs._node == rhs._node;
}

template<typename T, typename BaseNodeT, typename NodeT>
bool operator!=(
    BaseInputIterator<T, BaseNodeT, NodeT> lhs, BaseInputIterator<T, BaseNodeT, NodeT> rhs)
{
    return lhs._node != rhs._node;
}

} // namespace Structures::STL
