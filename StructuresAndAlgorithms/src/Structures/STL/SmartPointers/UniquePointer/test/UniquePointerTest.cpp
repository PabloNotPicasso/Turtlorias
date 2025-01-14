#include "Structures/STL/SmartPointers/UniquePointer/UniquePointer.h"

#include <gtest/gtest.h>

using namespace Structures::STL;

class Dummy {
public:
    void f()
    {
        ++cnt;
    }
    int cnt = 0;
};

TEST(UniquePointer, creation_empty)
{
    UniquePtr<Dummy> dummy_ptr;
    EXPECT_EQ(dummy_ptr.get(), nullptr);
}

TEST(UniquePtr, creation_dummy)
{
    UniquePtr<Dummy> dummy_ptr(new Dummy);
    EXPECT_NE(dummy_ptr.get(), nullptr);
}

TEST(UniquePtr, deleter)
{
    bool customDeleterIsCalled = false;

    struct Deleter {
        bool& _customDeleterIsCalled;
        constexpr Deleter(bool& customDeleterIsCalled)
            : _customDeleterIsCalled{customDeleterIsCalled}
        {
        }
        ~Deleter() = default;
        void operator()(Dummy* object) const
        {
            _customDeleterIsCalled = true;
            delete object;
        }
    } deleter(customDeleterIsCalled);

    UniquePtr<Dummy, Deleter> dummy_ptr(new Dummy, deleter);
    EXPECT_NE(dummy_ptr.get(), nullptr);
    EXPECT_FALSE(customDeleterIsCalled);
    dummy_ptr.reset();
    EXPECT_EQ(dummy_ptr.get(), nullptr);
    EXPECT_TRUE(customDeleterIsCalled);
}

TEST(UniquePtr, move)
{
    UniquePtr<int> ptr1(new int(100));
    UniquePtr<int> ptr2 = std::move(ptr1);
    EXPECT_EQ(ptr1.get(), nullptr);
    EXPECT_EQ(*ptr2, 100);
}

TEST(UniquePtr, self_move)
{
    UniquePtr<int> ptr1(new int(200));
    ptr1 = std::move(ptr1);
    EXPECT_EQ(*ptr1, 200);
}

TEST(UniquePtr, reset)
{
    UniquePtr<Dummy> ptr1(new Dummy);
    EXPECT_NE(ptr1.get(), nullptr);
    ptr1.reset();
    EXPECT_EQ(ptr1.get(), nullptr);
    ptr1.reset();
    ptr1.reset(new Dummy);
    EXPECT_NE(ptr1.get(), nullptr);
}

TEST(UniquePtr, dereferencing)
{
    UniquePtr<int> ptr1(new int(50));
    EXPECT_EQ(*ptr1, 50);

    ptr1.reset(new int(1));
    EXPECT_EQ(*ptr1, 1);
}

TEST(UniquePtr, functionCall)
{
    UniquePtr<Dummy> ptr1(new Dummy);
    EXPECT_EQ(ptr1->cnt, 0);
    ptr1->f();
    EXPECT_EQ(ptr1->cnt, 1);
}
