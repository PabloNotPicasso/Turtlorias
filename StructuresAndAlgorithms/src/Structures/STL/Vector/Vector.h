#pragma once

#include <cstddef>
#include <cstdint>
#include <utility>

namespace Structures {

template<typename T>
class Vector {
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = size_t;
    using byte = int8_t;

    using iterator = pointer;
    using const_iterator = const_pointer;

public:
    Vector()
        : _begin(createArray(1U))
        , _size(0)
        , _capacity(1)
    {
    }

    explicit Vector(size_type count)
        : _begin(createArray(count))
        , _size(count)
        , _capacity(count)
    {
        pointer toCreateIt = _begin;
        try {
            for (; toCreateIt != _begin + _size; ++toCreateIt) {
                new (toCreateIt) T();
            }
        } catch (...) {
            freeArray(_begin, toCreateIt - _begin);
            throw;
        }
    }

    Vector(size_type count, const value_type& value)
        : _begin(createArray(count))
        , _size(count)
        , _capacity(count)
    {
        pointer toCreateIt = _begin;
        try {
            for (; toCreateIt != _begin + _size; ++toCreateIt) {
                new (toCreateIt) T(value);
            }
        } catch (...) {
            freeArray(_begin, toCreateIt - _begin);
            throw;
        }
    }

    Vector(const Vector& toCopy)
    {
        auto newArray = createArray(toCopy.size());

        pointer toCreateIt = newArray;
        try {
            for (pointer toCopyIt = toCopy._begin; toCopyIt != toCopy.end();
                 ++toCopyIt, ++toCreateIt) {
                new (toCreateIt) T(*toCopyIt);
            }
        } catch (...) {
            freeArray(newArray, toCreateIt - newArray);
            throw;
        }
        _begin = newArray;
        _size = toCopy.size();
        _capacity = _size;
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
        auto newArray = createArray(iList.size());

        pointer toCreateIt = newArray;
        try {
            for (auto ilIt = iList; ilIt != iList.end(); ++ilIt, ++toCreateIt) {
                new (toCreateIt) T(*ilIt);
            }
        } catch (...) {
            freeArray(newArray, toCreateIt - newArray);
            throw;
        }
        _begin = newArray;
        _size = iList.size();
        _capacity = _size;
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
        freeArray(_begin, _size);
    }

    void reserve(size_type newCapacity)
    {
        if (newCapacity <= _capacity) {
            return;
        }

        pointer newArr = makeExtendedCopy(_begin, _size, newCapacity);
        freeArray(_begin, _size);

        _begin = newArr;
        _capacity = newCapacity;
    }

    void resize(size_type newSize)
    {
        if (newSize <= _size) {
            return;
        }

        if (newSize <= _capacity) {
            size_type toConstructIdx = _size;
            try {
                for (; toConstructIdx < newSize; ++toConstructIdx) {
                    new (_begin + toConstructIdx) T();
                }
            } catch (...) {
                for (size_type toDeleteIdx = _size; toDeleteIdx < toConstructIdx; ++toDeleteIdx) {
                    (_begin + toDeleteIdx)->~T();
                }
                throw;
            }
            _size = newSize;
        } else {
            auto newArr = makeExtendedCopy(_begin, _size, newSize);
            size_type toConstructIdx = _size;
            try {
                for (; toConstructIdx < newSize; ++toConstructIdx) {
                    new (newArr + toConstructIdx) T();
                }
            } catch (...) {
                freeArray(newArr, toConstructIdx);
                throw;
            }

            freeArray(_begin, _size);
            _begin = newArr;
            _size = newSize;
            _capacity = newSize;
        }
    }
    void resize(size_type newSize, const value_type& value)
    {
        if (newSize <= _size) {
            return;
        }

        if (newSize <= _capacity) {
            size_type toConstructIdx = _size;
            try {
                for (; toConstructIdx < newSize; ++toConstructIdx) {
                    new (_begin + toConstructIdx) T(value);
                }
            } catch (...) {
                for (size_type toDeleteIdx = _size; toDeleteIdx < toConstructIdx; ++toDeleteIdx) {
                    (_begin + toDeleteIdx)->~T();
                }
                throw;
            }
            _size = newSize;
        } else {
            auto newArr = makeExtendedCopy(_begin, _size, newSize);
            size_type toConstructIdx = _size;
            try {
                for (; toConstructIdx < newSize; ++toConstructIdx) {
                    new (newArr + toConstructIdx) T(value);
                }
            } catch (...) {
                freeArray(newArr, toConstructIdx);
                throw;
            }

            freeArray(_begin, _size);
            _begin = newArr;
            _size = newSize;
            _capacity = newSize;
        }
    }

