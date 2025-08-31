#include "BigInteger.h"

#include "Frame.h"
#include "Logger/LoggerApi.h"

#include <cassert>
#include <iomanip>

namespace Structures {

BigInteger::BigInteger()
    : BigInteger(0)
{
}

BigInteger::BigInteger(const BigInteger& toCopy)
    : m_frames(toCopy.m_frames)
{
}
BigInteger::BigInteger(BigInteger&& toMove)
    : m_frames(std::move(toMove.m_frames))
{
}
BigInteger& BigInteger::operator=(const BigInteger& toCopy)
{
    m_frames = toCopy.m_frames;
    return *this;
}
BigInteger& BigInteger::operator=(BigInteger&& toMove)
{
    m_frames = std::move(toMove.m_frames);
    return *this;
}

BigInteger::BigInteger(value_type value)
{
    bool isNegative = value < 0;
    value = llabs(value);

    do {
        Frame::value_t toAdd = value % Frame::Mod;
        toAdd = isNegative ? (-toAdd) : (toAdd);
        addNewFrame(toAdd);
        value /= Frame::Mod;
    } while (value);
}

void BigInteger::addNewFrame(value_type value)
{
    m_frames.emplace_back(value);
}

int8_t BigInteger::sign() const
{
    return m_frames.back() > 0 ? 1 : (m_frames.back() == 0 ? 0 : -1);
}

std::string BigInteger::toString() const
{
    std::stringstream ss;

    auto revIt = m_frames.rbegin();
    ss << *(revIt++);
    for (; revIt != m_frames.rend(); ++revIt) {
        ss << std::right << std::setw(Frame::MaxFrameLenght) << std::setfill('0') << llabs(*revIt);
    }
    return ss.str();
}

BigInteger BigInteger::operator-() const
{
    BigInteger copy = *this;
    for (auto& i : copy.m_frames) {
        i = -i;
    }
    return copy;
}

bool operator==(const BigInteger& lhs, const BigInteger& rhs)
{
    return std::equal(begin(lhs.m_frames), end(lhs.m_frames), begin(rhs.m_frames));
}
bool operator<(const BigInteger& lhs, const BigInteger& rhs)
{
    if (lhs == rhs) {
        return false;
    }
    if (lhs.sign() != rhs.sign()) {
        return lhs.sign() < rhs.sign();
    }
    if (lhs.m_frames.size() != rhs.m_frames.size()) {
        return (lhs.sign() < 0) ^ (lhs.m_frames.size() < rhs.m_frames.size());
    }

    bool isLess = false;
    int32_t differentIdx = lhs.m_frames.size() - 1;
    while (differentIdx >= 0 && lhs.m_frames[differentIdx] == rhs.m_frames[differentIdx]) {
        --differentIdx;
    }

    return lhs.m_frames[differentIdx] < rhs.m_frames[differentIdx];
}

bool operator>(const BigInteger& lhs, const BigInteger& rhs)
{
    return rhs < lhs;
}
bool operator<=(const BigInteger& lhs, const BigInteger& rhs)
{
    return !(lhs > rhs);
}
bool operator>=(const BigInteger& lhs, const BigInteger& rhs)
{
    return rhs <= lhs;
}
bool operator!=(const BigInteger& lhs, const BigInteger& rhs)
{
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const BigInteger& bi)
{
    return os << bi.toString();
}

std::istream& operator>>(std::istream& is, BigInteger& bi)
{
    std::string str;
    is >> str;
    bi.m_frames.clear();

    bool isNegative = str[0] == '-';
    if (isNegative) {
        str.erase(str.begin());
    }

    int64_t lPointer = std::max<int>(0, str.size() - Frame::MaxFrameLenght);
    int64_t rPointer = str.size() - 1;

    for (; rPointer >= 0;) {
        auto value = stoi(str.substr(lPointer, rPointer - lPointer + 1));
        value = isNegative ? -value : value;

        bi.addNewFrame(value);
        rPointer = lPointer - 1;
        lPointer = std::max<int>(0, lPointer - Frame::MaxFrameLenght);
    }
    return is;
}

BigInteger operator+(const BigInteger& biLhs, const BigInteger& biRhs)
{
    auto& lhs = biLhs.m_frames;
    auto& rhs = biRhs.m_frames;

    BigInteger biSum = biLhs;
    auto& sum = biSum.m_frames;

    int64_t buffer = 0;
    size_t idx = 0;
    for (; idx < sum.size() && idx < rhs.size(); ++idx) {
        int64_t frameSum = buffer + sum[idx].value() + rhs[idx].value();
        sum[idx] = frameSum % Frame::Mod;
        buffer = frameSum / Frame::Mod;
    }

    for (; idx < rhs.size(); ++idx) {
        int64_t frameSum = buffer + rhs[idx].value();
        biSum.addNewFrame(frameSum % Frame::Mod);
        buffer = frameSum / Frame::Mod;
    }
    return biSum;
}

} // namespace Structures
