#pragma once
#include "Structures/Effective/SegmentAccumulator/ISegmentAccumulator.h"

#include <cmath>

namespace Structures {

template<typename ValueType>
class SegmentSqrt : public ISegmentAccumulator<ValueType> {
public:
    using AccumulateFunction = typename ISegmentAccumulator<ValueType>::AccumulateFunction;
    SegmentSqrt() = default;
    virtual ~SegmentSqrt() = default;

    void init(
        const std::vector<ValueType>& array,
        const AccumulateFunction& accumulateFunction,
        const ValueType& zerro) override;

    ValueType get(size_t l, size_t r) const override;

    void update(size_t index, const ValueType& newValue) override;

    bool isBuilt() const override;

private:
    void buildBlocks();

private:
    bool m_isBuilt = false;
    size_t m_blockLen = 0;
    ValueType m_zerro = 0;
    AccumulateFunction m_accumulate;
    std::vector<ValueType> m_array;
    std::vector<ValueType> m_blocks;
};

// Implementation
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
ValueType SegmentSqrt<ValueType>::get(size_t l, size_t r) const
{
    ValueType accumulation = m_zerro;
    for (size_t i = l; i <= r;) {
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
void SegmentSqrt<ValueType>::update(size_t index, const ValueType& newValue)
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
