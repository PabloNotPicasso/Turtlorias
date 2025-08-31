#pragma once

#include "BaseForwardIterator.h"

namespace Structures::STL {

template<typename T>
class BaseBidirectionalIterator : public BaseForwardIterator<T> {
public:
    using Parent = BaseForwardIterator<T>;

    using iterator_category = std::bidirectional_iterator_tag;

    using difference_type = typename Parent::difference_type;
    using value_type = typename Parent::value_type;
    using pointer = typename Parent::pointer;
    using reference = typename Parent::reference;

public:
    using Parent::Parent;

    BaseBidirectionalIterator& operator--()
    {
        if (this->_elementId == 0) {
            this->_elementId = DequeBlockSize;
            --this->_block;
        }
        --this->_elementId;
        return *this;
    }
    BaseBidirectionalIterator operator--(int /*dummy*/)
    {
        BaseBidirectionalIterator toReturn = *this;
        this->operator--();
        return toReturn;
    }
};

} // namespace Structures::STL
