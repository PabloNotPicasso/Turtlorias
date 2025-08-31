#pragma once

#include <string>

template<typename Char>
class lowCharTraits : public std::char_traits<Char> {
public:
    static void assign(Char& lhs, const Char& rhs)
    {
        lhs = std::tolower(rhs);
    }

    static Char* move(Char* larr, const Char* rarr, size_t n)
    {
        for (size_t i = 0; i < n; ++i) {
            assign(larr[i], rarr[i]);
        }
        return larr;
    }

    static Char* copy(Char* lhs, const Char* rhs, size_t n)
    {
        return move(lhs, rhs, n);
    }
};

template<typename Char>
using basic_low_string = std::basic_string<Char, lowCharTraits<Char>>;

using low_string = basic_low_string<char>;
using low_wstring = basic_low_string<wchar_t>;

template<typename Char, typename Traits, typename Char2>
std::basic_ostream<Char, Traits>& operator<<(
    std::basic_ostream<Char, Traits>& os, const basic_low_string<Char2>& lowStr)
{
    return os.write(lowStr.data(), lowStr.size());
}

template<typename Char>
class equal_traits : public std::char_traits<Char> {
public:
    static bool eq(Char c1, Char c2)
    {
        return std::tolower(c1) == std::tolower(c2);
    }

    static bool lt(Char c1, Char c2)
    {
        return std::tolower(c1) < std::tolower(c2);
    }

    static int compare(const Char* s1, const Char* s2, size_t n)
    {
        for (; n--; ++s1, ++s2) {
            if (lt(*s1, *s2)) {
                return -1;
            } else if (lt(*s2, *s1)) {
                return 1;
            }
        }
        return 0;
    }

    static const char* find(const Char* s, int n, Char a)
    {
        for (; n--; ++s) {
            if (eq(*s, a)) {
                return s;
            }
        }
        return nullptr;
    }
};

template<typename Char>
using basic_eqlow_string = std::basic_string<Char, equal_traits<Char>>;

using eqlow_string = basic_eqlow_string<char>;
using eqlow_wstring = basic_eqlow_string<wchar_t>;

template<typename Char, typename Traits, typename Char2>
std::basic_ostream<Char, Traits>& operator<<(
    std::basic_ostream<Char, Traits>& os, const basic_eqlow_string<Char2>& lowStr)
{
    return os.write(lowStr.data(), lowStr.size());
}
