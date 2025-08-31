#pragma once

#include "BaseBidirectionalIterator.h"

namespace Structures::STL {

template<typename T, typename BaseNodeT, typename NodeT>
class ListIterator : public BaseBidirectionalIterator<T, BaseNodeT, NodeT> {
public:
    using Parent = BaseBidirectionalIterator<T, BaseNodeT, NodeT>;

    using iterator_category = typename Parent::iterator_category;

    using difference_type = typename Parent::difference_type;
    using value_type = typename Parent::value_type;
    using pointer = typename Parent::pointer;
    using reference = typename Parent::reference;

public:
    using Parent::Parent;

    BaseNodeT* _get_node()
    {
        return this->_node;
    }
};

} // namespace Structures::STL
