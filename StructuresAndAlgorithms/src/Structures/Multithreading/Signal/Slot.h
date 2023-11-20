#pragma once

#include "Event/Types.h"

#include <functional>
#include <list>

namespace Multithreading {

template<typename... Args>
class Slot {
public:
    using SlotFunction = std::function<void(Args&&...)>;

public:
    Slot(SlotFunction slotFunction)
        : m_slotFunction(slotFunction)
    {
    }

    virtual ~Slot() = default;

    void operator()(Args... args)
    {
        std::invoke(m_slotFunction, std::forward<Args>(args)...);
    }

    SimpleCallback simpleBind(Args&&... args)
    {
        // ? copy of args
        return [args..., this]() { this->operator()(args...); };
    }

private:
    SlotFunction m_slotFunction;
};

} // namespace Multithreading