#pragma once

#include "ControllBlock.h"

#include <functional>

namespace Structures {

template<typename ObjectType>
class SharedPtr {
public:
    static constexpr auto defaultDeleter = [](ObjectType* obj) { delete obj; };
    SharedPtr(ObjectType* ptr = nullptr, std::function<void(ObjectType*)> deleter = defaultDeleter);

    SharedPtr(const SharedPtr& to_copy);

    ~SharedPtr();

    SharedPtr& operator=(const SharedPtr& to_copy);

    ObjectType* get() const;

    void reset();

private:
    void try_to_delete();

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
    m_ptr = to_copy.get();
    m_deleter = to_copy.m_deleter;
    m_controlBlock = to_copy.m_controlBlock;
    m_controlBlock->increment();
}

template<typename ObjectType>
SharedPtr<ObjectType>& SharedPtr<ObjectType>::operator=(const SharedPtr& to_copy)
{
    m_ptr = to_copy.get();
    m_deleter = to_copy.m_deleter;
    m_controlBlock = to_copy.m_controlBlock;
    m_controlBlock->increment();
    return *this;
}

template<typename ObjectType>
ObjectType* SharedPtr<ObjectType>::get() const
{
    return m_ptr;
}

template<typename ObjectType>
void SharedPtr<ObjectType>::SharedPtr::reset()
{
    try_to_delete();
}

template<typename ObjectType>
SharedPtr<ObjectType>::~SharedPtr()
{
    if (m_controlBlock && m_controlBlock->isZero()) {
        m_deleter(m_ptr);
        delete m_controlBlock;
    }
}

template<typename ObjectType>
void SharedPtr<ObjectType>::try_to_delete()
{
    if (m_controlBlock) {
        if (!m_controlBlock->isZero()) {
            m_controlBlock->decrement();
        }
        if (m_controlBlock->isZero()) {
            m_deleter(m_ptr);
            delete m_controlBlock;
        }
    }
    m_controlBlock = nullptr;
    m_ptr = nullptr;
}

} // namespace Structures
