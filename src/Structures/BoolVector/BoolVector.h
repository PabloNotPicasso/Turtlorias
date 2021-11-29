#pragma once

#include <cstdint>
#include <vector>

namespace Structures {

class BoolVector {
private:
    using byte = int8_t;
    class BitController {
    public:
        BitController(const BitController& bc) = default;
        BitController(const size_t& globalIndex, byte& byteRef);

        BitController& operator=(const BitController& bc);
        BitController& operator=(bool value);

        operator bool() const;

    protected:
        bool getBit() const;
        void setBit(const bool& newValue);

    private:
        const size_t m_index;
        byte& m_byte;
    };

public:
    BoolVector(const size_t& size = 0);
    BoolVector(std::initializer_list<bool> list);

    BitController operator[](const size_t& index);

    BitController operator[](const size_t& index) const;

    size_t capacity() const;

    size_t size() const;

    void push_back(const bool& newValue);

protected:
    void extend();

    byte& getByteRef(const size_t& index) const;

private:
    mutable std::vector<byte> m_array;
    size_t m_size;
};

} // namespace Structures