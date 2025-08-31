#pragma once

#include "BaseForwardIterator.h"

namespace Structures::STL {

template<typename T, typename BaseNodeT, typename NodeT>
class BaseBidirectionalIterator : public BaseForwardIterator<T, BaseNodeT, NodeT> {
public:
    using Parent = BaseForwardIterator<T, BaseNodeT, NodeT>;

    using iterator_category = std::bidirectional_iterator_tag;

    using difference_type = typename Parent::difference_type;
    using value_type = typename Parent::value_type;
    using pointer = typename Parent::pointer;
    using reference = typename Parent::reference;

public:
    using Parent::Parent;

    BaseBidirectionalIterator& operator--()
    {
        this->_node = this->_node->_previous;
        return *this;
    }
    BaseBidirectionalIterator operator--(int /*dummy*/)
    {
        BaseBidirectionalIterator toReturn = *this;
        this->_node = this->_node->_previous;
        return toReturn;
    }
};

} // namespace Structures::STL
