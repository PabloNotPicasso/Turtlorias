#pragma once

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <utility>

namespace Structures::STL {

template<
    typename T,
    size_t BlockSize,
    typename Allocator = std::allocator<T>,
    typename AllocatorPtr = std::allocator<T*>>
class DequeHelper {
public:
    using value_type = T;
    using size_type = size_t;

public:
    /**
     * @brief Create a raw unintitialized block array of \p size elements
     *
     * @param size
     * @return T**
     */
    [[nodiscard]] static T** createBlocksArray(size_t size)
    {
        auto blocks = createBlocksPointersArray(size);
        for (size_t i = 0; i != size; ++i) {
            blocks[i] = createBlock();
        }
        return blocks;
    }

    static void freeBlocksArray(T** blocks, size_t size)
    {
        for (size_t i = 0; i != size; ++i) {
            freeBlock(blocks[i]);
        }
        freeBlocksPointersArray(blocks, size);
    }

    /**
     * @brief Create a raw unintitialized block array of \p size elements
     *
     * @param size
     * @return T**
     */
    [[nodiscard]] static T** createBlocksPointersArray(size_t size)
    {
        AllocatorPtr allocator;
        return allocator.allocate(size);
    }

    static void freeBlocksPointersArray(T** _blocks, size_t _size)
    {
        AllocatorPtr allocator;
        allocator.deallocate(_blocks, _size);
    }

    /**
     * @brief Create a raw unintitialized fixed-size array for block
     *
     * @return T*
     */
    [[nodiscard]] static T* createBlock()
    {
        Allocator allocator;
        return allocator.allocate(BlockSize);
    }

    static void freeBlock(T* block)
    {
        Allocator allocator;
        return allocator.deallocate(block, BlockSize);
    }

    template<typename... Args>
    static void constructElement(T* toCreatePtr, Args&&... args)
    {
        Allocator allocator;
        allocator.construct(toCreatePtr, std::forward<Args>(args)...);
    }

    static void destroyElement(T* toDestroyPtr)
    {
        Allocator allocator;
        allocator.destroy(toDestroyPtr);
    }

    static void destroyAll(
        T** const source, size_t size, size_t beginIdx, size_t endIdx, size_t beginOffset)
    {
        size_t elementIdx = 0;
        size_t elementIdxInsideBlock = beginOffset;
        for (size_t blockIdx = beginIdx; blockIdx <= endIdx; ++blockIdx) {
            for (; elementIdxInsideBlock != BlockSize && elementIdx != size;
                 ++elementIdxInsideBlock, ++elementIdx) {
                destroyElement(source[blockIdx] + elementIdxInsideBlock);
            }
            elementIdxInsideBlock = 0;
        }
    }

    /**
     * @brief Create a copy of block array of \b source blocks array
     *
     * @param source
     * @param size
     * @param beginIdx
     * @param endIdx
     * @param beginOffset
     * @return T**
     */
    [[nodiscard]] static T** copyBlocksArray(
        const T** const source, size_t size, size_t beginIdx, size_t endIdx, size_t beginOffset)
    {
        assert(beginOffset < BlockSize);
        T** blocks = createBlocksArray(size);

        size_t elementIdx = 0;
        size_t elementIdxInsideBlock = beginOffset;
        for (size_t blockIdx = beginIdx; blockIdx <= endIdx; ++blockIdx) {
            for (; elementIdxInsideBlock != BlockSize && elementIdx != size;
                 ++elementIdxInsideBlock, ++elementIdx) {
                constructElement(
                    blocks[blockIdx] + elementIdxInsideBlock,
                    source[blockIdx][elementIdxInsideBlock]);
            }
            elementIdxInsideBlock = 0;
        }

        return blocks;
    }

    static void moveToBlocksPointersArray(
        T** source, size_type sourceBegin, size_type sourceEnd, T** target, size_type moveOffset)
    {
        for (size_type sourceBlockIdx = sourceBegin; sourceBlockIdx <= sourceEnd;
             ++sourceBlockIdx) {
            target[sourceBlockIdx + moveOffset] = source[sourceBlockIdx];
        }
    };

    /**
     * @brief Call destructors for all elements from \b source
     *
     * @param source
     * @param size
     * @param beginIdx
     * @param endIdx
     * @param beginOffset
     * @return T**
     */
    static void destroyElements(
        T** source, size_t size, size_t beginIdx, size_t endIdx, size_t beginOffset)
    {
        size_t elementIdx = 0;
        size_t elementIdxInsideBlock = beginOffset;
        for (size_t blockIdx = beginIdx; blockIdx <= endIdx; ++blockIdx) {
            for (; elementIdxInsideBlock != BlockSize && elementIdx != size;
                 ++elementIdxInsideBlock, ++elementIdx) {
                destroyElement(source[blockIdx] + elementIdxInsideBlock);
            }
            elementIdxInsideBlock = 0;
        }
    }
};

} // namespace Structures::STL