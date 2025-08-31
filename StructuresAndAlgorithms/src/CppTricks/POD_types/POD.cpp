#include <type_traits>

/**
 * @brief POD type is both StandardLayout and Trivial struct
 *
 * When a class or struct is both trivial and standard-layout,
 * it is a POD (Plain Old Data) type. The memory layout of POD
 * types is therefore contiguous and each member has a higher
 * address than the member that was declared before it, so
 * that byte for byte copies and binary I/O can be performed
 * on these types. Scalar types such as int are also POD types.
 * POD types that are classes can have only POD types
 * as non-static data members.
 *
 * https://learn.microsoft.com/en-us/cpp/cpp/trivial-standard-layout-and-pod-types?view=msvc-170
 */

namespace ArePOD {

struct POD1 {
public:
    POD1() = default;
    POD1(int a, int b)
        : i(a)
        , j(b)
    {
    }
    void function()
    {
        // just function
    }
    int i;
    int j;
};

struct PODDerived : public POD1 {
public:
    PODDerived() = default;
    PODDerived(int a, int b)
        : POD1(a, b)
    {
    }
    void otherFunction()
    {
        // just function
    }
};

} // namespace ArePOD

namespace NotPOD {

struct NonPODBase {
public:
    // POD structure cannot contain virtual function
    virtual void anyVirtualFunction() { }
};

struct NonPODDerived : public NonPODBase {
public:
    // POD structure cannot contain virtual function
    void anyVirtualFunction() override { }
};

struct NonPOD1 {
public:
    NonPOD1() { }

    // POD structure cannot contain virtual function
    virtual void anyVirtualFunction() { }

    int a;
    int b;
};

struct NonPOD2 {
public:
    // POD structure cannot contain user-defined constructor
    NonPOD2() { }

    int a;
    int b;
};

struct NonPOD3 {
public:
    // POD structure cannot contain user-defined constructor
    NonPOD3() { }

    int a;

    // POD cannot contain data members with different access control
private:
    int b;
};

} // namespace NotPOD

int main()
{
    // std::is_pod is equal to std::is_standard_layout && std::is_trivial
    static_assert(std::is_pod<ArePOD::POD1>());
    static_assert(std::is_pod<ArePOD::PODDerived>());

    static_assert(!std::is_pod<NotPOD::NonPODBase>());
    static_assert(!std::is_pod<NotPOD::NonPODDerived>());
    static_assert(!std::is_pod<NotPOD::NonPOD1>());
    static_assert(!std::is_pod<NotPOD::NonPOD2>());
    static_assert(!std::is_pod<NotPOD::NonPOD3>());

    return 0;
}
