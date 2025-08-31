#include "Structures/Effective/Mediator/Mediator.h"

#include <gtest/gtest.h>

using namespace Structures;

TEST(Mediator, creation_empty)
{
    Mediator<int> mediator;
    EXPECT_TRUE(mediator.empty());
    EXPECT_THROW(mediator.getMedian(), EmptyMediatorException);
}

TEST(Mediator, addingValue_increasing)
{
    Mediator<int> mediator;
    mediator.add(1);
    EXPECT_EQ(1, mediator.getMedian());

    mediator.add(2);
    EXPECT_EQ(1, mediator.getMedian());

    mediator.add(3);
    EXPECT_EQ(2, mediator.getMedian());

    mediator.add(4);
    EXPECT_EQ(2, mediator.getMedian());

    mediator.add(5);
    EXPECT_EQ(3, mediator.getMedian());
}

TEST(Mediator, addingValue_decreasing)
{
    Mediator<int> mediator;

    mediator.add(5);
    EXPECT_EQ(5, mediator.getMedian());

    mediator.add(4);
    EXPECT_EQ(4, mediator.getMedian());

    mediator.add(3);
    EXPECT_EQ(4, mediator.getMedian());

    mediator.add(2);
    EXPECT_EQ(3, mediator.getMedian());

    mediator.add(1);
    EXPECT_EQ(3, mediator.getMedian());
}

TEST(Mediator, addingValue_different)
{
    Mediator<int> mediator;
    mediator.add(1);
    EXPECT_EQ(1, mediator.getMedian());

    mediator.add(10);
    EXPECT_EQ(1, mediator.getMedian());

    mediator.add(3);
    EXPECT_EQ(3, mediator.getMedian());

    mediator.add(8);
    EXPECT_EQ(3, mediator.getMedian());

    mediator.add(5);
    EXPECT_EQ(5, mediator.getMedian());

    mediator.add(7);
    EXPECT_EQ(5, mediator.getMedian());
}

TEST(Mediator, clear)
{
    Mediator<int> mediator;
    mediator.add(1);
    mediator.add(3);
    mediator.add(5);
    mediator.add(7);
    mediator.add(8);
    mediator.add(10);

    mediator.clear();
    EXPECT_TRUE(mediator.empty());
    EXPECT_THROW(mediator.getMedian(), EmptyMediatorException);
}

TEST(Mediator, erase)
{
    Mediator<int> mediator;
    mediator.add(1);
    mediator.add(3);
    mediator.add(5);
    mediator.add(7);
    mediator.add(8);
    mediator.add(10);

    mediator.erase(1);
    EXPECT_EQ(7, mediator.getMedian());

    mediator.erase(7);
    EXPECT_EQ(5, mediator.getMedian());

    mediator.erase(10);
    EXPECT_EQ(5, mediator.getMedian());

    mediator.erase(8);
    EXPECT_EQ(3, mediator.getMedian());

    mediator.erase(3);
    EXPECT_EQ(5, mediator.getMedian());

    mediator.erase(5);
    EXPECT_THROW(mediator.getMedian(), EmptyMediatorException);
    EXPECT_TRUE(mediator.empty());
}

TEST(Mediator, erase_sameValues)
{
    Mediator<int> mediator;
    mediator.add(1);
    mediator.add(1);
    mediator.add(1);
    mediator.add(1);
    mediator.add(10);
    mediator.add(10);

    mediator.erase(1);
    EXPECT_EQ(1, mediator.getMedian());

    mediator.erase(10);
    EXPECT_EQ(1, mediator.getMedian());

    mediator.erase(1);
    EXPECT_EQ(1, mediator.getMedian());

    mediator.erase(1);
    EXPECT_EQ(1, mediator.getMedian());

    mediator.erase(1);
    EXPECT_EQ(10, mediator.getMedian());
}
