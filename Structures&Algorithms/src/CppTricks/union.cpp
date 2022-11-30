#include <bits/stdc++.h>

/**
 * @brief Example of using unions and twin-hack
 * 
 */
class PrivateTwin
{
public:
    PrivateTwin()
    {
        srand(time(nullptr));
        m_privateNumber = rand();
    }
    int number() const {
        return m_privateNumber;
    }
private:
    // private member with no setters
    int m_privateNumber;
};

// Full copy of PrivateTwin with public modifier
class BadTwin
{
public:
    BadTwin()
    {
    }
    // public member
    int m_privateNumber;
};

union Twins
{
    Twins(){}
    PrivateTwin priv;
    BadTwin bad;
};

int main()
{
    // Example with union
    {
        std::cout << "Example with union"<< std::endl;

        Twins twins;
        twins.priv = PrivateTwin();

        // Access to private member
        assert( twins.priv.number() == twins.bad.m_privateNumber );
        std::cout << "Private number: " << twins.priv.number() << std::endl;
        std::cout << "Change through bad twin to 10" << std::endl;
        twins.bad.m_privateNumber = 10;
        assert( twins.priv.number() == twins.bad.m_privateNumber );
        std::cout << "Private number: " << twins.priv.number() << std::endl;
    }
    // Example with reinterpret cast
    {
        std::cout << std::endl << "Example with reinterpret cast"<< std::endl;

        PrivateTwin privateTwin;

        BadTwin* badTwin = reinterpret_cast<BadTwin*>(&privateTwin);

        // Access to private member
        assert( privateTwin.number() == badTwin->m_privateNumber );
        std::cout << "Private number: " << privateTwin.number() << std::endl;
        std::cout << "Change through bad twin to 10" << std::endl;
        badTwin->m_privateNumber = 10;
        assert( privateTwin.number() == badTwin->m_privateNumber );
        std::cout << "Private number: " << privateTwin.number() << std::endl;
    }
    // Example with raw pointers
    {
        std::cout << std::endl << "Example with raw pointers"<< std::endl;

        PrivateTwin privateTwin;
        BadTwin* badTwin = static_cast<BadTwin*>(static_cast<void*>(&privateTwin));

        // Access to private member
        assert( privateTwin.number() == badTwin->m_privateNumber );
        std::cout << "Private number: " << privateTwin.number() << std::endl;
        std::cout << "Change through bad twin to 10" << std::endl;
        badTwin->m_privateNumber = 10;
        assert( privateTwin.number() == badTwin->m_privateNumber );
        std::cout << "Private number: " << privateTwin.number() << std::endl;
    }
    return 0;
}
