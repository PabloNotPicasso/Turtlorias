#pragma once

#include "Logger/LoggerApi.h"
#include "Node.h"

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <utility>

namespace Structures::STL {

template<typename T, typename Allocator = std::allocator<Node<T>>>
class ForwardListHelper {
public:
    using value_type = T;
    using size_type = size_t;

    using NodeT = Node<T>;

protected:
    static NodeT* allocateNode()
    {
        Allocator allocator;
        return allocator.allocate(1);
    }
    static void deallocateNode(NodeT* toDeallocate)
    {
        Allocator allocator;
        allocator.deallocate(toDeallocate, 1);
    }

    template<typename... Args>
    static NodeT* createNode(Args... args)
    {
        auto node = allocateNode();

        // TODO: try catch
        Allocator allocator;
        allocator.construct(node, std::forward<Args>(args)...);

        return node;
    }

    static NodeT* createNode(const T& toCopy)
    {
        auto node = allocateNode();

        // TODO: try catch
        Allocator allocator;
        allocator.construct(node, toCopy);

        return node;
    }

    static NodeT* createNode(T&& toMove)
    {
        auto node = allocateNode();

        // TODO: try catch
        Allocator allocator;
        allocator.construct(node, std::move(toMove));

        return node;
    }

    static void deleteNode(NodeT* toDestroy)
    {
        Allocator allocator;
        allocator.destroy(toDestroy);

        deallocateNode(toDestroy);
    }
};

} // namespace Structures::STL
