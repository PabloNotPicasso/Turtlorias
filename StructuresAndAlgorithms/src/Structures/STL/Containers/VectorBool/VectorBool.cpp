#include "VectorBool.h"

#include <cassert>
#include <iostream>

// anonymous
namespace {
constexpr size_t BIT_IN_BYTE = 8;
}

namespace Structures::STL {

Vector<bool>::reference Vector<bool>::operator[](const size_t index)
{
    return BitController(index % BIT_IN_BYTE, this->getBytePtr(index));
}

Vector<bool>::const_reference Vector<bool>::operator[](const size_t index) const
{
    return BitController(index % BIT_IN_BYTE, this->getBytePtr(index));
}

void Vector<bool>::push_back(const value_type& newValue)
{
    if (capacity() == size()) {
        extend();
    }
    size_t newBitIndex = size();
    BitController newBit(newBitIndex, getBytePtr(newBitIndex));
    newBit = newValue;
    ++this->m_size;
}

void Vector<bool>::extend()
{
    // m_array.push_back(0);
}

Vector<bool>::byte* Vector<bool>::getBytePtr(const size_t index)
{
    return data() + index / BIT_IN_BYTE;
}

const Vector<bool>::byte* Vector<bool>::getBytePtr(const size_t index) const
{
    return data() + index / BIT_IN_BYTE;
}

} // namespace Structures::STL