#include "TimerImpl.h"

namespace Structures {

TimerImpl::TimerImpl(Callback callback)
    : m_timerData(callback)
    , m_isStarted(false)
{
}

void TimerImpl::start(Duration timeout, size_t timesToShot)
{
    if (m_isStarted) {
        return;
    }
    m_isStarted = true;

    m_timerData.m_timeout = timeout;
    m_timerData.m_timesToShot = timesToShot;
    m_timerIterator = TimerThread::Instance().addTimer(&m_timerData);
}

void TimerImpl::stop()
{
    if (!m_isStarted) {
        return;
    }
    m_isStarted = false;
    TimerThread::Instance().deleteTimer(m_timerIterator);
}

auto TimerImpl::callback() const -> Callback
{
    return m_timerData.m_callback;
}

auto TimerImpl::timeout() const -> std::chrono::milliseconds
{
    return m_timerData.m_timeout;
}

auto TimerImpl::shotsLeft() const -> size_t
{
    return m_timerData.m_timesToShot;
}

auto TimerImpl::isStarted() const -> bool
{
    return m_isStarted;
}

} // namespace Structures
