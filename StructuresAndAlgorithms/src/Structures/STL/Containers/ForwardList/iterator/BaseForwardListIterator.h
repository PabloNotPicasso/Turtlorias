#pragma once

#include "Structures/STL/Containers/ForwardList/Node.h"

#include <iterator>

namespace Structures::STL {

template<typename T>
class BaseForwardListIterator {
public:
    template<typename U, typename NodeAllocator>
    friend class ForwardList;

    using BaseNodeT = BaseNode<T>;
    using NodeT = Node<T>;

    using iterator_category = std::forward_iterator_tag;
    using difference_type = int32_t;

    using value_type = BaseNodeT;
    using pointer = BaseNodeT*;
    using reference = BaseNodeT&;

public:
    BaseForwardListIterator()
        : _node(nullptr)
    {
    }

    BaseForwardListIterator(BaseNodeT* node)
        : _node(node)
    {
    }

    BaseForwardListIterator& operator++()
    {
        _node = _node->_next;
        return *this;
    }
    BaseForwardListIterator operator++(int /*dummy*/)
    {
        BaseForwardListIterator toReturn = *this;
        _node = _node->_next;
        return toReturn;
    }

    template<typename U>
    friend bool operator==(
        const BaseForwardListIterator<U>& lhs, const BaseForwardListIterator<U>& rhs);

    template<typename U>
    friend bool operator!=(
        const BaseForwardListIterator<U>& lhs, const BaseForwardListIterator<U>& rhs);

protected:
    BaseNodeT* _node;
};

template<typename T>
bool operator==(const BaseForwardListIterator<T>& lhs, const BaseForwardListIterator<T>& rhs)
{
    return lhs._node == rhs._node;
}

template<typename T>
bool operator!=(const BaseForwardListIterator<T>& lhs, const BaseForwardListIterator<T>& rhs)
{
    return lhs._node != rhs._node;
}

} // namespace Structures::STL