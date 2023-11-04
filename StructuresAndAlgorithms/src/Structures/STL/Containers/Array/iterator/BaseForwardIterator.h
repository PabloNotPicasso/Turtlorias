#pragma once

#include "BaseInputIterator.h"

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
        ++this->_element;
        return *this;
    }
    BaseForwardIterator operator++(int /*dummy*/)
    {
        BaseForwardIterator toReturn = *this;
        ++this->_element;
        return toReturn;
    }
};

} // namespace Structures::STL