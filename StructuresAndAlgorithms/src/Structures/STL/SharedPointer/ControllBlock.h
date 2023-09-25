#pragma once

#include <cassert>
#include <cstddef>

namespace Structures::STL {

class ControllBlock {
public:
    ControllBlock()
        : m_counter(0)
    {
    }

    void increment()
    {
        ++m_counter;
    }
    void decrement()
    {
        assert(m_counter);
        --m_counter;
    }
    bool isZero() const
    {
        return !m_counter;
    }

private:
    size_t m_counter;
};

} // namespace Structures::STL