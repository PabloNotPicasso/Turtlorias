#include "Structures/SharedPointer/SharedPointer.h"

#include <gtest/gtest.h>

using namespace Structures;

class Dummy {
public:
};

TEST(SharedPtr, creation_empty)
{
    SharedPtr<Dummy> dummy_ptr;
    EXPECT_EQ(dummy_ptr.get(), nullptr);
}

TEST(SharedPtr, creation_dummy)
{
    SharedPtr<Dummy> dummy_ptr(new Dummy);
    EXPECT_NE(dummy_ptr.get(), nullptr);
}

TEST(SharedPtr, deleter)
{
    bool customDeleterIsCalled = false;
    SharedPtr<Dummy> dummy_ptr(new Dummy, [&customDeleterIsCalled](Dummy* object) {
        customDeleterIsCalled = true;
        delete object;
    });
    EXPECT_NE(dummy_ptr.get(), nullptr);
    dummy_ptr.reset();
    EXPECT_EQ(dummy_ptr.get(), nullptr);
    EXPECT_TRUE(customDeleterIsCalled);
}

TEST(SharedPtr, copy)
{
    Dummy* obj = new Dummy;
    SharedPtr<Dummy> dummy_ptr(obj);
    {
        SharedPtr<Dummy> ptr_copy = dummy_ptr;
        EXPECT_EQ(ptr_copy.get(), obj);
        dummy_ptr.reset();

        EXPECT_EQ(dummy_ptr.get(), nullptr);
        EXPECT_EQ(ptr_copy.get(), obj);

        ptr_copy.reset();
        EXPECT_EQ(ptr_copy.get(), nullptr);
    }
}
