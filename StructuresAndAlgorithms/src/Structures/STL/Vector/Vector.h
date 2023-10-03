#pragma once

#include "VectorBase.h"

namespace Structures::STL {

template<typename T, typename Allocator = std::allocator<T>>
class Vector : public VectorBase<T, Allocator> {
public:
    using Base = VectorBase<T, Allocator>;

    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = size_t;

    using iterator = pointer;
    using const_iterator = const_pointer;

    static constexpr size_t capacityMultiplier = 2U;

public:
    Vector()
        : _begin(Base::createArray(1U))
        , _size(0)
        , _capacity(1)
    {
    }

    explicit Vector(size_type count)
        : _begin(Base::createArray(count))
        , _size(count)
        , _capacity(count)
    {
        try {
            Base::constructArray(_begin, _begin + _size);
        } catch (...) {
            Base::freeRawArray(_begin, _capacity);
            throw;
        }
    }

    Vector(size_type count, const value_type& value)
        : _begin(Base::createArray(count))
        , _size(count)
        , _capacity(count)
    {
        try {
            Base::constructArray(_begin, _begin + _size, value);
        } catch (...) {
            Base::freeRawArray(_begin, _capacity);
            throw;
        }
    }

    Vector(const Vector& toCopy)
    {
        _begin = Base::makeExtendedCopy(toCopy._begin, toCopy.size(), toCopy.size());
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
        auto newArray = Base::createArray(newCapacity);

        pointer toCreateIt = newArray;
        try {
            for (auto ilIt = iList; ilIt != iList.end(); ++ilIt, ++toCreateIt) {
                new (toCreateIt) T(*ilIt);
            }
        } catch (...) {
            Base::deleteAndFree(newArray, newCapacity, toCreateIt - newArray);
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
            Base::deleteAndFree(_begin, _capacity, _size);
        }
    }

    void reserve(size_type newCapacity)
    {
        if (newCapacity <= _capacity) {
            return;
        }

        pointer newArr = Base::makeExtendedCopy(_begin, _size, newCapacity);

        Base::deleteAndFree(_begin, _capacity, _size);

        _begin = newArr;
        _capacity = newCapacity;
    }

    void resize(size_type newSize)
    {
        if (newSize <= _size) {
            return;
        }

        if (newSize <= _capacity) {
            Base::constructArray(_begin + _size, _begin + newSize);
            _size = newSize;
        } else {
            auto newCapacity = newSize;

            auto newArr = Base::makeExtendedCopy(_begin, _size, newSize);
            try {
                Base::constructArray(newArr + _size, newArr + newSize);
            } catch (...) {
                Base::freeRawArray(newArr, newCapacity);
                throw;
            }
            Base::deleteAndFree(_begin, _capacity, _size);

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
            Base::constructArray(_begin + _size, _begin + newSize, value);
            _size = newSize;
        } else {
            auto newCapacity = newSize;

            auto newArr = Base::makeExtendedCopy(_begin, _size, newSize);
            try {
                Base::constructArray(newArr + _size, newArr + newSize, value);
            } catch (...) {
                Base::freeRawArray(newArr, newCapacity);
                throw;
            }
            Base::deleteAndFree(_begin, _capacity, _size);

            _begin = newArr;
            _size = newSize;
            _capacity = newCapacity;
        }
    }

    void push_back(const value_type& value)
    {
        if (_size < _capacity) {
            // We can skip try-catch here
            Base::constructElement(_begin + _size, value);
            ++_size;
            return;
        }

        size_type newCapacity = _capacity * capacityMultiplier;
        auto newArr = Base::makeExtendedCopy(_begin, _size, newCapacity);

        try {
            // Add new element
            Base::constructElement(newArr + _size, value);
        } catch (...) {
            Base::deleteAndFree(newArr, newCapacity, _size);
            throw;
        }
        Base::deleteAndFree(_begin, _capacity, _size);
        _begin = newArr;
        ++_size;
        _capacity = newCapacity;
    }
    void push_back(value_type&& value)
    {
        if (_size < _capacity) {
            // We can skip try-catch here
            Base::constructElement(_begin + _size, std::move(value));
            ++_size;
            return;
        }

        size_type newCapacity = _capacity * capacityMultiplier;
        auto newArr = Base::makeExtendedCopy(_begin, _size, newCapacity);

        try {
            // Add new element
            Base::constructElement(newArr + _size, std::move(value));
        } catch (...) {
            Base::deleteAndFree(newArr, newCapacity, _size);
            throw;
        }
        Base::deleteAndFree(_begin, _capacity, _size);
        _begin = newArr;
        ++_size;
        _capacity = newCapacity;
    }

    template<typename... Args>
    void emplace_back(Args... args)
    {
        if (_size < _capacity) {
            Base::constructElement(_begin + _size, std::forward<Args>(args)...);
            ++_size;
            return;
        }

        size_type newCapacity = _capacity * capacityMultiplier;
        auto newArr = Base::makeExtendedCopy(_begin, _size, newCapacity);

        try {
            // Add new element
            Base::constructElement(newArr + _size, std::forward<Args>(args)...);
        } catch (...) {
            Base::deleteAndFree(newArr, newCapacity, _size);
            throw;
        }
        Base::deleteAndFree(_begin, _capacity, _size);
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
        Base::destroyElement(_begin + _size);
    }

    void insert(size_type idx, const value_type& value)
    {
        if (_size < _capacity) {
            size_type reverseIdx = _size;
            // exception ?
            for (; reverseIdx > idx; --reverseIdx) {
                Base::constructElement(_begin + reverseIdx, _begin[reverseIdx - 1]);
                Base::destroyElement(_begin + reverseIdx - 1);
            }
            Base::constructElement(_begin + idx, value);
            ++_size;
            return;
        }

        auto newCapacity = _capacity * capacityMultiplier;
        T* newArr = Base::createArray(newCapacity);

        try {
            Base::copyConstructElements(newArr, _begin, idx);
            Base::constructElement(newArr + idx, value);
            Base::copyConstructElements(newArr + idx + 1, _begin + idx, _size - idx);
        } catch (...) {
            Base::freeRawArray(newArr, newCapacity);
            throw;
        }

        Base::deleteAndFree(_begin, _capacity, _size);
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

    iterator end() noexcept
    {
        return _begin + _size;
    }
    const_iterator end() const noexcept
    {
        return _begin + _size;
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
        auto shrinkedCopy = Base::makeExtendedCopy(_begin, _size, _size);
        Base::deleteAndFree(_begin, _capacity, _size);

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