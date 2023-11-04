#include "Helpers/TestHelper.h"
#include "Structures/STL/Containers/Vector/Vector.h"

#include <gtest/gtest.h>

using namespace Structures::STL;

class VectorTest : public BaseTest { };

TEST_F(VectorTest, creation_empty)
{
    Vector<Dummy> vector;

    EXPECT_EQ(vector.size(), 0);
    EXPECT_EQ(vector.capacity(), 1);

    EXPECT_EQ(0, TestHelper::existingCopies);
    EXPECT_EQ(0, TestHelper::constructorCnt);
    EXPECT_EQ(0, TestHelper::destructorCnt);
    EXPECT_EQ(0, TestHelper::copyConstructorCnt);
    EXPECT_EQ(0, TestHelper::copyAssignCnt);
    EXPECT_EQ(0, TestHelper::moveConstructorCnt);
    EXPECT_EQ(0, TestHelper::moveAssignCnt);
}

TEST_F(VectorTest, creation_constructing)
{
    size_t size = 10;
    Vector<Dummy> vector(size);

    EXPECT_EQ(vector.size(), size);
    EXPECT_EQ(vector.capacity(), size);

    for (size_t i = 0; i < vector.size(); ++i) {
        EXPECT_EQ(vector[i].data, Dummy::initialDataString);
        EXPECT_EQ(vector.at(i).data, Dummy::initialDataString);
    }

    EXPECT_EQ(10, TestHelper::existingCopies);
    EXPECT_EQ(10, TestHelper::constructorCnt);
    EXPECT_EQ(0, TestHelper::destructorCnt);
    EXPECT_EQ(0, TestHelper::copyConstructorCnt);
    EXPECT_EQ(0, TestHelper::copyAssignCnt);
    EXPECT_EQ(0, TestHelper::moveConstructorCnt);
    EXPECT_EQ(0, TestHelper::moveAssignCnt);
}

TEST_F(VectorTest, creation_copy)
{
    Dummy dummy;
    dummy.data = "SomeOtherData";
    size_t newSize = 10;
    Vector<Dummy> vector(newSize, dummy);

    for (size_t i = 0; i < vector.size(); ++i) {
        EXPECT_EQ(vector[i].data, dummy.data);
        EXPECT_EQ(vector.at(i).data, dummy.data);
    }

    EXPECT_EQ(vector.size(), newSize);
    EXPECT_EQ(vector.capacity(), newSize);

    EXPECT_EQ(11, TestHelper::existingCopies);
    EXPECT_EQ(1, TestHelper::constructorCnt);
    EXPECT_EQ(0, TestHelper::destructorCnt);
    EXPECT_EQ(10, TestHelper::copyConstructorCnt);
    EXPECT_EQ(0, TestHelper::copyAssignCnt);
    EXPECT_EQ(0, TestHelper::moveConstructorCnt);
    EXPECT_EQ(0, TestHelper::moveAssignCnt);
}

TEST_F(VectorTest, reserve)
{
    size_t newSize = 10;
    Vector<Dummy> vector;

    vector.reserve(newSize);

    EXPECT_EQ(vector.size(), 0);
    EXPECT_EQ(vector.capacity(), newSize);

    EXPECT_EQ(0, TestHelper::existingCopies);
    EXPECT_EQ(0, TestHelper::constructorCnt);
    EXPECT_EQ(0, TestHelper::destructorCnt);
    EXPECT_EQ(0, TestHelper::copyConstructorCnt);
    EXPECT_EQ(0, TestHelper::copyAssignCnt);
    EXPECT_EQ(0, TestHelper::moveConstructorCnt);
    EXPECT_EQ(0, TestHelper::moveAssignCnt);
}

TEST_F(VectorTest, resize_empty)
{
    size_t newSize = 10;
    Vector<Dummy> vector;

    vector.resize(newSize);

    EXPECT_EQ(vector.size(), newSize);
    EXPECT_EQ(vector.capacity(), newSize);

    for (size_t i = 0; i < vector.size(); ++i) {
        EXPECT_EQ(vector[i].data, Dummy::initialDataString);
    }

    EXPECT_EQ(10, TestHelper::existingCopies);
    EXPECT_EQ(10, TestHelper::constructorCnt);
    EXPECT_EQ(0, TestHelper::destructorCnt);
    EXPECT_EQ(0, TestHelper::copyConstructorCnt);
    EXPECT_EQ(0, TestHelper::copyAssignCnt);
    EXPECT_EQ(0, TestHelper::moveConstructorCnt);
    EXPECT_EQ(0, TestHelper::moveAssignCnt);
}

TEST_F(VectorTest, resize_with_value)
{
    Dummy dummy;
    dummy.data = "someOTherString";
    size_t newSize = 10;
    Vector<Dummy> vector;

    vector.resize(newSize, dummy);

    EXPECT_EQ(vector.size(), newSize);
    EXPECT_EQ(vector.capacity(), newSize);

    for (size_t i = 0; i < vector.size(); ++i) {
        EXPECT_EQ(vector[i].data, dummy.data);
    }

    EXPECT_EQ(11, TestHelper::existingCopies);
    EXPECT_EQ(1, TestHelper::constructorCnt);
    EXPECT_EQ(0, TestHelper::destructorCnt);
    EXPECT_EQ(10, TestHelper::copyConstructorCnt);
    EXPECT_EQ(0, TestHelper::copyAssignCnt);
    EXPECT_EQ(0, TestHelper::moveConstructorCnt);
    EXPECT_EQ(0, TestHelper::moveAssignCnt);
}

