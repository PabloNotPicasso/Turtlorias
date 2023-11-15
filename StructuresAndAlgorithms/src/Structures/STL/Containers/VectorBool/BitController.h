#pragma once

#include <cstddef>
#include <cstdint>

namespace Structures::STL {

template<typename Byte>
class BitController {
public:
    // internalIndex < 8
    BitController(size_t internalIndex, Byte* bytePtr)
        : m_index(internalIndex)
        , m_byte(bytePtr)
    {
    }

    BitController& operator=(const BitController& bc)
    {
        setBit(bc);
        return *this;
    }

    BitController& operator=(bool value)
    {
        setBit(value);
        return *this;
    }

    operator bool() const
    {
        return getBit();
    }

protected:
    bool getBit() const
    {
        return *m_byte & (1 << m_index);
    }
    void setBit(const bool newValue){
        if (getBit() != newValue) {
            *m_byte ^= (1 << m_index);
        }
    }

private:
    const size_t m_index;
    Byte* m_byte;
};

} // namespace Structures::STL