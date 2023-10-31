#pragma once

#include "Structures/STL/List/Node.h"

#include <iterator>

namespace Structures::STL {

template<typename T>
class BaseListIterator {
public:
    template<typename U, typename NodeAllocator>
    friend class List;

    using BaseNode = BaseListNode<T>;
    using Node = ListNode<T>;

    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = int32_t;

    using value_type = BaseNode;
    using pointer = BaseNode*;
    using reference = BaseNode&;

public:
    BaseListIterator()
        : _node(nullptr)
    {
    }

    BaseListIterator(BaseNode* node)
        : _node(node)
    {
    }

    BaseListIterator& operator++()
    {
        _node = _node->_next;
        return *this;
    }
    BaseListIterator operator++(int /*dummy*/)
    {
        BaseListIterator toReturn = *this;
        _node = _node->_next;
        return toReturn;
    }
    BaseListIterator& operator--()
    {
        _node = _node->_previous;
        return *this;
    }
    BaseListIterator operator--(int /*dummy*/)
    {
        BaseListIterator toReturn = *this;
        _node = _node->_previous;
        return toReturn;
    }

    template<typename U>
    friend bool operator==(const BaseListIterator<U>& lhs, const BaseListIterator<U>& rhs);

    template<typename U>
    friend bool operator!=(const BaseListIterator<U>& lhs, const BaseListIterator<U>& rhs);

protected:
    BaseNode* _node;
};

template<typename T>
bool operator==(const BaseListIterator<T>& lhs, const BaseListIterator<T>& rhs)
{
    return lhs._node == rhs._node;
}

template<typename T>
bool operator!=(const BaseListIterator<T>& lhs, const BaseListIterator<T>& rhs)
{
    return lhs._node != rhs._node;
}

} // namespace Structures::STL