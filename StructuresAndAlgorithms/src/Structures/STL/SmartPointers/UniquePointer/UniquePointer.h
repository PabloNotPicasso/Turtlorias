#pragma once

#include <functional>

namespace Structures::STL {

class DefaultDeleter {
public:
    constexpr DefaultDeleter() noexcept = default;
    template<typename ObjectType>
    void operator()(ObjectType* toDelete) const
    {
        delete toDelete;
    };
};

template<typename ObjectType, typename Deleter = DefaultDeleter>
class UniquePtr {
public:
    UniquePtr(const UniquePtr& to_copy) = delete;
    UniquePtr& operator=(const UniquePtr& to_copy) = delete;

    UniquePtr(ObjectType* ptr = nullptr, Deleter deleter = Deleter{});
    UniquePtr(UniquePtr&& to_move);
    UniquePtr& operator=(UniquePtr&& to_move);

    ~UniquePtr();

    ObjectType* operator->() const;
    ObjectType& operator*();
    const ObjectType& operator*() const;
    operator bool() const;

    ObjectType* get() const;
    Deleter& get_deleter() const;

    void reset(ObjectType* ptr = nullptr);
    ObjectType* release();
    void swap(UniquePtr&);

private:
    ObjectType* m_ptr;
    Deleter m_deleter;
};

//////////////////////////////////////////////////////////////////////////////////////////////////
// Implementation
template<typename ObjectType, typename Deleter>
UniquePtr<ObjectType, Deleter>::UniquePtr(ObjectType* ptr, Deleter deleter)
    : m_ptr{ptr}
    , m_deleter{deleter}
{
}

template<typename ObjectType, typename Deleter>
UniquePtr<ObjectType, Deleter>::UniquePtr(UniquePtr&& to_move)
    : UniquePtr()
{
    std::swap(m_ptr, to_move.m_ptr);
}

template<typename ObjectType, typename Deleter>
UniquePtr<ObjectType, Deleter>& UniquePtr<ObjectType, Deleter>::operator=(UniquePtr&& to_move)
{
    if (this == &to_move) {
        return *this;
    }
    reset();
    std::swap(m_ptr, to_move.m_ptr);
    return *this;
}

template<typename ObjectType, typename Deleter>
ObjectType* UniquePtr<ObjectType, Deleter>::operator->() const
{
    return m_ptr;
}

template<typename ObjectType, typename Deleter>
ObjectType& UniquePtr<ObjectType, Deleter>::operator*()
{
    return *m_ptr;
}

template<typename ObjectType, typename Deleter>
const ObjectType& UniquePtr<ObjectType, Deleter>::operator*() const
{
    return *m_ptr;
}

template<typename ObjectType, typename Deleter>
UniquePtr<ObjectType, Deleter>::operator bool() const
{
    return m_ptr != nullptr;
}

template<typename ObjectType, typename Deleter>
ObjectType* UniquePtr<ObjectType, Deleter>::get() const
{
    return m_ptr;
}

template<typename ObjectType, typename Deleter>
Deleter& UniquePtr<ObjectType, Deleter>::get_deleter() const
{
    return m_deleter;
}

template<typename ObjectType, typename Deleter>
void UniquePtr<ObjectType, Deleter>::reset(ObjectType* ptr)
{
    m_deleter(m_ptr);
    m_ptr = ptr;
}

template<typename ObjectType, typename Deleter>
ObjectType* UniquePtr<ObjectType, Deleter>::release()
{
    auto toReturn = m_ptr;
    m_ptr = nullptr;
    return toReturn;
}

template<typename ObjectType, typename Deleter>
void UniquePtr<ObjectType, Deleter>::swap(UniquePtr& toSwap)
{
    std::swap(m_ptr, toSwap.m_ptr);
    std::swap(m_deleter, toSwap.m_deleter);
}

template<typename ObjectType, typename Deleter>
UniquePtr<ObjectType, Deleter>::~UniquePtr()
{
    reset();
}

} // namespace Structures::STL
