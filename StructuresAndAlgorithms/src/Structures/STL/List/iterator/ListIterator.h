#pragma once

#include "BaseListIterator.h"

namespace Structures::STL {

struct ConstTag { };
struct NonConstTag { };

template<typename T, typename ModifierTag>
class ListIterator;

template<typename T>
class ListIterator<T, NonConstTag> : public BaseListIterator<T> {
public:
    using BaseIterator = BaseListIterator<T>;
    using BaseNode = typename BaseIterator::BaseNode;
    using Node = typename BaseIterator::Node;

    using iterator_category = typename BaseIterator::iterator_category;
    using difference_type = typename BaseIterator::difference_type;

    using value_type = typename BaseIterator::value_type;
    using pointer = typename BaseIterator::pointer;
    using reference = typename BaseIterator::reference;

    ListIterator(BaseNode* node)
        : BaseIterator(node)
    {
    }

    T& operator*()
    {
        return static_cast<Node*>(this->_node)->_value;
    }
    T* operator->()
    {
        return &static_cast<Node*>(this->_node)->_value;
    }
};

template<typename T>
class ListIterator<T, ConstTag> : public BaseListIterator<T> {
public:
    using BaseIterator = BaseListIterator<T>;
    using BaseNode = typename BaseIterator::BaseNode;
    using Node = typename BaseIterator::Node;
    using iterator_category = typename BaseIterator::iterator_category;
    using difference_type = typename BaseIterator::difference_type;

    using value_type = const typename BaseIterator::value_type;
    using pointer = const typename BaseIterator::pointer;
    using reference = const typename BaseIterator::reference;

    ListIterator(const BaseNode* node)
        : BaseIterator(const_cast<BaseNode*>(node))
    {
    }

    const T& operator*() const
    {
        return static_cast<const Node*>(this->_node)->_value;
    }
    const T* operator->() const
    {
        return &static_cast<const Node*>(this->_node)->_value;
    }
};

} // namespace Structures::STL