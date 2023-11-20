#pragma once

#include <functional>

namespace Multithreading {

class IEvent {
public:
    virtual ~IEvent() = default;

    virtual void invoke() = 0;
};

} // namespace Multithreading