#include "String.h"

namespace Structures {

using size_type = String::size_type;
using value_type = String::value_type;
using pointer = String::pointer;
using reference = String::reference;
using const_reference = String::const_reference;

std::ostream& operator<<(std::ostream& os, const String& toPrint)
{
    os << toPrint.c_str();
    return os;
}

std::istream& operator>>(std::istream& is, String& toScan)
{
    toScan.clear();

    char symbol = String::nullTerminate;
    // Skip leading whitespaces
    do {
        symbol = is.get();
    } while (isspace(symbol) && !is.eof());

    while (!isspace(symbol) && !is.eof()) {
        toScan.push_back(symbol);
        symbol = is.get();
    }

    if (!isspace(symbol)) {
        toScan.push_back(symbol);
    }
    return is;
}

String& String::operator+=(const String& rhs)
{
    for (size_t i = 0; i < rhs.size(); ++i) {
        push_back(rhs[i]);
    }
    return *this;
}

String& String::operator+=(value_type symbol)
{
    push_back(symbol);
    return *this;
}

String& String::operator+=(const value_type* array)
{
    for (size_t i = 0; array[i] != String::nullTerminate; ++i) {
        push_back(array[i]);
    }
    return *this;
}

String operator+(const String& lhs, const String& rhs)
{
    String result = lhs;
    return result += rhs;
}

String operator+(const String& lhs, value_type symbol)
{
    String result = lhs;
    return result += symbol;
}

String operator+(const String& lhs, const value_type* array)
{
    String result = lhs;
    return result += array;
}

bool operator==(const String& lhs, const String& rhs)
{
    bool areEqual = lhs.size() == rhs.size();
    for (size_t i = 0; areEqual && i < lhs.size(); ++i) {
        areEqual &= lhs[i] == rhs[i];
    }
    return areEqual;
}

bool operator!=(const String& lhs, const String& rhs)
{
    return !(lhs == rhs);
}

bool operator>(const String& lhs, const String& rhs)
{
    auto cmp = strcmp(lhs._begin, rhs._begin);
    return cmp > 0;
}

bool operator>=(const String& lhs, const String& rhs)
{
    auto cmp = strcmp(lhs._begin, rhs._begin);
    return cmp >= 0;
}

bool operator<(const String& lhs, const String& rhs)
{
    return rhs > lhs;
}
bool operator<=(const String& lhs, const String& rhs)
{
    return rhs >= lhs;
}

} // namespace Structures