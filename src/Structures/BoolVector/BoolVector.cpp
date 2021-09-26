#include "BoolVector.h"

#include <iostream>

// anonymous
namespace {
constexpr size_t BIT_IN_BYTE = 8;
}

namespace Structures {

////////////////////////////////////////////////////////////////////////////////////
// BitController
BoolVector::BitController::BitController(const size_t& globalIndex, byte& byteRef)
    : m_index(globalIndex % BIT_IN_BYTE)
    , m_byte(byteRef)
{
}

BoolVector::BitController& BoolVector::BitController::operator=(const BitController& bc)
{
    setBit(bc);
    return *this;
}

BoolVector::BitController& BoolVector::BitController::operator=(bool value)
{
    setBit(value);
    return *this;
}

BoolVector::BitController::operator bool() const
{
    return getBit();
}

bool BoolVector::BitController::getBit() const
{
    return m_byte & (1 << m_index);
}

void BoolVector::BitController::setBit(const bool& newValue)
{
    if (getBit() != newValue) {
        std::cout << " Change Value " << m_index << " " << (int)m_byte << " ";
        m_byte ^= (1 << m_index);
        std::cout << " to " << (int)m_byte << " \n";
    }
}
// End of BitController
/////////////////////////////////////////////////////////////////////////

BoolVector::BoolVector(const size_t& size)
    : m_array(1 + size / BIT_IN_BYTE)
    , m_size(size)
{
}

BoolVector::BoolVector(const std::initializer_list<bool> list)
    : BoolVector(list.size())
{
    for (const auto& item : list) {
        push_back(item);
    }
}

BoolVector::BitController BoolVector::operator[](const size_t& index)
{
    return BitController(index, getByteRef(index));
}

BoolVector::BitController BoolVector::operator[](const size_t& index) const
{
    return BitController(index, getByteRef(index));
}

size_t BoolVector::capacity() const
{
    return m_array.size() * BIT_IN_BYTE;
}

size_t BoolVector::size() const
{
    return m_size;
}

void BoolVector::push_back(const bool& newValue)
{
    if (capacity() == size()) {
        extend();
    }
    size_t newBitIndex = size();
    BitController newBit(newBitIndex, getByteRef(newBitIndex));
    newBit = newValue;
    ++m_size;
}

void BoolVector::extend()
{
    m_array.push_back(0);
}

byte& BoolVector::getByteRef(const size_t& index) const
{
    return m_array[index / BIT_IN_BYTE];
}

} // namespace Structures