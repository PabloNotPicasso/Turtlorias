#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

namespace Structures::STL {

class VectorBool {
private:
    using byte = int8_t;
    class BitController {
    public:
        BitController(const size_t globalIndex, byte& byteRef);

        BitController& operator=(const BitController& bc);
        BitController& operator=(bool value);

        operator bool() const;

    protected:
        bool getBit() const;
        void setBit(const bool newValue);

    private:
        const size_t m_index;
        byte& m_byte;
    };

public:
    /**
     * @brief Will create vector which support at least \p size boolean variables
     */
    VectorBool(const size_t size = 0);

    /**
     * @brief Will create vector using initializer list values
     */
    VectorBool(std::initializer_list<bool> list);

    /**
     * @brief Returns modifieble BitController by \p index
     */
    BitController operator[](const size_t index);

    const BitController operator[](const size_t index) const;

    /**
     * @brief Returns capacity of allocated storage
     */
    size_t capacity() const;

    /**
     * @brief Returns container size
     */
    size_t size() const;

    /**
     * @brief Push new value to storage
     */
    void push_back(const bool newValue);

protected:
    void extend();

    byte& getByteRef(const size_t index) const;

private:
    mutable std::vector<byte> m_array;
    size_t m_size;
};

} // namespace Structures::STL