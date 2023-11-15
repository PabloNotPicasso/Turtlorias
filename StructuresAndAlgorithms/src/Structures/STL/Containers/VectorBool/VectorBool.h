#pragma once

#include "Structures/STL/Containers/Vector/Vector.h"
#include "BitController.h"

namespace Structures::STL {

template<>
class Vector<bool> : public Vector<char> {
public:
    using byte = char;

    using value_type = bool;
    using reference = BitController<byte>;
    using const_reference = const BitController<const byte>;
    using size_type = size_t;

    using pointer = bool*;
    using const_pointer = const bool*;

    using iterator = BaseRandomAccessIterator<reference>;
    using const_iterator = BaseRandomAccessIterator<const_reference>;

public:
    Vector();
    explicit Vector(size_type count);
    Vector(size_type count, const value_type& value);
    Vector(const Vector& toCopy);
    Vector(Vector&& toMove);
    explicit Vector(std::initializer_list<bool> iList);
    Vector& operator=(const Vector& toCopy);
    Vector& operator=(Vector&& toMove);
    Vector& operator=(std::initializer_list<bool> iList);
    ~Vector();

    void reserve(size_type newCapacity);
    void resize(size_type newSize);
    void resize(size_type newSize, const value_type& value);

    void push_back(const value_type& value);
    void push_back(value_type&& value);
    template<typename... Args>
    void emplace_back(Args... args);

    void pop_back();

    void insert(size_type idx, const value_type& value);

    reference operator[](size_type idx);
    const_reference operator[](size_type idx) const;
    reference at(size_type idx);
    const_reference at(size_type idx) const;
    reference back();
    const_reference back() const;
    bool empty() const noexcept;
    size_type size() const noexcept;
    size_type capacity() const noexcept;
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;

    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;
    pointer data();
    const pointer data() const;

    void clear();
    void shrink_to_fit();

    void swap(Vector& toSwap) noexcept;

protected:
    void extend();

    byte* getBytePtr(const size_t index);
    const byte* getBytePtr(const size_t index) const;
};

} // namespace Structures::STL