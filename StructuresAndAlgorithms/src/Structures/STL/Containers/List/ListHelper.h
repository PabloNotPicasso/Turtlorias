#pragma once

#include "Logger/LoggerApi.h"
#include "Node.h"

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <utility>

namespace Structures::STL {

template<typename T, typename Allocator = std::allocator<ListNode<T>>>
class ListHelper {
public:
    using value_type = T;
    using size_type = size_t;

    using BaseNode = BaseListNode<T>;
    using Node = ListNode<T>;

protected:
    static Node* allocateNode()
    {
        Allocator allocator;
        return allocator.allocate(1);
    }
    static void deallocateNode(Node* toDeallocate)
    {
        Allocator allocator;
        allocator.deallocate(toDeallocate, 1);
    }
    static void deallocateNode(BaseNode* toDeallocate)
    {
        Allocator allocator;
        allocator.deallocate(static_cast<Node*>(toDeallocate), 1);
    }

    template<typename... Args>
    static Node* createNode(Args... args)
    {
        auto node = allocateNode();

        // TODO: try catch
        Allocator allocator;
        allocator.construct(node, std::forward<Args>(args)...);

        return node;
    }

    static Node* createNode(const T& toCopy)
    {
        auto node = allocateNode();

        // TODO: try catch
        Allocator allocator;
        allocator.construct(node, toCopy);

        return node;
    }

    static Node* createNode(T&& toMove)
    {
        auto node = allocateNode();

        // TODO: try catch
        Allocator allocator;
        allocator.construct(node, std::move(toMove));

        return node;
    }

    static void deleteNode(Node* toDestroy)
    {
        Allocator allocator;
        allocator.destroy(toDestroy);

        deallocateNode(toDestroy);
    }
    static void deleteNode(BaseNode* toDestroy)
    {
        Allocator allocator;
        allocator.destroy(static_cast<Node*>(toDestroy));

        deallocateNode(toDestroy);
    }
};

} // namespace Structures::STL
