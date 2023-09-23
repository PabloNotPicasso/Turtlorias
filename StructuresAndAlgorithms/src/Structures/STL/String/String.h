#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <utility>

namespace Structures {

class String {
public:
    using size_type = size_t;
    using value_type = char;
    using pointer = char*;
    using reference = char&;
    using const_reference = const char&;

    constexpr static value_type nullTerminate = '\0';

public:
    String()
        : _begin(new value_type[1])
        , _size(0)
        , _capacity(1)
    {
    }

    explicit String(size_type count, value_type value = nullTerminate)
        : _begin(new value_type[count])
        , _size(count)
        , _capacity(count)
    {
        memset(_begin, value, _size);
    }

    ~String()
    {
        freeArray(_begin);
    }

    void reserve(size_type newCapacity)
    {
        if (newCapacity <= _capacity) {
            return;
        }

        pointer newArr = makeExtendedCopy(_begin, _size, newCapacity);
        freeArray(_begin);

        _begin = newArr;
        _capacity = newCapacity;
    }

    void resize(size_type newSize, value_type symbol = nullTerminate)
    {
        if (newSize <= _size) {
            return;
        }

        if (newSize <= _capacity) {
            memset(_begin + _size, symbol, newSize - _size);
            _size = newSize;
        } else {
            auto newArr = makeExtendedCopy(_begin, _size, newSize);
            memset(newArr + _size, symbol, newSize - _size);
            freeArray(_begin);
            _begin = newArr;
            _size = newSize;
            _capacity = newSize;
        }
    }

    void push_back(value_type value)
    {
        if (_size < _capacity) {
            _begin[_size] = value;
            ++_size;
            return;
        }

        size_type newCapacity = _capacity * 2;
        auto newArr = makeExtendedCopy(_begin, _size, newCapacity);

        newArr[_size] = value;
        freeArray(_begin);

        _begin = newArr;
        ++_size;
        _capacity = newCapacity;
    }

    void pop_back()
    {
        if (empty()) {
            throw "pop_back on empty String";
        }

        back() = nullTerminate;
        --_size;
    }

    void insert(size_type idx, const value_type& value)
    {
        if (_size < _capacity) {
            size_type reverseIdx = _size;
            for (; reverseIdx > idx; --reverseIdx) {
                _begin[reverseIdx] = _begin[reverseIdx - 1];
            }
            _begin[idx] = value;
            ++_size;
            return;
        }

        auto newCapacity = _capacity * 2;
        pointer newArr = new value_type[newCapacity];

        memcpy(newArr, _begin, idx);
        newArr[idx] = value;
        memcpy(newArr + idx + 1, _begin + idx, _size - idx);

        freeArray(_begin);

        _begin = newArr;
        ++_size;
        _capacity = newCapacity;
    }

    reference operator[](size_type idx)
    {
        return _begin[idx];
    }
    const_reference operator[](size_type idx) const
    {
        return _begin[idx];
    }

    reference at(size_type idx)
    {
        if (idx < _size) {
            return (*this)[idx];
        }
        throw "out_of_scope exception";
    }
    const_reference at(size_type idx) const
    {
        if (idx < _size) {
            return (*this)[idx];
        }
        throw "out_of_scope exception";
    }

    reference back()
    {
        return at(_size - 1);
    }
    const_reference back() const
    {
        return at(_size - 1);
    }

    bool empty() const noexcept
    {
        return _size;
    }

    size_type size() const noexcept
    {
        return _size;
    }
    size_type capacity() const noexcept
    {
        return _capacity;
    }

protected:
    pointer makeExtendedCopy(pointer array, size_type currentSize, size_type extendedCapacity)
    {
        pointer newArr = new value_type[extendedCapacity];
        mempcpy(newArr, array, currentSize);
        return newArr;
    }

    void freeArray(pointer array)
    {
        delete[] array;
    }

private:
    pointer _begin;
    size_type _size;
    size_type _capacity;
};

} // namespace Structures