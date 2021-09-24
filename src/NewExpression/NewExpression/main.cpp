#include <bits/stdc++.h>

using namespace std;

// Function to call on bad_alloc exception
void noMemory()
{
    cout << "noMemory Called\n";
}

class A
{
public:
    A():a(1){}
    int a;
};

int main()
{
    // allocation and constr
    A* p1 = new A;
    cout << p1->a;

    // allocation and constr noexcept
    A* p2 = new(nothrow) A;
    cout << p2->a;

    // allocation, NO constr
    A* p3 = (A*)::operator new(sizeof(A));
    cout << p3->a;

    // NO allocation, constr
    new(p3) A;
    cout << p3->a;

    // function to call if new cannot allocate the memory
    std::set_new_handler( noMemory );
    // nothrow param - making new noexcept
    // On bad_alloc  - returns 0
    int *a = new(std::nothrow) int[ 0x7FFFFFFF ]; // try to allocate 2GB memory
    if( !a )
    {
        std::cout << "Cannot allocate 2Gb\n"; // Its impossible to allocate the memory
    }
    if( a )
    {
        std:: cout << "Success allocate 2Gb\n";
        delete[] a;
    }

    return 0;
}