TEST_F(VectorTest, push_back_copy)
{
    Dummy dummy;
    Vector<Dummy> vector;
    vector.push_back(dummy);

    EXPECT_EQ(vector.size(), 1);
    EXPECT_EQ(vector.capacity(), 1);

    EXPECT_EQ(2, TestHelper::existingCopies);
    EXPECT_EQ(1, TestHelper::constructorCnt);
    EXPECT_EQ(0, TestHelper::destructorCnt);
    EXPECT_EQ(1, TestHelper::copyConstructorCnt);
    EXPECT_EQ(0, TestHelper::copyAssignCnt);
    EXPECT_EQ(0, TestHelper::moveConstructorCnt);
    EXPECT_EQ(0, TestHelper::moveAssignCnt);
}

TEST_F(VectorTest, push_back_move)
{
    Dummy dummy;
    Vector<Dummy> vector;
    vector.push_back(std::move(dummy));

    EXPECT_EQ(vector.size(), 1);
    EXPECT_EQ(vector.capacity(), 1);

    EXPECT_EQ(vector[0].data, Dummy::initialDataString);
    EXPECT_EQ(dummy.data, "");

    EXPECT_EQ(2, TestHelper::existingCopies);
    EXPECT_EQ(1, TestHelper::constructorCnt);
    EXPECT_EQ(0, TestHelper::destructorCnt);
    EXPECT_EQ(0, TestHelper::copyConstructorCnt);
    EXPECT_EQ(0, TestHelper::copyAssignCnt);
    EXPECT_EQ(1, TestHelper::moveConstructorCnt);
    EXPECT_EQ(0, TestHelper::moveAssignCnt);
}

TEST_F(VectorTest, emplace_back)
{
    Vector<Dummy> vector;

    const std::string myData = "MyData";

    vector.emplace_back(myData);
    EXPECT_EQ(vector.size(), 1);
    EXPECT_EQ(vector.capacity(), 1);
    EXPECT_EQ(vector.back().data, myData);

    EXPECT_EQ(1, TestHelper::existingCopies);
    EXPECT_EQ(1, TestHelper::constructorCnt);
    EXPECT_EQ(0, TestHelper::destructorCnt);
    EXPECT_EQ(0, TestHelper::copyConstructorCnt);
    EXPECT_EQ(0, TestHelper::copyAssignCnt);
    EXPECT_EQ(0, TestHelper::moveConstructorCnt);
    EXPECT_EQ(0, TestHelper::moveAssignCnt);

    vector.emplace_back(myData);
    EXPECT_EQ(vector.size(), 2);
    EXPECT_EQ(vector.capacity(), 2);
    EXPECT_EQ(vector.back().data, myData);

    EXPECT_EQ(2, TestHelper::existingCopies);
    EXPECT_EQ(2, TestHelper::constructorCnt);
    EXPECT_EQ(1, TestHelper::destructorCnt);
    EXPECT_EQ(1, TestHelper::copyConstructorCnt);
    EXPECT_EQ(0, TestHelper::copyAssignCnt);
    EXPECT_EQ(0, TestHelper::moveConstructorCnt);
    EXPECT_EQ(0, TestHelper::moveAssignCnt);
}

TEST_F(VectorTest, at_exception)
{
    Vector<Dummy> vector;

    EXPECT_ANY_THROW(vector.at(10););

    EXPECT_EQ(0, TestHelper::existingCopies);
    EXPECT_EQ(0, TestHelper::constructorCnt);
    EXPECT_EQ(0, TestHelper::destructorCnt);
    EXPECT_EQ(0, TestHelper::copyConstructorCnt);
    EXPECT_EQ(0, TestHelper::copyAssignCnt);
    EXPECT_EQ(0, TestHelper::moveConstructorCnt);
    EXPECT_EQ(0, TestHelper::moveAssignCnt);
}

TEST_F(VectorTest, insert)
{
    const size_t size = 10;
    Vector<Dummy> vector(size);

    const size_t insertPosition = 5;
    vector.insert(insertPosition, withDataDummy);
    const size_t newSize = size + 1;
    EXPECT_EQ(vector.size(), newSize);
    EXPECT_EQ(vector.capacity(), size * 2);

    EXPECT_EQ(vector[insertPosition].data, withDataDummy.data);
    for (size_t i = 0; i < insertPosition; ++i) {
        EXPECT_EQ(vector[i].data, uninitializedDummy.data);
    }
    for (size_t i = insertPosition + 1; i < newSize; ++i) {
        EXPECT_EQ(vector[i].data, uninitializedDummy.data);
    }

    EXPECT_EQ(11, TestHelper::existingCopies);
    EXPECT_EQ(10, TestHelper::constructorCnt);
    EXPECT_EQ(10, TestHelper::destructorCnt);
    EXPECT_EQ(11, TestHelper::copyConstructorCnt);
    EXPECT_EQ(0, TestHelper::copyAssignCnt);
    EXPECT_EQ(0, TestHelper::moveConstructorCnt);
    EXPECT_EQ(0, TestHelper::moveAssignCnt);
}