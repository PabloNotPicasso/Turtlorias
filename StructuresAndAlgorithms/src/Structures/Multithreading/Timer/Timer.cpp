#include "Timer.h"

#include "TimerImpl.h"

namespace Structures {

Timer::Timer(Callback callback)
    : m_impl(std::make_unique<TimerImpl>(callback))
{
}

Timer::~Timer()
{
    stop();
}

void Timer::start(Duration timeout, size_t timesToShot)
{
    m_impl->start(timeout, timesToShot);
}

void Timer::stop()
{
    m_impl->stop();
}

auto Timer::callback() const -> Callback
{
    return m_impl->callback();
}

auto Timer::timeout() const -> std::chrono::milliseconds
{
    return m_impl->timeout();
}

auto Timer::shotsLeft() const -> size_t
{
    return m_impl->shotsLeft();
}

auto Timer::isStarted() const -> bool
{
    return m_impl->isStarted();
}

} // namespace Structures