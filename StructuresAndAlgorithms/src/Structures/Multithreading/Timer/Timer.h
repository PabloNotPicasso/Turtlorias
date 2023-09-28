#pragma once

#include "TimerTypes.h"

#include <memory>

namespace Structures {

class TimerImpl;

class Timer {
    constexpr static size_t infiniteTimesToShot = std::numeric_limits<size_t>::max();

public:
    Timer(Callback);
    ~Timer();

    void start(Duration timeout, size_t timesToShot = infiniteTimesToShot);
    void stop();

    auto callback() const -> Callback;
    auto timeout() const -> Duration;
    auto shotsLeft() const -> size_t;
    auto isStarted() const -> bool;

private:
    std::unique_ptr<TimerImpl> m_impl;
};

} // namespace Structures