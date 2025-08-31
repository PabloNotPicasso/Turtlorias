#pragma once

#include <utility>

namespace Structures::STL {

template<typename T>
struct BaseListNode {
    BaseListNode()
        : _previous(this)
        , _next(this)
    {
    }

    BaseListNode* _previous;
    BaseListNode* _next;
};

template<typename T>
struct ListNode : public BaseListNode<T> {
    template<typename... Args>
    ListNode(Args... args)
        : _value(std::forward<Args>(args)...)
    {
    }

    ListNode(const T& value)
        : _value(value)
    {
    }

    ListNode(T&& value)
        : _value(std::move(value))
    {
    }
    T _value;
};

} // namespace Structures::STL
