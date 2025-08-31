#pragma once

#include "TimerThread.h"
#include "TimerTypes.h"

#include <atomic>

namespace Structures {

struct TimerData {
    TimerData(Callback callback)
        : m_callback(callback)
        , m_timeout(Duration::zero())
        , m_timesToShot(0U)
    {
    }

    Callback m_callback;
    Duration m_timeout;
    std::atomic<size_t> m_timesToShot;
};

class TimerImpl {
public:
    TimerImpl(Callback);
    ~TimerImpl() = default;

    void start(Duration timeout, size_t timesToShot);
    void stop();

    auto callback() const -> Callback;
    auto timeout() const -> Duration;
    auto shotsLeft() const -> size_t;
    auto isStarted() const -> bool;

private:
    TimerData m_timerData;
    bool m_isStarted;
    TimerThread::TimerIterator m_timerIterator;
};

} // namespace Structures
