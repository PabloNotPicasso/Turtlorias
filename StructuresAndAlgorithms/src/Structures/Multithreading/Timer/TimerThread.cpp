#include "TimerThread.h"

#include "Logger/LoggerApi.h"
#include "TimerImpl.h"

namespace Structures {

class TimerThread::TimerHandler {
public:
    TimerHandler(TimerData* timerData)
        : m_timerData(timerData)
        , m_nextShotTimestamp(Clock::now() + timerData->m_timeout)
    {
    }

    bool nextShot()
    {
        --m_timerData->m_timesToShot;
        m_nextShotTimestamp = m_nextShotTimestamp + m_timerData->m_timeout;
        return m_timerData->m_timesToShot > 0;
    }

    TimerData* timerData()
    {
        return m_timerData;
    }

    Timestamp nextShotTimestamp() const
    {
        return m_nextShotTimestamp;
    }

    constexpr bool operator<(const TimerHandler& rhs) const noexcept
    {
        return m_nextShotTimestamp < rhs.m_nextShotTimestamp;
    }

private:
    TimerData* m_timerData;
    Timestamp m_nextShotTimestamp;
};

TimerThread::TimerThread()
    : m_state(State::Idle)
    , m_threadIsRunning(false)
{
    std::unique_lock ul(m_mtx);

    m_thread = std::make_unique<std::thread>(std::bind(&TimerThread::run, this));

    m_cv.wait(ul, [threadIsRunning = &m_threadIsRunning]() { return threadIsRunning; });
}

TimerThread::~TimerThread()
{
    m_threadIsRunning = false;

    if (m_state != State::Idle) {
        std::unique_lock ul(m_mtx);
        m_state = State::Idle;
        m_timers.clear();
        m_cv.notify_one();
    }

    if (m_thread->joinable()) {
        m_thread->join();
    }
}

auto TimerThread::addTimer(TimerData* timerData) -> TimerThread::TimerIterator
{
    std::unique_lock ul(m_mtx);
    m_state = State::Interrupted;
    m_cv.notify_one();

    TimerHandler timerHandler(timerData);

    auto itToInsert = std::lower_bound(m_timers.begin(), m_timers.end(), timerHandler);

    return m_timers.insert(itToInsert, timerHandler);
}

void TimerThread::deleteTimer(TimerThread::TimerIterator itToDelete)
{
    std::unique_lock ul(m_mtx);
    m_state = State::Interrupted;
    m_timers.erase(itToDelete);
    m_cv.notify_one();
}

void TimerThread::run()
{
    m_threadIsRunning = true;
    while (m_threadIsRunning) {
        while (!m_timers.empty()) {
            {
                std::unique_lock ul(m_mtx);
                m_state = State::Waiting;
                m_cv.wait_until(ul, m_timers.front().nextShotTimestamp());
            }

            switch (m_state) {
            case State::Interrupted:
                continue;
                break;
            case State::Waiting:
                processNextTimer();
                break;
            default:
                break;
            }
        }
        if (m_state != State::Idle) {
            m_state = State::Idle;
        }
    }
}

void TimerThread::processNextTimer()
{
    if (m_timers.empty()) {
        LOG_ERR("m_timers is empty");
        return;
    }
    TimerHandler& timer = m_timers.front();
    auto callback = timer.timerData()->m_callback;

    std::thread([callback]() { std::invoke(callback); }).detach();

    bool willBeRepeated = timer.nextShot();

    if (willBeRepeated) {
        auto newPossitionIt = std::lower_bound(std::next(m_timers.begin()), m_timers.end(), timer);
        m_timers.splice(newPossitionIt, m_timers, m_timers.begin());
    } else {
        m_timers.pop_front();
    }
}

} // namespace Structures
