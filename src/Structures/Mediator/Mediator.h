#pragma once
#include <set>

namespace Structures {

class EmptyMediatorException : public std::exception {
public:
    const char* what() const noexcept override
    {
        return "Mediator is empty";
    }
};

template<typename ValueType>
class Mediator {
public:
    void add(const ValueType& value);

    void erase(const ValueType& value);

    const ValueType& getMedian() const;

    bool empty() const;

    void clear();

protected:
    void recombine();

private:
    std::multiset<ValueType> m_left;
    std::multiset<ValueType> m_right;
};

// Implementation
template<typename ValueType>
void Mediator<ValueType>::add(const ValueType& value)
{
    if (empty() || value < getMedian()) {
        m_left.insert(value);
    } else {
        m_right.insert(value);
    }
    recombine();
}

template<typename ValueType>
void Mediator<ValueType>::erase(const ValueType& value)
{
    if (auto itToErase = m_left.find(value); itToErase != m_left.end()) {
        m_left.erase(itToErase);
    } else if (auto itToErase = m_right.find(value); itToErase != m_right.end()) {
        m_right.erase(itToErase);
    }
    recombine();
}

template<typename ValueType>
const ValueType& Mediator<ValueType>::getMedian() const
{
    if (empty()) {
        throw EmptyMediatorException();
    }
    return *m_left.rbegin();
}

template<typename ValueType>
bool Mediator<ValueType>::empty() const
{
    return m_left.empty();
}

template<typename ValueType>
void Mediator<ValueType>::clear()
{
    m_left.clear();
    m_right.clear();
}

template<typename ValueType>
void Mediator<ValueType>::recombine()
{
    // from left to right
    if (1. * m_left.size() - 1. * m_right.size() > 1) {
        auto toMove = prev(m_left.end());
        m_right.insert(*toMove);
        m_left.erase(toMove);
    } else if (m_right.size() > m_left.size()) {
        auto toMove = m_right.begin();
        m_left.insert(*toMove);
        m_right.erase(toMove);
    }
}

} // namespace Structures
