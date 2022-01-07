#include <cassert>

namespace Dummy {

bool getTrue()
{
    return true;
}

bool getFalse()
{
    return false;
}

void throwInt()
{
    throw(int(1));
}

void toAssert()
{
    assert(false);
}

} // namespace Dummy