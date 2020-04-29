#include <bits/stdc++.h>

using namespace std;

class A
{
public:
    A(){}
    ~A(){
        cout << "~A()\n";
    }
};

template < typename T >
class SharedPtr
{
private:
    T* m_ptr;
    size_t* m_cnt;
    function<void(T*)> m_deleter;
    void try_to_delete()
    {
        (*m_cnt)--;
        if( *m_cnt == 0 )
        {
            if( nullptr == m_deleter )
            {
                delete m_ptr;
            }
            else
            {
                m_deleter(m_ptr);
            }
        }
        else
        {
            m_cnt = new size_t(0);
        }
        m_ptr = nullptr;
    }
public:
    SharedPtr( ):
        m_ptr(nullptr),
        m_cnt( new size_t(0) ),
        m_deleter(nullptr)
    {}
    SharedPtr( T* ptr, function<void(T*)> deleter = nullptr ) :
        m_ptr(ptr),
        m_cnt( new size_t(1) ),
        m_deleter(deleter)
    {}
    SharedPtr( SharedPtr& to_copy )
    {
        m_ptr = to_copy.get();
        m_cnt = to_copy.m_cnt;
        (*m_cnt)++;
    }
    SharedPtr operator=( SharedPtr& to_copy )
    {
        m_ptr = to_copy.get();
        m_cnt = to_copy.m_cnt;
        (*m_cnt)++;
    }
    T* get()
    {
        return m_ptr;
    }
    void reset()
    {
        try_to_delete();
    }
    ~SharedPtr()
    {
        try_to_delete();
    }
};

int main()
{
    SharedPtr<A> ptr(new A, [](A* obj){
                                cout << "delete A";
                                delete obj;
                            }
    );
    SharedPtr<A> ptr1(ptr);
    SharedPtr<A> ptr2 = ptr1;
    cout << " END \n";
    return 0;
}
