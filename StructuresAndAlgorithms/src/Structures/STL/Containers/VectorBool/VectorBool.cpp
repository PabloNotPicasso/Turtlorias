#include "VectorBool.h"

#include <cassert>
#include <iostream>

// anonymous
namespace {
constexpr size_t BIT_IN_BYTE = 8;
}

namespace Structures::STL {

////////////////////////////////////////////////////////////////////////////////////
// BitController
VectorBool::BitController::BitController(const size_t globalIndex, byte& byteRef)
    : m_index(globalIndex % BIT_IN_BYTE)
    , m_byte(byteRef)
{
}

VectorBool::BitController& VectorBool::BitController::operator=(const BitController& bc)
{
    setBit(bc);
    return *this;
}

VectorBool::BitController& VectorBool::BitController::operator=(bool value)
{
    setBit(value);
    return *this;
}

VectorBool::BitController::operator bool() const
{
    return getBit();
}

bool VectorBool::BitController::getBit() const
{
    return m_byte & (1 << m_index);
}

void VectorBool::BitController::setBit(const bool newValue)
{
    if (getBit() != newValue) {
        m_byte ^= (1 << m_index);
    }
}
// End of BitController
/////////////////////////////////////////////////////////////////////////

VectorBool::VectorBool(const size_t size)
    : m_array(1 + size / BIT_IN_BYTE)
    , m_size(size)
{
}

VectorBool::VectorBool(const std::initializer_list<bool> list)
    : VectorBool(list.size())
{
    for (const auto& item : list) {
        push_back(item);
    }
}

VectorBool::BitController VectorBool::operator[](const size_t index)
{
    assert(index < size());
    return BitController(index, getByteRef(index));
}

const VectorBool::BitController VectorBool::operator[](const size_t index) const
{
    assert(index < size());
    return BitController(index, getByteRef(index));
}

size_t VectorBool::capacity() const
{
    return m_array.size() * BIT_IN_BYTE;
}

size_t VectorBool::size() const
{
    return m_size;
}

void VectorBool::push_back(const bool newValue)
{
    if (capacity() == size()) {
        extend();
    }
    size_t newBitIndex = size();
    BitController newBit(newBitIndex, getByteRef(newBitIndex));
    newBit = newValue;
    ++m_size;
}

void VectorBool::extend()
{
    m_array.push_back(0);
}

VectorBool::byte& VectorBool::getByteRef(const size_t index) const
{
    return m_array[index / BIT_IN_BYTE];
}

} // namespace Structures::STL