    void push_back(const value_type& value)
    {
        if (_size < _capacity) {
            // We can skip try-catch here
            new (_begin + _size) T(value);
            ++_size;
            return;
        }

        size_type newCapacity = _capacity * 2;
        auto newArr = makeExtendedCopy(_begin, _size, newCapacity);

        try {
            // Add new element
            new (newArr + _size) T(value);
        } catch (...) {
            freeArray(newArr, _size);
            throw;
        }
        freeArray(_begin, _size);
        _begin = newArr;
        ++_size;
        _capacity = newCapacity;
    }
    void push_back(value_type&& value)
    {
        if (_size < _capacity) {
            // We can skip try-catch here
            new (_begin + _size) T(std::move(value));
            ++_size;
            return;
        }

        size_type newCapacity = _capacity * 2;
        auto newArr = makeExtendedCopy(_begin, _size, newCapacity);

        try {
            // Add new element
            new (newArr + _size) T(std::move(value));
        } catch (...) {
            freeArray(newArr, _size);
            throw;
        }
        freeArray(_begin, _size);
        _begin = newArr;
        ++_size;
        _capacity = newCapacity;
    }

    template<typename... Args>
    void emplace_back(Args... args)
    {
        if (_size < _capacity) {
            new (_begin + _size) T(args...);
            ++_size;
            return;
        }

        size_type newCapacity = _capacity * 2;
        auto newArr = makeExtendedCopy(_begin, _size, newCapacity);

        try {
            // Add new element
            new (newArr + _size) T(args...);
        } catch (...) {
            freeArray(newArr, _size);
            throw;
        }
        freeArray(_begin, _size);
        _begin = newArr;
        ++_size;
        _capacity = newCapacity;
    }
    void pop_back()
    {
        if (empty()) {
            throw "pop_back on empty vector";
        }

        back().~T();
        --_size;
    }

    void insert(size_type idx, const value_type& value)
    {
        if (_size < _capacity) {
            size_type reverseIdx = _size;
            // exception ?
            for (; reverseIdx > idx; --reverseIdx) {
                new (_begin + reverseIdx) T(_begin[reverseIdx - 1]);
                _begin[reverseIdx - 1].~T();
            }
            new (_begin + idx) T(value);
            ++_size;
            return;
        }

        auto newCapacity = _capacity * 2;
        T* newArr = createArray(newCapacity);
        size_t originalIdx = 0;
        size_t newArrayIdx = 0;
        for (; originalIdx < idx; ++newArrayIdx) {
            new (newArr + newArrayIdx) T(_begin[originalIdx++]);
        }
        new (newArr + idx) T(value);
        ++newArrayIdx;
        for (; originalIdx < _size; ++newArrayIdx) {
            new (newArr + newArrayIdx) T(_begin[originalIdx++]);
        }

        freeArray(_begin, _size);
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
        deleteElements(_begin, _size);
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
        auto shrinkedCopy = makeExtendedCopy(_begin, _size, _size);
        freeArray(_begin, _size);

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

protected:
    /**
     * @brief Create copy of \p array which contains \p extendedCapacity elements
     * First \p currentSize elements will be copied from \p array
     *
     * @param array
     * @param currentSize
     * @param extendedCapacity
     * @return T*
     */
    T* makeExtendedCopy(pointer array, size_type currentSize, size_type extendedCapacity)
    {
        T* newArr = createArray(extendedCapacity);

        size_type idxToCopy = 0;
        try {
            for (; idxToCopy < currentSize; ++idxToCopy) {
                new (newArr + idxToCopy) T(array[idxToCopy]);
            }
        } catch (...) {
            freeArray(_begin, idxToCopy);
            throw;
        }
        return newArr;
    }

    /**
     * @brief Create a raw unintitialized array with \p size elements
     *
     * @param size
     * @return T*
     */
    T* createArray(size_t size)
    {
        return reinterpret_cast<T*>(new byte[size * sizeof(T)]);
    }

    /**
     * @brief Free allocated raw \p array without calling destructors
     *
     * @param array
     */
    void freeRawArray(T* array)
    {
        delete[] reinterpret_cast<byte*>(array);
    }

    /**
     * @brief Call destructors for first \b size elements of \b array
     *
     * @param array
     * @param size
     */
    void deleteElements(T* array, size_type size)
    {
        for (size_type idxToDelete = 0; idxToDelete < size; ++idxToDelete) {
            array[idxToDelete].~T();
        }
    }

    /**
     * @brief Free allocated \p array after calling destructors for first \p size elements
     *
     * @param array
     * @param size
     */
    void freeArray(T* array, size_type size)
    {
        deleteElements(array, size);
        freeRawArray(array);
    }

private:
    pointer _begin;
    size_type _size;
    size_type _capacity;
};

} // namespace Structures