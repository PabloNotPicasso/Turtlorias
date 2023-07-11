#pragma once
#include <cassert>
#include <typeindex>
namespace Structures {

class Any {
public:
    Any();
    ~Any();

    template<typename T>
    Any(const T& obj);

    template<typename T>
    bool is();

    template<typename T>
    T as();

    template<typename T>
    Any& operator=(const T& obj);

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
bool Any::is()
{
    return typeid(T).hash_code() == ind.hash_code();
}

template<typename T>
T Any::as()
{
    assert(is<T>());
    return *(static_cast<T*>(ptr));
}

template<typename T>
Any& Any::operator=(const T& obj)
{
    reset();
    ptr = new T(obj);
    ind = typeid(T);
    return *this;
}

} // namespace Structures