#pragma once

#include <chrono>
#include <functional>

using Callback = std::function<void()>;

using Clock = std::chrono::steady_clock;
using Timestamp = Clock::time_point;
using Duration = std::chrono::milliseconds;
