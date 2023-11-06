#pragma once

#include "ForwardListHelper.h"
#include "Logger/LoggerApi.h"
#include "Node.h"
#include "iterator/ForwardListIterator.h"

namespace Structures::STL {

template<typename T, typename NodeAllocator = std::allocator<Node<T>>>
class ForwardList : public ForwardListHelper<T, NodeAllocator> {
public:
    using Helper = ForwardListHelper<T, NodeAllocator>;

    using BaseNodeT = BaseNode<T>;
    using NodeT = Node<T>;

    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = size_t;

    using iterator = ForwardListIterator<T, BaseNodeT, NodeT>;
    using const_iterator = ForwardListIterator<const T, BaseNodeT, NodeT>;

public:
    ForwardList() { }

    explicit ForwardList(size_type count)
    {
        for (size_type i = 0; i != count; ++i) {
            emplace_front();
        }
    }

    ForwardList(size_type count, const value_type& value)
    {
        for (size_type i = 0; i != count; ++i) {
            push_front(value);
        }
    }

    ForwardList(const ForwardList& toCopy)
        : ForwardList()
    {
        auto insertIterator = before_begin();
        for (auto& listItem : toCopy) {
            auto newElement = Helper::createNode(*listItem);
            insertIterator = insertAfterNode(insertIterator, iterator(newElement));
        }
    }

    ForwardList(ForwardList&& toMove)
        : ForwardList()
    {
        std::swap(_head, toMove._head);
    }

    explicit ForwardList(std::initializer_list<T> iList)
        : ForwardList()
    {
        auto insertIterator = before_begin();
        for (auto& listItem : iList) {
            auto newElement = Helper::createNode(listItem);
            insertIterator = insertAfterNode(insertIterator, newElement);
        }
    }

    ForwardList& operator=(const ForwardList& toCopy)
    {
        ForwardList copy(toCopy);
        swap(copy);
        return *this;
    }

    ForwardList& operator=(ForwardList&& toMove)
    {
        swap(toMove);
        return *this;
    }

    ForwardList& operator=(std::initializer_list<T> iList)
    {
        ForwardList toCopy(iList);
        swap(toCopy);
        return *this;
    }

    ~ForwardList()
    {
        clear();
    }

    iterator push_front(const value_type& value)
    {
        auto node = Helper::createNode(value);
        return insertAfterNode(&_head, node);
    }

    iterator push_front(value_type&& value)
    {
        auto node = Helper::createNode(std::move(value));
        return insertAfterNode(&_head, node);
    }

    template<typename... Args>
    iterator emplace_front(Args&&... args)
    {
        auto node = Helper::createNode(std::forward<Args>(args)...);
        return insertAfterNode(&_head, node);
    }

    iterator insertAfter(const iterator insertAfterIt, const value_type& valueToInsert)
    {
        auto node = Helper::createNode(valueToInsert);
        return insertAfterNode(insertAfterIt, node);
    }

    void pop_front()
    {
        auto toDelete = static_cast<NodeT*>(_head._next);
        _head->next = toDelete->next;
        Helper::deleteNode(toDelete);
    }

    /**
     * @brief All elements will be destructed. Allocated data will be released
     */
    void clear()
    {
        for (NodeT* toDelete = static_cast<NodeT*>(_head._next); toDelete != nullptr;) {
            NodeT* next = static_cast<NodeT*>(toDelete->_next);
            Helper::deleteNode(toDelete);
            toDelete = next;
        }
        _head._next = nullptr;
    }

    T& front()
    {
        return static_cast<NodeT*>(_head._next)->_value;
    }
    const T& front() const
    {
        return static_cast<NodeT*>(_head._next)->_value;
    }

    iterator before_begin()
    {
        return iterator(&_head);
    }
    const_iterator before_begin() const
    {
        return const_iterator(&_head);
    }

    iterator begin()
    {
        return iterator(_head._next);
    }
    const_iterator begin() const
    {
        return const_iterator(_head._next);
    }
    const_iterator cbegin() const
    {
        return const_iterator(_head._next);
    }

    iterator end()
    {
        return iterator(nullptr);
    }
    const_iterator end() const
    {
        return const_iterator(nullptr);
    }
    const_iterator cend() const
    {
        return const_iterator(nullptr);
    }

    size_type empty() const
    {
        return _head._next == nullptr;
    }

    /**
     * @brief Swap all data members to \p toSwap
     *
     * @param toSwap
     */
    void swap(ForwardList& toSwap) noexcept
    {
        std::swap(this->_head, toSwap._head);
    }

private:
    iterator insertAfterNode(iterator insertAfterIt, NodeT* nodeToInsert)
    {
        auto insertAfterItNode = insertAfterIt._get_node();
        nodeToInsert->_next = insertAfterItNode->_next;
        insertAfterItNode->_next = nodeToInsert;
        return iterator(nodeToInsert);
    }

private:
    BaseNodeT _head;
};

template<typename T, typename NodeAllocator = std::allocator<Node<T>>>
bool operator==(const ForwardList<T, NodeAllocator>& lhs, const ForwardList<T, NodeAllocator>& rhs)
{
    auto lhsIt = lhs.cbegin();
    auto rhsIt = rhs.cbegin();
    while (rhsIt != rhs.cend() && lhsIt != lhs.cend() && *lhsIt == *rhsIt) {
        ++lhsIt;
        ++rhsIt;
    }

    return rhsIt == rhs.cend() && lhsIt == lhs.cend();
}

} // namespace Structures::STL