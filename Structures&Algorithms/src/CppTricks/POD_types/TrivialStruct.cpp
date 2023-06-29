#include <type_traits>

/**
 * @brief Trivial struct is memcopy-able, but it cannot be reliably consumed by C programs
 *
 * When a class or struct in C++ has compiler-provided or explicitly
 * defaulted special member functions, then it is a trivial type.
 * It occupies a contiguous memory area. It can have members with different
 * access specifiers. In C++, the compiler is free to choose how to order
 * members in this situation. Therefore, you can memcopy such objects but
 * you cannot reliably consume them from a C program.
 *
 * A trivial type T can be copied into an array of char or unsigned char,
 * and safely copied back into a T variable
 *
 * Trivial types have:
 *   trivial default constructor,
 *   trivial copy constructor,
 *   trivial copy assignment operator
 *   trivial destructor.
 * In each case, trivial means the constructor/operator/destructor
 *   is not user-provided and belongs to a class that has:
 *      - no virtual functions or virtual base classes,
 *      - no base classes with a corresponding non-trivial constructor/operator/destructor
 *      - no data members of class type with a corresponding non-trivial
 * constructor/operator/destructor
 *
 * https://learn.microsoft.com/en-us/cpp/cpp/trivial-standard-layout-and-pod-types?view=msvc-170
 */

namespace AreTrivial {

struct Trivial1 {
public:
    int i;
    void function()
    {
        // just function
    }

private:
    int j;
};

struct Trivial2 {
public:
    Trivial2() = default;
    Trivial2(int a, int b)
        : i(a)
        , j(b)
    {
    }
    int i;

private:
    int j; // Different access control
};

} // namespace AreTrivial

namespace NotTrivial {

struct NonTrivialBase {
public:
    // Trivial structure cannot contain virtual function
    virtual void anyVirtualFunction() { }
};

struct NonTrivialDerived : public NonTrivialBase {
public:
    // Trivial structure cannot contain virtual function
    void anyVirtualFunction() override { }
};

struct NonTrivial1 {
public:
    NonTrivial1() { }

    // Trivial structure cannot contain virtual function
    virtual void anyVirtualFunction() { }

    int a;
    int b;
};

struct NonTrivial2 {
public:
    // Trivial structure cannot contain user-defined constructor
    NonTrivial2() { }

    int a;
    int b;
};

struct NonTrivial3 {
public:
    NonTrivial3() = default;

    // Trivial structure cannot contain default member initialization
    // std::has_trivial_default_constructor<T1>() returns false
    int a = 0;
};

} // namespace NotTrivial

int main()
{
    static_assert(std::is_trivial<AreTrivial::Trivial1>());
    static_assert(std::is_trivial<AreTrivial::Trivial2>());

    static_assert(!std::is_trivial<NotTrivial::NonTrivialBase>());
    static_assert(!std::is_trivial<NotTrivial::NonTrivialDerived>());
    static_assert(!std::is_trivial<NotTrivial::NonTrivial1>());
    static_assert(!std::is_trivial<NotTrivial::NonTrivial2>());
    static_assert(!std::is_trivial<NotTrivial::NonTrivial3>());

    return 0;
}