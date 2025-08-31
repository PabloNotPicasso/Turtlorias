#pragma once

#include "Helpers/TestHelper.h"
#include "Structures/STL/Containers/Vector/Vector.h"

#include <gtest/gtest.h>

class BaseVectorIteratorTest : public BaseTest {
public:
    void SetUp() override
    {
        vector = VectorInst({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    }

    using VectorInst = Structures::STL::Vector<int>;
    using VectorIterator = VectorInst::iterator;
    using VectorConstIterator = VectorInst::const_iterator;
    VectorInst vector;
};
