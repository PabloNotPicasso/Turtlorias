#pragma once
#include "Structures/SegmentAccumulator/ISegmentAccumulator.h"

#include <cmath>
#include <numeric>

namespace Structures {

template<typename ValueType>
class SegmentBrute : public ISegmentAccumulator<ValueType> {
public:
    using AccumulateFunction = typename ISegmentAccumulator<ValueType>::AccumulateFunction;
    SegmentBrute();
    virtual ~SegmentBrute() = default;

    void init(
        const std::vector<ValueType>& array,
        const AccumulateFunction& accumulateFunction,
        const ValueType& zerro) override;

    ValueType get(const int& l, const int& r) const override;

    void update(const int& index, const ValueType& newValue) override;

    bool isBuilt() const override;

private:
    bool m_isBuilt;
    AccumulateFunction m_accumulate;
    ValueType m_zerro;
    std::vector<ValueType> m_array;
};

// Implementation
template<typename ValueType>
SegmentBrute<ValueType>::SegmentBrute()
    : m_isBuilt(false)
{
}

template<typename ValueType>
void SegmentBrute<ValueType>::init(
    const std::vector<ValueType>& array,
    const AccumulateFunction& accumulateFunction,
    const ValueType& zerro)
{
    m_array = array;
    m_accumulate = accumulateFunction;
    m_zerro = zerro;
    m_isBuilt = true;
}

template<typename ValueType>
bool SegmentBrute<ValueType>::isBuilt() const
{
    return m_isBuilt;
}

template<typename ValueType>
ValueType SegmentBrute<ValueType>::get(const int& l, const int& r) const
{
    ValueType accumulation
        = std::accumulate(m_array.begin() + l, m_array.begin() + r + 1, m_zerro, m_accumulate);
    return accumulation;
}

template<typename ValueType>
void SegmentBrute<ValueType>::update(const int& index, const ValueType& newValue)
{
    m_array[index] = newValue;
}

} // namespace Structures
