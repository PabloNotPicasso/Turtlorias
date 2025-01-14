#include "Structures/STL/SmartPointers/SharedPointer/SharedPointer.h"

#include <gtest/gtest.h>

using namespace Structures::STL;

class Dummy {
public:
    void f() {
        ++cnt;
    }
    int cnt = 0;
};

TEST(SharedPtr, creation_empty)
{
    SharedPtr<Dummy> dummy_ptr;
    EXPECT_EQ(dummy_ptr.get(), nullptr);
    EXPECT_EQ(dummy_ptr.use_count(), 0);
}

TEST(SharedPtr, creation_dummy)
{
    SharedPtr<Dummy> dummy_ptr(new Dummy);
    EXPECT_NE(dummy_ptr.get(), nullptr);
    EXPECT_EQ(dummy_ptr.use_count(), 1);
}

TEST(SharedPtr, deleter)
{
    bool customDeleterIsCalled = false;
    SharedPtr<Dummy> dummy_ptr(new Dummy, [&customDeleterIsCalled](Dummy* object) {
        customDeleterIsCalled = true;
        delete object;
    });
    EXPECT_EQ(dummy_ptr.use_count(), 1);
    EXPECT_NE(dummy_ptr.get(), nullptr);
    dummy_ptr.reset();
    EXPECT_EQ(dummy_ptr.use_count(), 0);
    EXPECT_EQ(dummy_ptr.get(), nullptr);
    EXPECT_TRUE(customDeleterIsCalled);
}

TEST(SharedPtr, copy)
{
    Dummy* obj = new Dummy;
    SharedPtr<Dummy> dummy_ptr(obj);
    {
        SharedPtr<Dummy> ptr_copy = dummy_ptr;
        EXPECT_EQ(dummy_ptr.use_count(), 2);
        EXPECT_EQ(ptr_copy.use_count(), 2);
        EXPECT_EQ(ptr_copy.get(), obj);
        dummy_ptr.reset();

        EXPECT_EQ(dummy_ptr.use_count(), 0);
        EXPECT_EQ(dummy_ptr.get(), nullptr);
        EXPECT_EQ(ptr_copy.use_count(), 1);
        EXPECT_EQ(ptr_copy.get(), obj);

        ptr_copy.reset();
        EXPECT_EQ(ptr_copy.use_count(), 0);
        EXPECT_EQ(ptr_copy.get(), nullptr);
    }
}
TEST(SharedPtr, copy_empty)
{
    SharedPtr<Dummy> ptr1;
    SharedPtr<Dummy> ptr2 = ptr1;
    EXPECT_EQ(ptr1.use_count(), 0);
    EXPECT_EQ(ptr1.get(), nullptr);
    EXPECT_EQ(ptr2.use_count(), 0);
    EXPECT_EQ(ptr2.get(), nullptr);
}

TEST(SharedPtr, move)
{
    SharedPtr<int> ptr1(new int(100));
    SharedPtr<int> ptr2 = std::move(ptr1);
    EXPECT_EQ(ptr1.use_count(), 0);
    EXPECT_EQ(ptr2.use_count(), 1);
    EXPECT_EQ(*ptr2, 100);
}

TEST(SharedPtr, self_assignment)
{
    SharedPtr<int> ptr1(new int(200));
    ptr1 = ptr1;
    EXPECT_EQ(ptr1.use_count(), 1);
    EXPECT_EQ(*ptr1, 200);
}

TEST(SharedPtr, reset)
{
    SharedPtr<Dummy> ptr1(new Dummy);
    {
        SharedPtr<Dummy> ptr2 = ptr1;
        SharedPtr<Dummy> ptr3 = ptr2;
        EXPECT_EQ(ptr1.use_count(), 3);
    }
    EXPECT_EQ(ptr1.use_count(), 1);
    ptr1.reset();
    EXPECT_EQ(ptr1.use_count(), 0);
    ptr1.reset();
    EXPECT_EQ(ptr1.use_count(), 0);

    ptr1.reset(new Dummy);
    EXPECT_EQ(ptr1.use_count(), 1);
}

TEST(SharedPtr, dereferencing)
{
    SharedPtr<int> ptr1(new int(50));
    EXPECT_EQ(ptr1.use_count(), 1);
    EXPECT_EQ(*ptr1, 50);
    ptr1.reset(new int(1));
    EXPECT_EQ(ptr1.use_count(), 1);
    EXPECT_EQ(*ptr1, 1);
}

TEST(SharedPtr, functionCall)
{
    SharedPtr<Dummy> ptr1(new Dummy);
    EXPECT_EQ(ptr1->cnt, 0);
    ptr1->f();
    EXPECT_EQ(ptr1->cnt, 1);
}
