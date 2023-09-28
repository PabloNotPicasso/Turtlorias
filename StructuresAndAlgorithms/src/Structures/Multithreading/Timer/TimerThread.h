#pragma once

#include "TimerTypes.h"

#include <atomic>
#include <condition_variable>
#include <list>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

namespace Structures {

class TimerData;

class TimerThread {
public:
    class TimerHandler;
    using TimerContainer = std::list<TimerHandler>;
    using TimerIterator = typename TimerContainer::iterator;

    static TimerThread& Instance()
    {
        static TimerThread timerThread;
        return timerThread;
    }

    auto addTimer(TimerData*) -> TimerIterator;
    void deleteTimer(TimerIterator);

private:
    TimerThread();
    ~TimerThread();
    void run();
    void processNextTimer();

private:
    TimerContainer m_timers;
    enum class State { Idle, Waiting, Interrupted, Processing };

    std::atomic<State> m_state;

    std::unique_ptr<std::thread> m_thread;
    bool m_threadIsRunning;
    std::mutex m_mtx;
    std::condition_variable m_cv;
};

} // namespace Structures