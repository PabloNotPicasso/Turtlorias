#pragma once

#include "VectorHelper.h"
#include "iterator/BaseRandomAccessIterator.h"

namespace Structures::STL {

template<typename T, typename Allocator = std::allocator<T>>
class Vector {
public:
    using Helper = VectorHelper<T, Allocator>;

    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = size_t;

    using iterator = BaseRandomAccessIterator<T>;
    using const_iterator = BaseRandomAccessIterator<const T>;

    static constexpr size_t capacityMultiplier = 2U;

public:
    Vector()
        : _begin(Helper::createArray(1U))
        , _size(0)
        , _capacity(1)
    {
    }

    explicit Vector(size_type count)
        : _begin(Helper::createArray(count))
        , _size(count)
        , _capacity(count)
    {
        try {
            Helper::constructArray(_begin, _begin + _size);
        } catch (...) {
            Helper::freeRawArray(_begin, _capacity);
            throw;
        }
    }

    Vector(size_type count, const value_type& value)
        : _begin(Helper::createArray(count))
        , _size(count)
        , _capacity(count)
    {
        try {
            Helper::constructArray(_begin, _begin + _size, value);
        } catch (...) {
            Helper::freeRawArray(_begin, _capacity);
            throw;
        }
    }

    Vector(const Vector& toCopy)
    {
        _begin = Helper::makeExtendedCopy(toCopy._begin, toCopy.size(), toCopy.size());
        _size = toCopy.size();
        _capacity = toCopy.size();
    }

    Vector(Vector&& toMove)
    {
        _begin = toMove._begin;
        _size = toMove._size;
        _capacity = toMove._capacity;

        toMove._begin = nullptr;
        toMove._size = 0;
        toMove._capacity = 0;
    }

    explicit Vector(std::initializer_list<T> iList)
    {
        auto newCapacity = iList.size();
        auto newArray = Helper::createArray(newCapacity);

        pointer toCreateIt = newArray;
        try {
            for (auto ilIt = iList.begin(); ilIt != iList.end(); ++ilIt, ++toCreateIt) {
                new (toCreateIt) T(*ilIt);
            }
        } catch (...) {
            Helper::deleteAndFree(newArray, newCapacity, toCreateIt - newArray);
            throw;
        }
        _begin = newArray;
        _size = newCapacity;
        _capacity = newCapacity;
    }

    Vector& operator=(const Vector& toCopy)
    {
        Vector copy(toCopy);
        swap(copy);
        return *this;
    }

    Vector& operator=(Vector&& toMove)
    {
        swap(toMove);
        return *this;
    }

    Vector& operator=(std::initializer_list<T> iList)
    {
        Vector toCopy(iList);
        swap(toCopy);
        return *this;
    }

    ~Vector()
    {
        if (_begin) {
            Helper::deleteAndFree(_begin, _capacity, _size);
        }
    }

    void reserve(size_type newCapacity)
    {
        if (newCapacity <= _capacity) {
            return;
        }

        pointer newArr = Helper::makeExtendedCopy(_begin, _size, newCapacity);

        Helper::deleteAndFree(_begin, _capacity, _size);

        _begin = newArr;
        _capacity = newCapacity;
    }

    void resize(size_type newSize)
    {
        if (newSize <= _size) {
            return;
        }

        if (newSize <= _capacity) {
            Helper::constructArray(_begin + _size, _begin + newSize);
            _size = newSize;
        } else {
            auto newCapacity = newSize;

            auto newArr = Helper::makeExtendedCopy(_begin, _size, newSize);
            try {
                Helper::constructArray(newArr + _size, newArr + newSize);
            } catch (...) {
                Helper::freeRawArray(newArr, newCapacity);
                throw;
            }
            Helper::deleteAndFree(_begin, _capacity, _size);

            _begin = newArr;
            _size = newSize;
            _capacity = newCapacity;
        }
    }
    void resize(size_type newSize, const value_type& value)
    {
        if (newSize <= _size) {
            return;
        }

        if (newSize <= _capacity) {
            Helper::constructArray(_begin + _size, _begin + newSize, value);
            _size = newSize;
        } else {
            auto newCapacity = newSize;

            auto newArr = Helper::makeExtendedCopy(_begin, _size, newSize);
            try {
                Helper::constructArray(newArr + _size, newArr + newSize, value);
            } catch (...) {
                Helper::freeRawArray(newArr, newCapacity);
                throw;
            }
            Helper::deleteAndFree(_begin, _capacity, _size);

            _begin = newArr;
            _size = newSize;
            _capacity = newCapacity;
        }
    }

