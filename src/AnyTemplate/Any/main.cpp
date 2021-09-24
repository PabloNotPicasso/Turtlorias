#include <iostream>
#include <vector>
#include <memory>
#include <iostream>
#include <typeinfo>
#include <typeindex>

using namespace std;


class any
{
public:
    type_index ind;
    void* ptr;
    any() : ind( typeid(nullptr) )
    {
        ptr = nullptr;
    }

    template<typename T>
    any( const T& obj ) : ind(typeid (T))
    {
        ptr = new T(obj);
    }

    template<typename T>
    bool is()
    {
        return typeid(T).hash_code() == ind.hash_code();
    }

    template<typename T>
    T as()
    {
        return *( static_cast<T*>(ptr) );
    }

    template<typename T>
    any& operator =( const T& obj )
    {
        reset();
        ptr = new T(obj);
        ind = typeid(T);
        return *this;
    }

    void reset()
    {
        if( ind.hash_code() == typeid(int).hash_code() )
        {
            delete static_cast<int*>(ptr);
        }
        else if( ind.hash_code() == typeid(string).hash_code() )
        {
            delete static_cast<string*>(ptr);
        }
        ptr = nullptr;
    }
    ~any()
    {
        reset();
    }
};



int main()
{
    any a = 123;
    any b = (string)"123";
    int ai = a.as<int>();
    string bs = b.as<string>();

    cout << ai << " " << bs;



    return 0;
}





