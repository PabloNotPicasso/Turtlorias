#pragma once

#include "BaseForwardListIterator.h"

namespace Structures::STL {

struct ConstTag { };
struct NonConstTag { };

template<typename T, typename ModifierTag>
class ForwardListIterator;

template<typename T>
class ForwardListIterator<T, NonConstTag> : public BaseForwardListIterator<T> {
public:
    using BaseIterator = BaseForwardListIterator<T>;
    using BaseNodeT = typename BaseIterator::BaseNodeT;
    using NodeT = typename BaseIterator::NodeT;

    using iterator_category = typename BaseIterator::iterator_category;
    using difference_type = typename BaseIterator::difference_type;

    using value_type = typename BaseIterator::value_type;
    using pointer = typename BaseIterator::pointer;
    using reference = typename BaseIterator::reference;

    ForwardListIterator(BaseNodeT* node)
        : BaseIterator(node)
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
};

template<typename T>
class ForwardListIterator<T, ConstTag> : public BaseForwardListIterator<T> {
public:
    using BaseIterator = BaseForwardListIterator<T>;
    using BaseNodeT = typename BaseIterator::BaseNodeT;
    using NodeT = typename BaseIterator::NodeT;
    using iterator_category = typename BaseIterator::iterator_category;
    using difference_type = typename BaseIterator::difference_type;

    using value_type = const typename BaseIterator::value_type;
    using pointer = const typename BaseIterator::pointer;
    using reference = const typename BaseIterator::reference;

    ForwardListIterator(const BaseNodeT* node)
        : BaseIterator(const_cast<BaseNodeT*>(node))
    {
    }

    const T& operator*() const
    {
        return static_cast<NodeT*>(this->_node)->_value;
    }
    const T* operator->() const
    {
        return &static_cast<NodeT*>(this->_node)->_value;
    }
};

} // namespace Structures::STL