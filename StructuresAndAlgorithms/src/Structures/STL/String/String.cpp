#include "String.h"

namespace Structures {

using size_type = String::size_type;
using value_type = String::value_type;
using pointer = String::pointer;
using reference = String::reference;
using const_reference = String::const_reference;

String::~String()
{
    freeArray(_begin);
}

String::String()
    : _begin(new value_type[1])
    , _size(0)
    , _capacity(1)
{
}

String::String(size_type count, value_type value)
    : _begin(new value_type[count])
    , _size(count)
    , _capacity(count)
{
    memset(_begin, value, _size);
}

String::String(const value_type* array)
    : _begin(new value_type[1])
    , _size(0)
    , _capacity(1)
{
    for (size_t i = 0; array[i] != String::nullTerminate; ++i) {
        push_back(array[i]);
    }
}

String::String(const std::initializer_list<value_type>& iList)
    : _begin(new value_type[1])
    , _size(0)
    , _capacity(1)
{
    reserve(iList.size());
    for (auto i : iList) {
        push_back(i);
    }
}

String::String(const String& toCopy)
{
    *this = toCopy;
}

String::String(String&& toMove)
{
    *this = std::forward<String&&>(toMove);
}

String& String::operator=(const String& toCopy)
{
    // Size or capacity?
    _begin = new value_type[toCopy.capacity()];
    _capacity = toCopy._capacity;
    _size = toCopy._size;

    memcpy(_begin, toCopy._begin, _capacity);
    return *this;
}

String& String::operator=(String&& toMove)
{
    _begin = toMove._begin;
    _size = toMove._size;
    _capacity = toMove._capacity;

    toMove._begin = nullptr;
    toMove._size = 0;
    toMove._capacity = 0;
    return *this;
}

void String::reserve(size_type newCapacity)
{
    if (newCapacity <= _capacity) {
        return;
    }

    value_type* newArr = makeExtendedCopy(_begin, _size, newCapacity);
    freeArray(_begin);

    _begin = newArr;
    _capacity = newCapacity;
}

void String::resize(size_type newSize, value_type symbol)
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

void String::push_back(value_type value)
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

void String::pop_back()
{
    if (empty()) {
        throw "pop_back on empty String";
    }

    back() = nullTerminate;
    --_size;
}

void String::insert(size_type idx, const value_type& value)
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
    value_type* newArr = new value_type[newCapacity];

    memcpy(newArr, _begin, idx);
    newArr[idx] = value;
    memcpy(newArr + idx + 1, _begin + idx, _size - idx);

    freeArray(_begin);

    _begin = newArr;
    ++_size;
    _capacity = newCapacity;
}

void String::clear()
{
    _size = 0;
}

pointer String::begin() const
{
    return _begin;
}

pointer String::end() const
{
    return _begin + _size;
}

reference String::operator[](size_type idx)
{
    return _begin[idx];
}
const_reference String::operator[](size_type idx) const
{
    return _begin[idx];
}

reference String::at(size_type idx)
{
    if (idx < _size) {
        return (*this)[idx];
    }
    throw "out_of_scope exception";
}
const_reference String::at(size_type idx) const
{
    if (idx < _size) {
        return (*this)[idx];
    }
    throw "out_of_scope exception";
}

reference String::back()
{
    return at(_size - 1);
}
const_reference String::back() const
{
    return at(_size - 1);
}

bool String::empty() const noexcept
{
    return _size == 0;
}

size_type String::size() const noexcept
{
    return _size;
}
size_type String::capacity() const noexcept
{
    return _capacity;
}
value_type* String::c_str() noexcept
{
    return _begin;
}
const value_type* String::c_str() const noexcept
{
    return _begin;
}

value_type* String::makeExtendedCopy(
    value_type* array, size_type currentSize, size_type extendedCapacity)
{
    value_type* newArr = new value_type[extendedCapacity];
    mempcpy(newArr, array, currentSize);
    return newArr;
}

void String::freeArray(value_type* array)
{
    delete[] array;
}

} // namespace Structures