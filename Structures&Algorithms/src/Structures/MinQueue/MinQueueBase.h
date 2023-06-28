#pragma once

#include <limits>

namespace Structures {

template<typename Numeric>
class MinQueueBase {
public:
    void push(const Numeric x);
    void pop();
    bool empty() const;
    size_t size() const;
    Numeric currentMin() const;
    constexpr static Numeric maxLimit()
    {
        return std::numeric_limits<Numeric>::max();
    }
};

} // namespace Structures