#include <type_traits>

/**
 * @brief Standard Layout is memcopy-able and can be consumed by C programs
 *
 * When a class or struct does not contain certain C++ language
 * features such as virtual functions which are not found in the
 * C language, and all members have the same access control,
 * it is a standard-layout type.
 *
 * It is memcopy-able and the layout is sufficiently defined
 * that it can be consumed by C programs. Standard-layout types
 * can have user-defined special member functions.
 * In addition, standard layout types have these characteristics:
 *      - no virtual functions or virtual base classes
 *      - all non-static data members have the same access control
 *      - all non-static members of class type are standard-layout
 *      - any base classes are standard-layout
 *      - has no base classes of the same type as the first non-static data member.
 *      - meets one of these conditions:
 *          - no non-static data member in the most-derived class and no more than one base class
 * with non-static data members, or
 *          - has no base classes with non-static data members
 *
 * https://learn.microsoft.com/en-us/cpp/cpp/trivial-standard-layout-and-pod-types?view=msvc-170
 */

namespace AreStandardLayout {

struct StandardLayout1 {
public:
    // Can contain user-defined constructor
    StandardLayout1()
    {
    }
    StandardLayout1(int a, int b)
        : i(a)
        , j(b)
    {
    }
    int i;
    int j;
};

struct StandardLayoutDerived : public StandardLayout1 {
public:
    void function()
    {
        // just function
    }
};

struct StandardLayout2 {
public:
    // Can contain default constructor
    StandardLayout2() = default;
    StandardLayout2(int a, int b)
        : i(a)
        , j(b)
    {
    }
    int i;
    int j;
};

} // namespace AreStandardLayout

namespace NotStandardLayout {

struct NonStandardLayoutDerived : public AreStandardLayout::StandardLayout1 {
public:
    // StandardLayout structure cannot have data member in both base and derived classes
    int b;
};

struct NonStandardLayout1 {
public:
    NonStandardLayout1()
    {
    }

    // StandardLayout structure cannot contain virtual function
    virtual void anyVirtualFunction()
    {
    }

    int a;
    int b;
};

struct NonStandardLayout2 {
public:
    int i;
    // Standard-layout cannot contain data members with different access control
private:
    int j;
};

} // namespace NotStandardLayout

int main()
{
    static_assert(std::is_standard_layout<AreStandardLayout::StandardLayout1>());
    static_assert(std::is_standard_layout<AreStandardLayout::StandardLayout2>());
    static_assert(std::is_standard_layout<AreStandardLayout::StandardLayoutDerived>());

    static_assert(!std::is_standard_layout<NotStandardLayout::NonStandardLayoutDerived>());
    static_assert(!std::is_standard_layout<NotStandardLayout::NonStandardLayout1>());
    static_assert(!std::is_standard_layout<NotStandardLayout::NonStandardLayout2>());

    return 0;
}