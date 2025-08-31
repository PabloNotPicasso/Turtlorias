#pragma once

#include <stddef.h>

#include <array>
#include <cstdint>
#include <initializer_list>
#include <sstream>

template<int N, int M>
class Matrix {
public:
    using ElementType = long long;

    Matrix(ElementType el)
    {
        for (unsigned i = 0; i < N; ++i) {
            for (unsigned j = 0; j < M; ++j) {
                data[i][j] = el;
            }
        }
    }

    Matrix(std::initializer_list<std::initializer_list<ElementType>> il)
    {
        // static_assert( il.size() == N );
        // static_assert( il.begin()->size() == M );
        unsigned i = 0;
        for (auto listOfLists : il) {
            unsigned j = 0;
            for (auto element : listOfLists) {
                data[i][j] = element;
                ++j;
            }
            ++i;
        }
    }

    const std::array<ElementType, M>& operator[](size_t rowIdx) const
    {
        return data[rowIdx];
    }

    std::array<ElementType, M>& operator[](size_t rowIdx)
    {
        return data[rowIdx];
    }

    std::string toString() const
    {
        std::stringstream ss;
        for (auto row : data) {
            ss << "|";
            for (auto el : row) {
                ss << el << " ";
            }
            ss << "|\n";
        }
        return ss.str();
    }

private:
    using row = std::array<ElementType, M>;
    std::array<row, N> data;
};

template<int N, int K, int M>
Matrix<N, M> operator*(const Matrix<N, K> lhs, const Matrix<K, M> rhs)
{
    Matrix<N, M> res(0);

    for (unsigned i = 0; i < N; ++i) {
        for (unsigned j = 0; j < M; ++j) {
            for (unsigned k = 0; k < K; ++k) {
                res[i][j] += lhs[i][k] * rhs[k][j];
            }
        }
    }

    return res;
}
