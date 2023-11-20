#include "Helpers/TestHelper.h"
#include "Signal/Signal.h"

using namespace Multithreading;

class SignalTest : public BaseTest {
public:
    void SetUp() override
    {
        BaseTest::SetUp();
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

TEST_F(SignalTest, creation)
{
    EXPECT_EQ(simpleCallback_calls, 0);
    Signal<int> signal;
    EXPECT_EQ(simpleCallback_calls, 0);

    constexpr auto times = 100;
    for (int i = 1; i <= times; ++i) {
        signal(i);
        EXPECT_EQ(simpleCallback_calls, 0);
    }
}

TEST_F(SignalTest, connect)
{
    Signal<int> signal;
    Slot<int> slot([this](int) { this->simpleCallback(); });
    signal.connect(slot);

    constexpr auto times = 100;
    for (int i = 1; i <= times; ++i) {
        signal(i);
        EXPECT_EQ(simpleCallback_calls, i);
    }
    EXPECT_EQ(signal.num_slots(), 1);
}

TEST_F(SignalTest, disconnect)
{
    Signal<int> signal;
    Slot<int> slot([this](int) { this->simpleCallback(); });
    auto connectionId = signal.connect(slot);
    signal.disconnect(connectionId);

    signal(0);
    EXPECT_EQ(simpleCallback_calls, 0);
    EXPECT_EQ(signal.num_slots(), 0);
}

TEST_F(SignalTest, disconnectAll)
{
    Signal<int> signal;

    constexpr int slotsToConnect = 100;
    for (int i = 0; i < slotsToConnect; ++i) {
        Slot<int> slot([this](int) { this->simpleCallback(); });
        auto connectionId = signal.connect(slot);
    }
    EXPECT_EQ(signal.num_slots(), slotsToConnect);

    signal.disconnectAll();
    EXPECT_EQ(signal.num_slots(), 0);

    signal(0);
    EXPECT_EQ(simpleCallback_calls, 0);
}

TEST_F(SignalTest, argumentCapturing)
{
    Signal<int> signal;
    int receivedValue = 0;
    Slot<int> slot([this, &receivedValue](int arg) { receivedValue = arg; });
    signal.connect(slot);

    for (int i = 0; i < 100; ++i) {
        signal(i);
        EXPECT_EQ(receivedValue, i);
    }
    EXPECT_EQ(simpleCallback_calls, 0);
}

TEST_F(SignalTest, valueArg)
{
    Signal<Dummy> signal;
    Slot<Dummy> slot([this](const Dummy&) {});
    signal.connect(slot);

    Dummy toSend("signal");

    TestHelper::reset();
    constexpr auto timesToEmitSignal = 1;
    for (int i = 0; i < timesToEmitSignal; ++i) {
        signal(toSend);
    }
    EXPECT_EQ(0, TestHelper::existingCopies);
    EXPECT_EQ(0, TestHelper::constructorCnt);
    EXPECT_EQ(3, TestHelper::destructorCnt);
    EXPECT_EQ(2, TestHelper::copyConstructorCnt);
    EXPECT_EQ(0, TestHelper::copyAssignCnt);
    EXPECT_EQ(1, TestHelper::moveConstructorCnt);
    EXPECT_EQ(0, TestHelper::moveAssignCnt);
}

TEST_F(SignalTest, referenceArg)
{
    Signal<const Dummy&> signal;
    Slot<const Dummy&> slot([this](const Dummy& arg) {});
    signal.connect(slot);

    Dummy toSend("signal");

    TestHelper::reset();
    constexpr auto timesToEmitSignal = 10;
    for (int i = 0; i < timesToEmitSignal; ++i) {
        signal(toSend);
    }
    EXPECT_EQ(0, TestHelper::existingCopies);
    EXPECT_EQ(0, TestHelper::constructorCnt);
    EXPECT_EQ(0, TestHelper::destructorCnt);
    EXPECT_EQ(0, TestHelper::copyConstructorCnt);
    EXPECT_EQ(0, TestHelper::copyAssignCnt);
    EXPECT_EQ(0, TestHelper::moveConstructorCnt);
    EXPECT_EQ(0, TestHelper::moveAssignCnt);
}

TEST_F(SignalTest, fewSlots)
{
    Signal<int> signal;
    std::vector<Signal<int>::SlotT> slots(
        10, Signal<int>::SlotT([this](int) { this->simpleCallback(); }));

    for (auto slot : slots) {
        signal.connect(slot);
    }

    signal(0);
    EXPECT_EQ(simpleCallback_calls, slots.size());
}