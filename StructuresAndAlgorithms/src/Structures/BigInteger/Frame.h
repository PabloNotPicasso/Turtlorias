#pragma once

#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdint>

namespace Structures {

/**
 * @brief Frame is abstraction to contain signed integer value
 * \p value is always in range [-999'999, 999'999]
 * In case of overflowing and out of range situation
 * \p value will be assigned to \p value (mod 1'000'000)
 */
class Frame {
public:
    using value_t = int32_t;

    static constexpr size_t Base = 10U;
    static constexpr size_t MaxFrameLenght = 6U;
    static constexpr int64_t Mod = 1'000'000;
    static constexpr value_t MaxFrameValue = Mod - 1;
    static constexpr value_t MinFrameValue = -MaxFrameValue;

    Frame(const value_t _value)
        : m_value(_value)
    {
        assert(abs(m_value) <= MaxFrameValue);
    }
    Frame()
        : m_value(0)
    {
    }
    Frame(const Frame& toCopy)
        : Frame(toCopy.m_value)
    {
    }
    Frame& operator=(const Frame& toCopy)
    {
        m_value = toCopy.m_value;
        return *this;
    }

    value_t value() const
    {
        return m_value;
    }
    operator value_t() const
    {
        return m_value;
    }

private:
    value_t m_value;
};

} // namespace Structures