#pragma once

#include <utility>

namespace Structures::STL {

template<typename T>
struct BaseNode {
    BaseNode()
        : _next(nullptr)
    {
    }
    BaseNode* _next;
};

template<typename T>
struct Node : public BaseNode<T> {
    template<typename... Args>
    Node(Args... args)
        : _value(std::forward<Args>(args)...)
    {
    }

    Node(const T& value)
        : _value(value)
    {
    }

    Node(T&& value)
        : _value(std::move(value))
    {
    }

    T _value;
};

} // namespace Structures::STL