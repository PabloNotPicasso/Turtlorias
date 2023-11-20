#include "Event.h"

namespace Multithreading {

Event::Event(const SimpleCallback& callback)
    : m_callback(callback)
{
}
Event::Event(SimpleCallback&& callback)
    : m_callback(callback)
{
}

void Event::invoke()
{
    std::invoke(m_callback);
}

} // namespace Multithreading