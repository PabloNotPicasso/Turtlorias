#pragma once

#include "MinQueueBase.h"

#include <cstdint>
#include <limits>
#include <stack>

namespace Structures {

template<typename Numeric>
class MinQueue : public MinQueueBase<Numeric> {
public:
    MinQueue() = default;

    void push(const Numeric x)
    {
        Numeric minimal(x);
        if (!head.empty()) {
            minimal = std::min(minimal, head.top().minimum);
        }
        head.push({x, minimal});
    }

    void pop()
    {
        if (tail.empty()) {
            transform();
        }
        if (tail.empty()) {
            return;
        }
        tail.pop();
    }

    bool empty() const
    {
        return head.empty() && tail.empty();
    }

    size_t size() const
    {
        return head.size() + tail.size();
    }

    Numeric currentMin() const
    {
        Numeric currentMinimum = MinQueue::maxLimit();
        if (!head.empty()) {
            currentMinimum = std::min(currentMinimum, head.top().minimum);
        }
        if (!tail.empty()) {
            currentMinimum = std::min(currentMinimum, tail.top().minimum);
        }
        return currentMinimum;
    }

private:
    /**
     * @brief Take all elements from \p head and push them to \p tail
     * Elements will be pushed one by one, so \p tail will contain reversed \p head elements
     */
    void transform()
    {
        while (!head.empty()) {
            // minimal is min of current head element and minimum of all tail stack
            const Numeric element = head.top().element;
            Numeric minimal = element;
            if (!tail.empty()) {
                minimal = std::min(element, tail.top().minimum);
            }
            head.pop();
            tail.push({element, minimal});
        }
    }

    struct Element_Min {
        Numeric element;
        Numeric minimum;
    };

public:
    std::stack<Element_Min> head;
    std::stack<Element_Min> tail;
};

} // namespace Structures
