#pragma once

#include "BaseInputIterator.h"
#include "Structures/STL/Containers/Deque/DequeSize.h"

namespace Structures::STL {

template<typename T>
class BaseForwardIterator : public BaseInputIterator<T> {
public:
    using Parent = BaseInputIterator<T>;

    using iterator_category = std::forward_iterator_tag;

    using difference_type = typename Parent::difference_type;
    using value_type = typename Parent::value_type;
    using pointer = typename Parent::pointer;
    using reference = typename Parent::reference;

public:
    using Parent::Parent;

    BaseForwardIterator& operator++()
    {
        ++this->_elementId;
        if (this->_elementId == DequeBlockSize) {
            ++this->_block;
            this->_elementId = 0;
        }
        return *this;
    }
    BaseForwardIterator operator++(int /*dummy*/)
    {
        BaseForwardIterator toReturn = *this;
        this->operator++();
        return toReturn;
    }
};

} // namespace Structures::STL