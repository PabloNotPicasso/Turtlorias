#pragma once

#include <cmath>
#include <functional>

namespace Helpers {

template<
    typename ValueType,
    typename AccumulateFunction = std::function<ValueType(const ValueType&, const ValueType&)>>
ValueType linearAccumulation(
    std::vector<ValueType> array, int l, int r, AccumulateFunction accum, ValueType zerro)
{
    ValueType accumulation = zerro;
    for (int i = l; i <= r; ++i)
        accumulation = accum(accumulation, array[i]);
    return accumulation;
}

template<typename Numeric>
Numeric getRandom(int l, int r)
{
    return rand() % (r - l + 1) + l;
}

template<typename Numeric>
std::vector<Numeric> getRandomArray(int size)
{
    std::vector<Numeric> v(size);
    for (int i = 0; i < size; ++i) {
        v[i] = getRandom<Numeric>(-1e9, 1e9);
    }
    return v;
}

constexpr double EPS = 1e-6;

template<typename Numeric>
bool areEqual(Numeric lhs, Numeric rhs)
{
    return lhs == rhs;
}

template<>
bool areEqual(double lhs, double rhs)
{
    return fabs(lhs - rhs) < EPS;
}

} // namespace Helpers
