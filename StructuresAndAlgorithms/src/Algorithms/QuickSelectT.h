#pragma once

#include <stddef.h>

#include <cstdint>
#include <functional>
#include <iostream>
#include <iterator>
#include <type_traits>

namespace Algorithm {

template<typename RandomIt, typename BinaryPred>
RandomIt __pivot(RandomIt begin, RandomIt end, BinaryPred pred)
{
    if (begin == end) {
        return begin;
    }
    RandomIt pivotElement = std::prev(end);
    RandomIt newPivotPosition = begin;
    for (auto it = begin; it != pivotElement; ++it) {
        if (pred(*it, *pivotElement)) {
            std::iter_swap(it, newPivotPosition);
            ++newPivotPosition;
        }
    }
    std::iter_swap(pivotElement, newPivotPosition);
    return newPivotPosition;
}

template<typename RandomIt, typename BinaryPred = std::less<>>
RandomIt quick_select(RandomIt begin, RandomIt end, size_t k, BinaryPred pred = {})
{
    static_assert(
        std::is_base_of_v<
            std::random_access_iterator_tag,
            typename std::iterator_traits<RandomIt>::iterator_category>,
        "quick_select requires random access iterator");

    const auto elementCnt = std::distance(begin, end);
    if (elementCnt <= 0) {
        return end;
    }
    if (k >= static_cast<size_t>(elementCnt)) {
        return end;
    }

    RandomIt pivotIt = __pivot(begin, end, pred);
    const auto pivotsStatisticK = static_cast<size_t>(std::distance(begin, pivotIt));
    if (pivotsStatisticK == k) {
        return pivotIt;
    }
    if (pivotsStatisticK < k) {
        return quick_select(std::next(pivotIt), end, k - (pivotsStatisticK + 1), pred);
    } else {
        return quick_select(begin, pivotIt, k, pred);
    }
}

} // namespace Algorithm
