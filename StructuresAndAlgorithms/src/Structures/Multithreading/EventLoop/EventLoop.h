#pragma once

#include "Event/IEvent.h"
#include "Event/Types.h"

#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

namespace Multithreading {

class EventLoop {
public:
    EventLoop();
    ~EventLoop();

    void postEvent(std::unique_ptr<IEvent> event);
    void postEvent(SimpleCallback simpleCallback);

    void run();
    void shutdown();

    std::thread::id threadId() const;
    bool isRunning() const;

private:
    void threadFunction();
    void processNextEvent();

private:
    enum class State {
        Running,
        Shutdown,
    } m_state;

    std::thread m_thread;
    mutable std::recursive_mutex m_mutex;
    std::condition_variable_any m_cv;

    std::queue<std::unique_ptr<IEvent>> m_eventsBuffer;
    std::queue<std::unique_ptr<IEvent>> m_eventsToProcess;
};

} // namespace Multithreading