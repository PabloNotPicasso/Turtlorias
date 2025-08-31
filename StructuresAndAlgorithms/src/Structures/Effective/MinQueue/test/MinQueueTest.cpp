#include "Structures/Effective/MinQueue/MinQueue.h"

#include <gtest/gtest.h>

#include <queue>

using namespace Structures;

TEST(MinQueue, creation_empty)
{
    MinQueue<int> minqueue;
    EXPECT_TRUE(minqueue.empty());
    EXPECT_EQ(minqueue.size(), 0ULL);
}

TEST(MinQueue, differentTypes)
{
    MinQueue<char> minqueue_char;
    EXPECT_EQ(minqueue_char.currentMin(), MinQueue<char>::maxLimit());
    EXPECT_EQ(std::numeric_limits<char>::max(), MinQueue<char>::maxLimit());

    MinQueue<int> minqueue_int;
    EXPECT_EQ(minqueue_int.currentMin(), MinQueue<int>::maxLimit());
    EXPECT_EQ(std::numeric_limits<int>::max(), MinQueue<int>::maxLimit());

    MinQueue<long long> minqueue_ll;
    EXPECT_EQ(minqueue_ll.currentMin(), MinQueue<long long>::maxLimit());
    EXPECT_EQ(std::numeric_limits<long long>::max(), MinQueue<long long>::maxLimit());

    MinQueue<float> minqueue_float;
    EXPECT_EQ(minqueue_float.currentMin(), MinQueue<float>::maxLimit());
    EXPECT_EQ(std::numeric_limits<float>::max(), MinQueue<float>::maxLimit());

    MinQueue<double> minqueue_double;
    EXPECT_EQ(minqueue_double.currentMin(), MinQueue<double>::maxLimit());
    EXPECT_EQ(std::numeric_limits<double>::max(), MinQueue<double>::maxLimit());
}

TEST(MinQueue, push)
{
    MinQueue<int> minqueue;
    constexpr int PushTimes = 100'000;
    for (int i = 0; i < PushTimes; ++i) {
        minqueue.push(i);
    }

    EXPECT_FALSE(minqueue.empty());
    EXPECT_EQ(minqueue.size(), PushTimes);
}

TEST(MinQueue, pop)
{
    MinQueue<int> minqueue;
    constexpr int PushTimes = 100'000;
    for (int i = 0; i < PushTimes; ++i) {
        minqueue.push(i);
    }

    constexpr int PopTimes = PushTimes / 2;
    for (int i = 0; i < PopTimes; ++i) {
        minqueue.pop();
    }

    EXPECT_FALSE(minqueue.empty());
    EXPECT_EQ(minqueue.size(), PushTimes - PopTimes);
}

TEST(MinQueue, currentMin)
{
    MinQueue<int> minqueue;
    constexpr int PushTimes = 100'000;
    for (int i = 0; i < PushTimes; ++i) {
        minqueue.push(i);
        EXPECT_EQ(minqueue.currentMin(), 0);
    }

    constexpr int PopTimes = PushTimes / 2;
    for (int i = 0; i < PopTimes; ++i) {
        EXPECT_EQ(minqueue.currentMin(), i);
        minqueue.pop();
    }
}

TEST(MinQueue, currentMin_mixed)
{
    MinQueue<int> minqueue;
    minqueue.push(10);
    minqueue.pop();
    EXPECT_TRUE(minqueue.empty());
    EXPECT_EQ(minqueue.size(), 0ULL);

    minqueue.push(7);
    // [7]
    EXPECT_EQ(minqueue.currentMin(), 7);

    minqueue.push(10);
    // [7, 10]
    EXPECT_EQ(minqueue.currentMin(), 7);

    minqueue.push(5);
    // [7, 10, 5]
    EXPECT_EQ(minqueue.currentMin(), 5);

    minqueue.push(3);
    // [7, 10, 5, 3]
    EXPECT_EQ(minqueue.currentMin(), 3);

    minqueue.push(100);
    // [7, 10, 5, 3, 100]
    EXPECT_EQ(minqueue.currentMin(), 3);

    minqueue.pop();
    EXPECT_EQ(minqueue.currentMin(), 3);
    // [10, 5, 3, 100]

    minqueue.pop();
    EXPECT_EQ(minqueue.currentMin(), 3);
    // [5, 3, 100]

    minqueue.pop();
    EXPECT_EQ(minqueue.currentMin(), 3);
    // [3, 100]

    minqueue.pop();
    EXPECT_EQ(minqueue.currentMin(), 100);
    // [100]
}

/**
 * @brief Random tests together with brute force MinQueue
 *
 */
template<typename Numeric>
class BruteMinQueue : public MinQueueBase<Numeric> {
public:
    void push(const Numeric x)
    {
        queue.push(x);
    }

    void pop()
    {
        if (!empty()) {
            queue.pop();
        }
    }

    bool empty() const
    {
        return queue.empty();
    }

    size_t size() const
    {
        return queue.size();
    }

    Numeric currentMin() const
    {
        if (queue.empty()) {
            return BruteMinQueue::maxLimit();
        }
        auto copyQueue = queue;
        std::vector<Numeric> elements;
        while (!copyQueue.empty()) {
            elements.push_back(copyQueue.front());
            copyQueue.pop();
        }
        return *std::min_element(begin(elements), end(elements));
    }

private:
    std::queue<Numeric> queue;
};

enum operationType {
    PUSH,
    POP,
};

TEST(MinQueue, randomQueue)
{
    MinQueue<int> minqueue;
    BruteMinQueue<int> bruteMinqueue;

    auto checkEqual = [&]() {
        EXPECT_EQ(minqueue.currentMin(), bruteMinqueue.currentMin());
        EXPECT_EQ(minqueue.size(), bruteMinqueue.size());
        EXPECT_EQ(minqueue.empty(), bruteMinqueue.empty());
    };

    auto pushRandom = [&]() {
        int generated = rand();
        minqueue.push(generated);
        bruteMinqueue.push(generated);
    };
    auto pop = [&]() {
        minqueue.pop();
        bruteMinqueue.pop();
    };

    constexpr int OperationNumber = 100'000;
    for (int i = 0; i < OperationNumber; ++i) {
        operationType op = rand() % 2 ? PUSH : POP;
        switch (op) {
        case PUSH:
            pushRandom();
            break;
        case POP:
            pop();
            break;
        default:
            break;
        }
        checkEqual();
    }
}
