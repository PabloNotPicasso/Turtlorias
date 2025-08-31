#include "Logger/LoggerApi.h"
#include "Structures/Multithreading/Timer/TimerAPI.h"

#include <gtest/gtest.h>

#include <thread>

using namespace Structures;
using namespace std::chrono_literals;

TEST(Timer, test)
{
    Timer fastTimer([]() { LOG_INF("fastTimer is elapsed"); });

    fastTimer.start(1s, 10);

    std::this_thread::sleep_for(2s);
    fastTimer.stop();

    std::this_thread::sleep_for(1s);
}

TEST(Timer, slowTimerTest)
{
    Timer slowTimer([]() {
        LOG_INF("slowTimer is elapsed");
        std::this_thread::sleep_for(1s);
    });
    Timer fastTimer([]() { LOG_INF("fastTimer is elapsed"); });

    slowTimer.start(1s, 10);
    std::this_thread::sleep_for(500ms);
    fastTimer.start(1s, 10);

    std::this_thread::sleep_for(5s);
    slowTimer.stop();
    fastTimer.stop();
    std::this_thread::sleep_for(50ms);
}
