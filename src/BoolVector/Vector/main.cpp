#include <bits/stdc++.h>

class VectorBoolAPI
{
private:
    size_t  m_size;
    char*   m_array;
public:
    VectorBoolAPI( size_t size ) : m_size( size )
    {
        m_array = new char[m_size];
    }
    ~VectorBoolAPI(){
        delete[] m_array;
    }
    size_t size() const
    {
        return m_size;
    }
protected:
    void set_bit(size_t index, bool value);
    bool get_bit(size_t index) const;
};


class VectorBool : public VectorBoolAPI
{
private:
    class BitController
    {
        size_t      m_index;
        VectorBool* m_parent;
    public:
        BitController( size_t index, VectorBool* parent ) : m_index(index), m_parent( parent )
            {}
        BitController( const BitController& bc ) = default;
        BitController& operator=( const BitController& bc)
        {
            m_parent->set_bit(m_index, static_cast<bool>(bc) );
            return  *this;
        }
        BitController& operator=( bool value )
        {
            m_parent->set_bit( m_index, value );
            return *this;
        }
        operator bool() const
        {
            return m_parent->get_bit( m_index );
        }
    };
public:
    VectorBool( size_t p_size = 1000 ):VectorBoolAPI(p_size/8+1)
    {}
    BitController operator[]( size_t index )
    {
        return BitController(index, this);
    }
    VectorBool( std::initializer_list<bool> list ): VectorBoolAPI(list.size()/8+1)
    {
        auto iterator = list.begin();
        for( size_t index = 0; iterator != list.end(); index++, iterator++ )
        {
            set_bit(index, *iterator);
        }
    }
};

void print( VectorBool& v, size_t n)
{
    for( size_t i = 0; i < n; i++ )
    {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}

int main()
{
    VectorBool v = { 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0};

    print( v, 10);
    if( v[0] )
    {
        v[1] = v[2] = v[3] = 1;
    }
    print( v, 10);

    return 0;
}

void VectorBoolAPI::set_bit(size_t index, bool value)
{
    if( get_bit(index) != value  )
    {
        m_array[index/8] ^= (1 << (index%8) );
    }
}

bool VectorBoolAPI::get_bit(size_t index) const
{
    return m_array[index/8] & (1 << (index%8) );
}
