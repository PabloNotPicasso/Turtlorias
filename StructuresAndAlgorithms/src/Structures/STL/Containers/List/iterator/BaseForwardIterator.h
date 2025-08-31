#pragma once

#include "BaseInputIterator.h"

namespace Structures::STL {

template<typename T, typename BaseNodeT, typename NodeT>
class BaseForwardIterator : public BaseInputIterator<T, BaseNodeT, NodeT> {
public:
    using Parent = BaseInputIterator<T, BaseNodeT, NodeT>;

    using iterator_category = std::forward_iterator_tag;

    using difference_type = typename Parent::difference_type;
    using value_type = typename Parent::value_type;
    using pointer = typename Parent::pointer;
    using reference = typename Parent::reference;

public:
    using Parent::Parent;

    BaseForwardIterator& operator++()
    {
        this->_node = this->_node->_next;
        return *this;
    }
    BaseForwardIterator operator++(int /*dummy*/)
    {
        BaseForwardIterator toReturn = *this;
        this->_node = this->_node->_next;
        return toReturn;
    }
};

} // namespace Structures::STL
