#pragma once

#include <cassert>
#include <cstddef>

namespace Structures::STL {

class ControllBlock {
public:
    ControllBlock() = default;

    inline void increment()
    {
        ++m_counter;
    }
    inline void decrement()
    {
        assert(m_counter);
        --m_counter;
    }
    inline bool isZero() const
    {
        return !m_counter;
    }

    inline size_t counter() const
    {
        return m_counter;
    }

private:
    size_t m_counter = 0;
};

} // namespace Structures::STL
