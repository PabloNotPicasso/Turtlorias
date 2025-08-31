#include <iostream>

class Base {
public:
    virtual ~Base() = default;
    virtual void foo(std::string str = "default")
    {
        std::cout << "Base::foo(std::string str = \"default\" ) : " << str << std::endl;
    }
};

class Derived : public Base {
public:
    virtual ~Derived() = default;

    void foo(std::string str = "default") override
    {
        std::cout << "Derived::foo(std::string str = \"default\" ) : " << str << std::endl;
    }

    /**
     * @brief This function will never be called =(
     */
    void foo()
    {
        std::cout << "Derived::foo()" << std::endl;
    }
};

int main()
{
    Base* der = new Derived;
    der->foo();
    return 0;
}
