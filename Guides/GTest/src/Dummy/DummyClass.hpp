#pragma once

class DummyClass {
public:
    virtual ~DummyClass() = default;

    virtual bool getTrue();

    virtual bool getFalse();

    virtual void throwInt();

    virtual void toAssert();

    // Returns value which is incremented after every call
    virtual int getIncreasingCounter();

    // Returns numberToReturn
    virtual int getInt(int numberToReturn);

    void notMocked();
private:
    int m_increasingCounter = 0;
};


class DummyWrapper
{
public:
    DummyWrapper(DummyClass* dummy):m_dummy(dummy){}

    void callGetTrue(){
        m_dummy->getTrue();
    }

    void callGetFalse(){
        m_dummy->getFalse();
    }

    void callNotMocked(){
        m_dummy->notMocked();
    }

    void callGetTrueNTimes(int n){
        for( int i = 0; i < n; ++i)
            m_dummy->getTrue();
    }

    void callGetInt(int numToGet){
        m_dummy->getInt(numToGet);
    }
private:
    DummyClass* m_dummy;
};
