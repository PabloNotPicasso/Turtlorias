#include "DummyClass.hpp"

#include "DummyFunctions.hpp"

bool DummyClass::getTrue()
{
    return Dummy::getTrue();
}

bool DummyClass::getFalse()
{
    return Dummy::getFalse();
}

void DummyClass::throwInt()
{
    Dummy::throwInt();
}

void DummyClass::toAssert()
{
    Dummy::toAssert();
}

int DummyClass::getIncreasingCounter()
{
    return m_increasingCounter++;
}

int DummyClass::getInt(int a)
{
    return a;
}

void DummyClass::notMocked(){}