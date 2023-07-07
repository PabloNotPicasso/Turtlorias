#pragma once

#include "CppTricks/FastPIMPL/FastPimple.h"

namespace thirdparty {
class origin;
} // namespace thirdparty

class Adapter {
public:
    Adapter();
    Adapter(Adapter&& other);
    Adapter& operator=(Adapter&& other);
    ~Adapter();

    void useOrigin();

private:
    using wrappedType = thirdparty::origin;

    constexpr static size_t Size{1};
    constexpr static size_t Alignment{1};

    FastPimple<wrappedType, Size, Alignment> pimple;
};