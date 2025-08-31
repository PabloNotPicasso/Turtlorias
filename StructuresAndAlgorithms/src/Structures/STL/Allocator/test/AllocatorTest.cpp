#include "Structures/STL/Allocator/Allocator.h"
#include "Structures/STL/Containers/Vector/Vector.h"

#include <gtest/gtest.h>

using namespace Structures::STL;

class Dummy {
public:
    static constexpr std::string_view initialDataString = "InitialDataString";
    std::string data;

    Dummy()
        : Dummy(initialDataString)
    {
    }

    Dummy(const std::string_view& dataToInitialize)
        : data(dataToInitialize)
    {
    }
};

TEST(Allocator, vectorTest)
{
    const size_t size = 10;
    Vector<Dummy, Allocator<Dummy>> vector(size);
}
