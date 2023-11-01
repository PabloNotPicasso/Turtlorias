#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <initializer_list>
#include <iostream>
#include <utility>

namespace Structures::STL {

class String {
public:
    using size_type = size_t;
    using value_type = char;
    using pointer = char*;
    using reference = char&;
    using const_reference = const char&;

    constexpr static value_type nullTerminate = '\0';
    // Is it integrated?
    constexpr static size_type maxSize = 1000;

public:
    ~String();
    String();
    explicit String(size_type count, value_type value = nullTerminate);

    String(const String&);
    String(String&&);
    String(const value_type*);
    String(std::initializer_list<value_type>);

    String& operator=(const String&);
    String& operator=(String&&);
    String& operator=(const value_type*);
    String& operator=(std::initializer_list<value_type>);

    void reserve(size_type newCapacity);
    void resize(size_type newSize, value_type symbol = nullTerminate);

    void push_back(value_type value);
    void pop_back();
    void insert(size_type idx, const value_type& value);
    void clear();

    pointer begin() const;
    pointer end() const;

    reference operator[](size_type idx);
    const_reference operator[](size_type idx) const;

    reference at(size_type idx);
    const_reference at(size_type idx) const;

    reference back();
    const_reference back() const;

    bool empty() const noexcept;
    size_type size() const noexcept;
    size_type capacity() const noexcept;

    const value_type* c_str() const noexcept;
    value_type* c_str() noexcept;

    void swap(String&) noexcept;

    String& operator+=(const String&);
    String& operator+=(value_type);
    String& operator+=(const value_type*);

protected:
    value_type* makeExtendedCopy(
        value_type* array, size_type currentSize, size_type extendedCapacity);
    void freeArray(value_type* array);

    friend std::ostream& operator<<(std::ostream&, const String&);
    friend std::istream& operator>>(std::istream&, String&);

    friend String operator+(const String&, const String&);
    friend String operator+(const String&, value_type);
    friend String operator+(const String&, const value_type*);

    friend String& operator-=(String&, const String&);
    friend String operator-(const String&, const String&);

    friend bool operator==(const String&, const String&);
    friend bool operator!=(const String&, const String&);

    friend bool operator>(const String&, const String&);
    friend bool operator>=(const String&, const String&);

    friend bool operator<(const String&, const String&);
    friend bool operator<=(const String&, const String&);

private:
    value_type* _begin;
    size_type _size;
    size_type _capacity;
};

std::ostream& operator<<(std::ostream&, const String&);
std::istream& operator>>(std::istream&, String&);

String operator+(const String&, const String&);

bool operator==(const String&, const String&);
bool operator!=(const String&, const String&);

bool operator>(const String&, const String&);
bool operator>=(const String&, const String&);

bool operator<(const String&, const String&);
bool operator<=(const String&, const String&);

} // namespace Structures::STL