#pragma once

#include <cassert>
#include <typeindex>

namespace Structures {

class Any {
public:
    Any();
    ~Any();

    Any(const Any&) = delete;
    Any& operator=(const Any& obj) = delete;

    template<typename T>
    Any(const T& obj);
    template<typename T>
    Any& operator=(const T& obj);

    template<typename T>
    bool is() const;

    template<typename T>
    T& as();
    template<typename T>
    const T& as() const;

    void reset();

private:
    std::type_index ind;
    void* ptr;
};

template<typename T>
Any::Any(const T& obj)
    : ind(typeid(T))
{
    ptr = new T(obj);
}

template<typename T>
Any& Any::operator=(const T& obj)
{
    reset();
    ptr = new T(obj);
    ind = typeid(T);
    return *this;
}

template<typename T>
bool Any::is() const
{
    return typeid(T).hash_code() == ind.hash_code();
}

template<typename T>
T& Any::as()
{
    assert(is<T>());
    return *(static_cast<T*>(ptr));
}

template<typename T>
const T& Any::as() const
{
    assert(is<T>());
    return *(static_cast<T*>(ptr));
}

} // namespace Structures