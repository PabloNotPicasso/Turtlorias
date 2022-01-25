#pragma once
#include "Structures/SegmentAccumulator/ISegmentAccumulator.h"

namespace Structures {

template<typename ValueType>
class SegmentTree : public ISegmentAccumulator<ValueType> {
public:
    using AccumulateFunction = typename ISegmentAccumulator<ValueType>::AccumulateFunction;
    SegmentTree();
    virtual ~SegmentTree() = default;

    void init(
        const std::vector<ValueType>& array,
        const AccumulateFunction& accumulateFunction,
        const ValueType& zerro) override;

    ValueType get(const int& l, const int& r) const override;

    void update(const int& index, const ValueType& newValue) override;

    bool isBuilt() const override;

private:
    void buildTree(const std::vector<ValueType>& array);

    void buildTreeRecurse(const std::vector<ValueType>& array, int lPoint, int rPoint, int v);
    ValueType getRecurse(const int lSegment, const int rSegment, int lTree, int rTree, int v) const;
    void updateRecurse(const int& index, const ValueType& newValue, int lTree, int rTree, int v);

private:
    bool m_isBuilt;
    AccumulateFunction m_accumulate;
    ValueType m_zerro;
    int m_elementCnt;
    std::vector<ValueType> m_tree;
};

// Implementation
template<typename ValueType>
SegmentTree<ValueType>::SegmentTree()
    : m_isBuilt(false)
{
}

template<typename ValueType>
void SegmentTree<ValueType>::init(
    const std::vector<ValueType>& array,
    const AccumulateFunction& accumulateFunction,
    const ValueType& zerro)
{
    m_accumulate = accumulateFunction;
    m_zerro = zerro;
    buildTree(array);
}

template<typename ValueType>
bool SegmentTree<ValueType>::isBuilt() const
{
    return m_isBuilt;
}

template<typename ValueType>
ValueType SegmentTree<ValueType>::get(const int& l, const int& r) const
{
    return getRecurse(l, r, 0, m_elementCnt - 1, 1);
}

template<typename ValueType>
void SegmentTree<ValueType>::update(const int& index, const ValueType& newValue)
{
    updateRecurse(index, newValue, 0, m_elementCnt - 1, 1);
}

template<typename ValueType>
void SegmentTree<ValueType>::buildTree(const std::vector<ValueType>& array)
{
    m_elementCnt = array.size();
    m_tree.resize(m_elementCnt * 3);
    buildTreeRecurse(array, 0, m_elementCnt - 1, 1);
    m_isBuilt = true;
}

template<typename ValueType>
void SegmentTree<ValueType>::buildTreeRecurse(
    const std::vector<ValueType>& array, int lPoint, int rPoint, int v)
{
    if (lPoint == rPoint) {
        m_tree[v] = array[lPoint];
        return;
    }
    int mid = (rPoint + lPoint) / 2;
    int leftTreeVertex = v * 2;
    int rightTreeVertex = v * 2 + 1;
    // build left tree
    buildTreeRecurse(array, lPoint, mid, leftTreeVertex);
    // build right tree
    buildTreeRecurse(array, mid + 1, rPoint, rightTreeVertex);
    m_tree[v] = m_accumulate(m_tree[leftTreeVertex], m_tree[rightTreeVertex]);
}

template<typename ValueType>
ValueType SegmentTree<ValueType>::getRecurse(
    const int lSegment, const int rSegment, int lTree, int rTree, int v) const
{
    if (lSegment > rSegment)
        return m_zerro;
    if (lTree == lSegment && rTree == rSegment)
        return m_tree[v];
    int mid = (lTree + rTree) / 2;
    int leftTreeVertex = v * 2;
    int rightTreeVertex = v * 2 + 1;

    ValueType leftTreeSum
        = getRecurse(lSegment, std::min(rSegment, mid), lTree, mid, leftTreeVertex);
    ValueType rightTreeSum
        = getRecurse(std::max(lSegment, mid + 1), rSegment, mid + 1, rTree, rightTreeVertex);
    return m_accumulate(leftTreeSum, rightTreeSum);
}

template<typename ValueType>
void SegmentTree<ValueType>::updateRecurse(
    const int& index, const ValueType& newValue, int lTree, int rTree, int v)
{
    if (lTree == rTree) {
        m_tree[v] = newValue;
        return;
    }
    int mid = (lTree + rTree) / 2;
    int leftTreeVertex = v * 2;
    int rightTreeVertex = v * 2 + 1;
    if (index <= mid) {
        updateRecurse(index, newValue, lTree, mid, leftTreeVertex);
    } else {
        updateRecurse(index, newValue, mid + 1, rTree, rightTreeVertex);
    }
    m_tree[v] = m_accumulate(m_tree[leftTreeVertex], m_tree[rightTreeVertex]);
}

} // namespace Structures
