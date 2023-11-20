#pragma once

#include "IEvent.h"
#include "Types.h"

#include <list>

namespace Multithreading {

class Event : public IEvent {
public:
    Event(const Event&) = delete;
    Event& operator=(const Event&) = delete;

    Event(const SimpleCallback& callback);
    Event(SimpleCallback&& callback);

    virtual ~Event() = default;

    void invoke() override;

private:
    const SimpleCallback m_callback;
};

} // namespace Multithreading