#include "EventLoop.h"

#include "Event/Event.h"

#include <functional>
#include <thread>

namespace Multithreading {

EventLoop::EventLoop()
    : m_state(State::Shutdown)
{
}

EventLoop::~EventLoop()
{
    shutdown();
}

void EventLoop::postEvent(std::unique_ptr<IEvent> event)
{
    {
        std::unique_lock ul(m_mutex);
        m_eventsBuffer.push(std::move(event));
    }
    m_cv.notify_one();
}

void EventLoop::postEvent(SimpleCallback simpleCallback)
{
    postEvent(std::make_unique<Event>(simpleCallback));
}

void EventLoop::run()
{
    if (m_state == State::Shutdown) {
        m_state = State::Running;
        m_thread = std::thread(&EventLoop::threadFunction, this);
    }
}

std::thread::id EventLoop::threadId() const
{
    return m_thread.get_id();
}

bool EventLoop::isRunning() const
{
    return m_state != State::Shutdown;
}

void EventLoop::threadFunction()
{
    while (m_state != State::Shutdown) {
        {
            std::unique_lock lock(m_mutex);
            m_cv.wait(lock, [this] { return !m_eventsBuffer.empty(); });
            std::swap(m_eventsBuffer, m_eventsToProcess);
        }
        while (!m_eventsToProcess.empty()) {
            processNextEvent();
        }
    }
}

void EventLoop::shutdown()
{
    postEvent([this]() { m_state = State::Shutdown; });

    if (m_thread.joinable()) {
        m_thread.join();
    }
}

void EventLoop::processNextEvent()
{
    auto eventToProcess = std::move(m_eventsToProcess.front());
    m_eventsToProcess.pop();
    eventToProcess->invoke();
}

} // namespace Multithreading