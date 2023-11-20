#include "Event/Event.h"
#include "Helpers/TestHelper.h"

using namespace Multithreading;

class EventTest : public BaseTest {
public:
    void SetUp() override
    {
        clear();
    }

    void clear()
    {
        simpleCallback_calls = 0;
    }

    void simpleCallback()
    {
        ++simpleCallback_calls;
    }
    int simpleCallback_calls;
};

TEST_F(EventTest, creation)
{
    EXPECT_EQ(simpleCallback_calls, 0);
    Event event([this]() { this->simpleCallback(); });

    EXPECT_EQ(simpleCallback_calls, 0);

    constexpr auto times = 100;
    for (int i = 1; i <= times; ++i) {
        event.invoke();
        EXPECT_EQ(simpleCallback_calls, i);
    }
}

TEST_F(EventTest, deleting)
{
    EXPECT_EQ(simpleCallback_calls, 0);
    {
        Event event([this]() { this->simpleCallback(); });
    }
    EXPECT_EQ(simpleCallback_calls, 0);
}

TEST_F(EventTest, virtualizing)
{
    IEvent* event = new Event([this]() { this->simpleCallback(); });

    EXPECT_EQ(simpleCallback_calls, 0);

    constexpr auto times = 100;
    for (int i = 1; i <= times; ++i) {
        event->invoke();
        EXPECT_EQ(simpleCallback_calls, i);
    }

    clear();

    delete event;
    EXPECT_EQ(simpleCallback_calls, 0);
}