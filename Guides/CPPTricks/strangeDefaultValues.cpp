#include<bits/stdc++.h>

using namespace std;

class Base
{
public:
    virtual ~Base() = default;
    virtual void foo(std::string str = "default" ){
        cout << "Base::foo(std::string str = \"default\" ) : " << str << endl;
    }
};

class Derived : public Base
{
    public:
    virtual ~Derived() = default;

    void foo(std::string str = "default" ) override
    {
        cout << "Derived::foo(std::string str = \"default\" ) : " << str << endl;
    }

    void foo()
    {
        cout << "Derived::foo()" << endl;
    }
};


int main()
{
    Base* der = new Derived;
    der->foo();
    return 0;
}