#pragma once

#include "ControllBlock.h"

#include <functional>

namespace Structures::STL {

template<typename ObjectType>
class SharedPtr {
public:
    static constexpr auto defaultDeleter = [](ObjectType* obj) { delete obj; };

    SharedPtr(ObjectType* ptr = nullptr, std::function<void(ObjectType*)> deleter = defaultDeleter);

    SharedPtr(const SharedPtr& to_copy);
    SharedPtr(SharedPtr&& to_move);
    SharedPtr& operator=(const SharedPtr& to_copy);
    SharedPtr& operator=(SharedPtr&& to_move);

    ~SharedPtr();

    ObjectType* operator->();
    ObjectType& operator*();
    const ObjectType& operator*() const;
    operator bool() const;

    ObjectType* get() const;

    void reset(
        ObjectType* ptr = nullptr, std::function<void(ObjectType*)> deleter = defaultDeleter);

    size_t use_count() const;

private:
    ObjectType* m_ptr;
    std::function<void(ObjectType*)> m_deleter;

    ControllBlock* m_controlBlock;
};

//////////////////////////////////////////////////////////////////////////////////////////////////
// Implementation
template<typename ObjectType>
SharedPtr<ObjectType>::SharedPtr(ObjectType* ptr, std::function<void(ObjectType*)> deleter)
    : m_ptr(ptr)
    , m_deleter(deleter)
    , m_controlBlock(new ControllBlock())
{
    if (ptr != nullptr) {
        m_controlBlock->increment();
    }
}

template<typename ObjectType>
SharedPtr<ObjectType>::SharedPtr(const SharedPtr& to_copy)
{
    m_ptr = to_copy.m_ptr;
    m_deleter = to_copy.m_deleter;
    m_controlBlock = to_copy.m_controlBlock;

    if (m_ptr) {
        m_controlBlock->increment();
    } else {
        m_controlBlock = new ControllBlock();
    }
}

template<typename ObjectType>
SharedPtr<ObjectType>::SharedPtr(SharedPtr&& to_move)
    : SharedPtr()
{
    std::swap(m_ptr, to_move.m_ptr);
    std::swap(m_deleter, to_move.m_deleter);
    std::swap(m_controlBlock, to_move.m_controlBlock);
}

template<typename ObjectType>
SharedPtr<ObjectType>& SharedPtr<ObjectType>::operator=(const SharedPtr& to_copy)
{
    if (this == &to_copy) {
        return *this;
    }
    m_ptr = to_copy.get();
    m_deleter = to_copy.m_deleter;
    m_controlBlock = to_copy.m_controlBlock;
    m_controlBlock->increment();
    return *this;
}

template<typename ObjectType>
SharedPtr<ObjectType>& SharedPtr<ObjectType>::operator=(SharedPtr&& to_move)
{
    if (this == &to_move) {
        return *this;
    }
    reset();
    std::swap(m_ptr, to_move.m_ptr);
    std::swap(m_deleter, to_move.m_deleter);
    std::swap(m_controlBlock, to_move.m_controlBlock);
    return *this;
}

template<typename ObjectType>
ObjectType* SharedPtr<ObjectType>::operator->()
{
    return m_ptr;
}

template<typename ObjectType>
ObjectType& SharedPtr<ObjectType>::operator*()
{
    return *m_ptr;
}

template<typename ObjectType>
const ObjectType& SharedPtr<ObjectType>::operator*() const
{
    return *m_ptr;
}

template<typename ObjectType>
SharedPtr<ObjectType>::operator bool() const
{
    return m_ptr != nullptr;
}

template<typename ObjectType>
ObjectType* SharedPtr<ObjectType>::get() const
{
    return m_ptr;
}

template<typename ObjectType>
void SharedPtr<ObjectType>::reset(ObjectType* ptr, std::function<void(ObjectType*)> deleter)
{
    if (m_ptr) {
        m_controlBlock->decrement();
    }

    if (m_controlBlock->isZero()) {
        m_deleter(m_ptr);
    } else {
        m_controlBlock = new ControllBlock();
    }

    m_ptr = ptr;
    m_deleter = deleter;
    if (m_ptr) {
        m_controlBlock->increment();
    }
}

template<typename ObjectType>
size_t SharedPtr<ObjectType>::use_count() const
{
    return m_controlBlock->counter();
}

template<typename ObjectType>
SharedPtr<ObjectType>::~SharedPtr()
{
    if (m_ptr) {
        m_controlBlock->decrement();
    }
    if (m_controlBlock->isZero()) {
        m_deleter(m_ptr);
        delete m_controlBlock;
    }
    m_ptr = nullptr;
    m_deleter = defaultDeleter;
}

} // namespace Structures::STL
