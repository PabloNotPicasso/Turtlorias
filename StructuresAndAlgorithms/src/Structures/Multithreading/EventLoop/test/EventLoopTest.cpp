#include "Helpers/TestHelper.h"
#include "Structures/Multithreading/EventLoop/EventLoop.h"

using namespace Multithreading;

class EventLoopTest : public BaseTest {
public:
    void SetUp() override
    {
        BaseTest::SetUp();
        eventLoop.run();
        eventLoopThreadId = eventLoop.threadId();
    }

    EventLoop eventLoop;

    std::thread::id eventLoopThreadId;
};

TEST_F(EventLoopTest, creation)
{
    EventLoop el;
    EXPECT_FALSE(el.isRunning());
    el.run();
    EXPECT_TRUE(el.isRunning());
    el.shutdown();
    EXPECT_FALSE(el.isRunning());
}

TEST_F(EventLoopTest, postEvent)
{
    std::thread::id eventThreadId;

    auto eventCallback = [&eventThreadId]() { eventThreadId = std::this_thread::get_id(); };

    eventLoop.postEvent(eventCallback);
    eventLoop.shutdown();

    EXPECT_EQ(eventThreadId, eventLoopThreadId);
}

TEST_F(EventLoopTest, postEventRepeated)
{
    int callsCount = 0;

    std::function<void()> eventCallback;
    eventCallback = [&]() {
        ++callsCount;
        eventLoop.postEvent(eventCallback);
    };

    eventLoop.postEvent(eventCallback);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    eventLoop.shutdown();

    EXPECT_GT(callsCount, 1);
}