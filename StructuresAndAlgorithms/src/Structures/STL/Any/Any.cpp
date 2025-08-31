#include "Any.h"

#include <string>

using namespace std;

namespace Structures::STL {

Any::Any()
    : ind(typeid(nullptr))
    , ptr(nullptr)
{
}

Any::~Any()
{
    reset();
}

void Any::reset()
{
    if (ind.hash_code() == typeid(int).hash_code()) {
        delete static_cast<int*>(ptr);
    } else if (ind.hash_code() == typeid(string).hash_code()) {
        delete static_cast<string*>(ptr);
    }
    ind = typeid(nullptr);
    ptr = nullptr;
}

} // namespace Structures::STL
