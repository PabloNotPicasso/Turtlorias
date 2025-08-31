#pragma once

#include "ListHelper.h"
#include "Logger/LoggerApi.h"
#include "Node.h"
#include "iterator/ListIterator.h"

namespace Structures::STL {

template<typename T, typename NodeAllocator = std::allocator<ListNode<T>>>
class List : public ListHelper<T, NodeAllocator> {
public:
    using Helper = ListHelper<T, NodeAllocator>;

    using BaseNode = BaseListNode<T>;
    using Node = ListNode<T>;

    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = size_t;

    using iterator = ListIterator<T, BaseNode, Node>;
    using const_iterator = ListIterator<const T, BaseNode, Node>;

public:
    List()
        : _size(0)
    {
        _head._next = &_head;
        _head._previous = &_head;
    }

    explicit List(size_type count)
        : List()
    {
        for (size_type i = 0; i != count; ++i) {
            emplace_back();
        }
    }

    List(size_type count, const value_type& value)
        : List()
    {
        for (size_type i = 0; i != count; ++i) {
            push_back(value);
        }
    }

    List(const List& toCopy)
        : List()
    {
        for (auto& listItem : toCopy) {
            push_back(listItem);
        }
    }

    List(List&& toMove)
        : List()
    {
        std::swap(_head, toMove._head);
        std::swap(_size, toMove._size);
    }

    explicit List(std::initializer_list<T> iList)
        : List()
    {
        for (auto& listItem : iList) {
            push_back(listItem);
        }
    }

    List& operator=(const List& toCopy)
    {
        List copy(toCopy);
        swap(copy);
        return *this;
    }

    List& operator=(List&& toMove)
    {
        swap(toMove);
        return *this;
    }

    List& operator=(std::initializer_list<T> iList)
    {
        List toCopy(iList);
        swap(toCopy);
        return *this;
    }

    ~List()
    {
        clear();
    }

    void push_back(const value_type& value)
    {
        auto node = Helper::createNode(value);
        insertNode(end(), node);
    }

    void push_back(value_type&& value)
    {
        auto node = Helper::createNode(std::move(value));
        insertNode(end(), node);
    }

    template<typename... Args>
    void emplace_back(Args&&... args)
    {
        auto node = Helper::createNode(std::forward<Args>(args)...);
        insertNode(end(), node);
    }

    void insert(const iterator toInsert, const value_type& valueToInsert)
    {
        auto node = Helper::createNode(valueToInsert);
        insertNode(toInsert, node);
    }

    void pop_back()
    {
        auto toDelete = _head->_previous;

        toDelete->_previous->_next = toDelete->_next;
        toDelete->_next->_previous = toDelete->_previous;

        Helper::deleteNode(toDelete);
        --_size;
    }

    bool empty() const noexcept
    {
        return _size == 0;
    }

    size_type size() const noexcept
    {
        return _size;
    }

    /**
     * @brief All elements will be destructed. Allocated data will be released
     */
    void clear()
    {
        for (auto toDelete = _head._next; toDelete != &_head;) {
            auto next = toDelete->_next;
            Helper::deleteNode(toDelete);
            toDelete = next;
        }
        _size = 0;
        _head._next = &_head;
        _head._previous = &_head;
    }

    T& back()
    {
        return static_cast<Node*>(_head._previous)->_value;
    }

    const T& back() const
    {
        return static_cast<Node*>(_head._previous)->_value;
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
        return iterator(&_head);
    }
    const_iterator end() const
    {
        return const_iterator(const_cast<BaseNode*>(&_head));
    }
    const_iterator cend() const
    {
        return const_iterator(const_cast<BaseNode*>(&_head));
    }

    /**
     * @brief Swap all data members to \p toSwap
     *
     * @param toSwap
     */
    void swap(List& toSwap) noexcept
    {
        std::swap(this->_head, toSwap._head);
        std::swap(this->_size, toSwap._size);
    }

private:
    void insertNode(iterator toInsert, BaseNode* node)
    {
        auto toInsertNode = toInsert._get_node();
        node->_previous = toInsertNode->_previous;
        node->_next = toInsertNode;
        // toInsert update
        toInsertNode->_previous = node;
        // previous element update
        node->_previous->_next = node;

        ++_size;
    }

private:
    size_type _size;
    BaseNode _head;
};

template<typename T>
bool operator==(const List<T>& lhs, const List<T>& rhs)
{
    if (lhs.size() != rhs.size()) {
        return false;
    }
    auto lhsIt = lhs.cbegin();
    auto rhsIt = rhs.cbegin();

    while (rhsIt != rhs.cend() && *lhsIt == *rhsIt) {
        ++lhsIt;
        ++rhsIt;
    }

    return rhsIt == rhs.cend();
}

} // namespace Structures::STL
