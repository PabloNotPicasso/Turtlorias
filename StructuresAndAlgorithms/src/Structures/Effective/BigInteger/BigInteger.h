#pragma once

#include <cstddef>
#include <cstdint>
#include <deque>
#include <iostream>

namespace Structures {

class Frame;

class BigInteger {
public:
    using value_type = int64_t;

    BigInteger();
    BigInteger(const BigInteger&);
    BigInteger(BigInteger&&);
    BigInteger& operator=(const BigInteger&);
    BigInteger& operator=(BigInteger&&);

    BigInteger(value_type);
    std::string toString() const;

    BigInteger operator-() const;

    friend BigInteger operator+(const BigInteger& lhs, const BigInteger& rhs);

    friend bool operator<(const BigInteger& lhs, const BigInteger& rhs);
    friend bool operator==(const BigInteger& lhs, const BigInteger& rhs);
    friend std::istream& operator>>(std::istream& is, BigInteger& bi);

private:
    int8_t sign() const;
    void addNewFrame(value_type);

    // Invariant:
    // m_frames is never empty!
    std::deque<Frame> m_frames;
};

bool operator<(const BigInteger& lhs, const BigInteger& rhs);
bool operator==(const BigInteger& lhs, const BigInteger& rhs);

bool operator>(const BigInteger& lhs, const BigInteger& rhs);
bool operator<=(const BigInteger& lhs, const BigInteger& rhs);
bool operator>=(const BigInteger& lhs, const BigInteger& rhs);
bool operator!=(const BigInteger& lhs, const BigInteger& rhs);

std::ostream& operator<<(std::ostream& os, const BigInteger& bi);
std::istream& operator>>(std::istream& is, BigInteger& bi);

BigInteger operator+(const BigInteger& lhs, const BigInteger& rhs);

} // namespace Structures