    void push_back(const value_type& value)
    {
        emplace_back(value);
    }
    void push_back(value_type&& value)
    {
        emplace_back(std::move(value));
    }
    template<typename... Args>
    void emplace_back(Args&&... args)
    {
        if (_size < _capacity) {
            Helper::constructElement(_begin + _size, std::forward<Args>(args)...);
            ++_size;
            return;
        }

        size_type newCapacity = _capacity * capacityMultiplier;
        auto newArr = Helper::makeExtendedCopy(_begin, _size, newCapacity);

        try {
            // Add new element
            Helper::constructElement(newArr + _size, std::forward<Args>(args)...);
        } catch (...) {
            Helper::deleteAndFree(newArr, newCapacity, _size);
            throw;
        }
        Helper::deleteAndFree(_begin, _capacity, _size);
        _begin = newArr;
        ++_size;
        _capacity = newCapacity;
    }
    void pop_back()
    {
        if (empty()) {
            throw "pop_back on empty vector";
        }

        --_size;
        Helper::destroyElement(_begin + _size);
    }

    void insert(size_type idx, const value_type& value)
    {
        if (_size < _capacity) {
            size_type reverseIdx = _size;
            // exception ?
            for (; reverseIdx > idx; --reverseIdx) {
                Helper::constructElement(_begin + reverseIdx, _begin[reverseIdx - 1]);
                Helper::destroyElement(_begin + reverseIdx - 1);
            }
            Helper::constructElement(_begin + idx, value);
            ++_size;
            return;
        }

        auto newCapacity = _capacity * capacityMultiplier;
        T* newArr = Helper::createArray(newCapacity);

        try {
            Helper::copyConstructElements(newArr, _begin, idx);
            Helper::constructElement(newArr + idx, value);
            Helper::copyConstructElements(newArr + idx + 1, _begin + idx, _size - idx);
        } catch (...) {
            Helper::freeRawArray(newArr, newCapacity);
            throw;
        }

        Helper::deleteAndFree(_begin, _capacity, _size);
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

    iterator begin() noexcept
    {
        return _begin;
    }
    const_iterator begin() const noexcept
    {
        return _begin;
    }
    const_iterator cbegin() const noexcept
    {
        return _begin;
    }

    iterator end() noexcept
    {
        return _begin + _size;
    }
    const_iterator end() const noexcept
    {
        return _begin + _size;
    }
    const_iterator cend() const noexcept
    {
        return _begin + _size;
    }

    pointer data()
    {
        return _begin;
    }
    const pointer data() const
    {
        return _begin;
    }

    /**
     * @brief Clears vector calling destructors for elements. Allocated data will not be released
     */
    void clear()
    {
        destroyElements(_begin, _begin + _size);
        _size = 0;
    }

    /**
     * @brief Reduces \b capacity to \b size
     * @note Invalidates pointers/references
     */
    void shrink_to_fit()
    {
        if (_size == _capacity) {
            return;
        }
        auto shrinkedCopy = Helper::makeExtendedCopy(_begin, _size, _size);
        Helper::deleteAndFree(_begin, _capacity, _size);

        _begin = shrinkedCopy;
        _capacity = _size;
    }

    /**
     * @brief Swap all data members to \p toSwap
     *
     * @param toSwap
     */
    void swap(Vector& toSwap) noexcept
    {
        std::swap(_begin, toSwap._begin);
        std::swap(_size, toSwap._size);
        std::swap(_capacity, toSwap._capacity);
    }

private:
    pointer _begin;
    size_type _size;
    size_type _capacity;
};

} // namespace Structures::STL