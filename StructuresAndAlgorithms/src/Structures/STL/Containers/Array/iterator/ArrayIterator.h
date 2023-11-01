#pragma once

#include "BaseArrayIterator.h"

namespace Structures::STL {

struct ConstTag { };
struct NonConstTag { };

template<typename T, typename ModifierTag>
class ArrayIterator;

template<typename T>
class ArrayIterator<T, NonConstTag> : public BaseArrayIterator<T> {
public:
    using BaseIterator = BaseArrayIterator<T>;

    using iterator_category = typename BaseIterator::iterator_category;
    using difference_type = typename BaseIterator::difference_type;

    using value_type = typename BaseIterator::value_type;
    using pointer = typename BaseIterator::pointer;
    using reference = typename BaseIterator::reference;

    ArrayIterator(T* element)
        : BaseIterator(element)
    {
    }

    T& operator*()
    {
        return *this->_element;
    }
    T* operator->()
    {
        return this->_element;
    }
};

template<typename T>
class ArrayIterator<T, ConstTag> : public BaseArrayIterator<T> {
public:
    using BaseIterator = BaseArrayIterator<T>;
    using iterator_category = typename BaseIterator::iterator_category;
    using difference_type = typename BaseIterator::difference_type;

    using value_type = const typename BaseIterator::value_type;
    using pointer = const typename BaseIterator::pointer;
    using reference = const typename BaseIterator::reference;

    ArrayIterator(const T* element)
        : BaseIterator(const_cast<T*>(element))
    {
    }

    const T& operator*() const
    {
        return *this->_element;
    }
    const T* operator->() const
    {
        return this->_element;
    }
};

} // namespace Structures::STL