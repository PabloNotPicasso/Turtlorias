#pragma once

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
// Vector class
struct Vector {
    using ValueType = int;
    Vector() = default;
    Vector(ValueType x)
        : x(x)
        , y(x){};
    Vector(ValueType x, ValueType y)
        : x(x)
        , y(y)
    {
    }
    Vector operator+(Vector toAdd) const
    {
        return Vector(x + toAdd.x, y + toAdd.y);
    }
    Vector operator*(Vector toMul) const
    {
        return Vector(x * toMul.x, y * toMul.y);
    }
    bool operator==(const Vector r) const
    {
        return x == r.x && y == r.y;
    }

protected:
    ValueType x, y;
};

template<typename T>
T getRandom(int l, int r)
{
    return rand() % (r - l + 1) + l;
}

template<>
Vector getRandom(int l, int r)
{
    return Vector(getRandom<Vector::ValueType>(l, r), getRandom<Vector::ValueType>(l, r));
}

template<typename T>
std::vector<T> getRandomArray(int size)
{
    std::vector<T> v(size);
    for (int i = 0; i < size; ++i) {
        v[i] = getRandom<T>(-1e9, 1e9);
    }
    return v;
}

} // namespace Helpers
