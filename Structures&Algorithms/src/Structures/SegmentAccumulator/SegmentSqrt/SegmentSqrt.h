#pragma once
#include "Structures/SegmentAccumulator/ISegmentAccumulator.h"

#include <cmath>

namespace Structures {

template<
    typename ValueType>
class SegmentSqrt : public ISegmentAccumulator<ValueType> {
public:
    using AccumulateFunction = typename ISegmentAccumulator<ValueType>::AccumulateFunction;
    SegmentSqrt();
    virtual ~SegmentSqrt() = default;

    void init(
        const std::vector<ValueType>& array,
        const AccumulateFunction& accumulateFunction,
        const ValueType& zerro) override;

    ValueType get(const int& l, const int& r) const override;

    void update(const int& index, const ValueType& newValue) override;

    bool isBuilt() const override;

private:
    void buildBlocks();

private:
    bool m_isBuilt;
    AccumulateFunction m_accumulate;
    ValueType m_zerro;
    std::vector<ValueType> m_array;
    std::vector<ValueType> m_blocks;
    int m_blockLen;
};

// Implementation
template<typename ValueType>
SegmentSqrt<ValueType>::SegmentSqrt()
    : m_isBuilt(false)
{
}

template<typename ValueType>
void SegmentSqrt<ValueType>::init(
    const std::vector<ValueType>& array,
    const AccumulateFunction& accumulateFunction,
    const ValueType& zerro)
{
    m_array = array;
    m_accumulate = accumulateFunction;
    m_zerro = zerro;
    buildBlocks();
    m_isBuilt = true;
}

template<typename ValueType>
bool SegmentSqrt<ValueType>::isBuilt() const
{
    return m_isBuilt;
}

template<typename ValueType>
ValueType SegmentSqrt<ValueType>::get(const int& l, const int& r) const
{
    ValueType accumulation = m_zerro;
    for (int i = l; i <= r;) {
        // If current element is start of a block and full block is in range
        if (i % m_blockLen == 0 && i + m_blockLen - 1 <= r) {
            // Adding block
            accumulation = m_accumulate(accumulation, m_blocks[i / m_blockLen]);
            i += m_blockLen;
        } else {
            // Adding element
            accumulation = m_accumulate(accumulation, m_array[i]);
            ++i;
        }
    }
    return accumulation;
}

template<typename ValueType>
void SegmentSqrt<ValueType>::update(const int& index, const ValueType& newValue)
{
    auto& blockToChange = m_blocks[index / m_blockLen];
    m_array[index] = newValue;
    blockToChange = m_zerro;
    int blockStart = index - index % m_blockLen;
    int blockEnd = blockStart + m_blockLen;
    for (int i = blockStart; i < blockEnd; ++i) {
        blockToChange = m_accumulate(blockToChange, m_array[i]);
    }
}

template<typename ValueType>
void SegmentSqrt<ValueType>::buildBlocks()
{
    m_blockLen = std::sqrt(m_array.size()) + 1;
    m_blocks.resize(m_blockLen, m_zerro);
    for (size_t i = 0; i < m_array.size(); ++i) {
        m_blocks[i / m_blockLen] = m_accumulate(m_blocks[i / m_blockLen], m_array[i]);
    }
}

} // namespace Structures
