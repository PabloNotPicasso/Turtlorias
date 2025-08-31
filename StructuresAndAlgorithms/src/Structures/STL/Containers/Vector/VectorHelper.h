#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <utility>

namespace Structures::STL {

template<typename T, typename Allocator = std::allocator<T>>
class VectorHelper {
public:
    using value_type = T;
    using size_type = size_t;

public:
    /**
     * @brief Create a raw unintitialized array of \p size elements
     *
     * @param size
     * @return T*
     */
    [[nodiscard]] static T* createArray(size_t size)
    {
        Allocator allocator;
        return allocator.allocate(size);
    }

    /**
     * @brief Free allocated raw \p array without calling destructors
     *
     * @param array
     */
    static void freeRawArray(T* array, size_type capacity)
    {
        Allocator allocator;
        allocator.deallocate(array, capacity);
    }

    static void destroyElement(T* toDestroyPtr)
    {
        Allocator allocator;
        allocator.destroy(toDestroyPtr);
    }
    /**
     * @brief Call destructors for first \b size elements of \b array
     *
     * @param array
     * @param size
     */
    static void destroyElements(T* begin, T* end)
    {
        Allocator allocator;
        for (auto toDestroyPtr = begin; toDestroyPtr != end; ++toDestroyPtr) {
            allocator.destroy(toDestroyPtr);
        }
    }

    template<typename... Args>
    static void constructElement(T* toCreatePtr, Args&&... args)
    {
        Allocator allocator;
        allocator.construct(toCreatePtr, std::forward<Args>(args)...);
    }
    /**
     * @brief Fill \b array with \b size elements equal to \b defaultValue
     *
     * @param array
     * @param size
     * @param defaultValue
     */
    static void constructArray(T* begin, T* end)
    {
        Allocator allocator;
        auto toCreatePtr = begin;
        try {
            for (; toCreatePtr != end; ++toCreatePtr) {
                allocator.construct(toCreatePtr);
            }
        } catch (...) {
            destroyElements(begin, toCreatePtr);
            throw;
        }
    }
    static void constructArray(T* begin, T* end, const value_type& defaultValue)
    {
        Allocator allocator;
        auto toCreatePtr = begin;
        try {
            for (; toCreatePtr != end; ++toCreatePtr) {
                allocator.construct(toCreatePtr, defaultValue);
            }
        } catch (...) {
            destroyElements(begin, toCreatePtr);
            throw;
        }
    }

    /**
     * @brief Free allocated \p array after calling destructors for first \p size elements
     *
     * @param array
     * @param capacity
     * @param size
     */
    static void deleteAndFree(T* array, size_type capacity, size_type size)
    {
        destroyElements(array, array + size);
        freeRawArray(array, capacity);
    }

    /**
     * @brief Call copy constructor for first \b size elements to copy from \b sourceArray to \b
     * targetArray
     *
     * @param targetArray
     * @param sourceArray
     * @param size
     */
    static void copyConstructElements(T* targetArray, const T* sourceArray, size_type size)
    {
        Allocator allocator;
        size_type idxToCopyConstruct = 0;
        try {
            for (; idxToCopyConstruct < size; ++idxToCopyConstruct) {
                allocator.construct(
                    targetArray + idxToCopyConstruct, sourceArray[idxToCopyConstruct]);
            }
        } catch (...) {
            destroyElements(targetArray, targetArray + idxToCopyConstruct);
            throw;
        }
    }

    /**
     * @brief Create copy of \p array which contains \p extendedCapacity elements
     * First \p currentSize elements will be copied from \p array
     * Other memory - uninitialized
     *
     * Is exception safe - all allocated data will be deallocated
     *
     * @param array
     * @param currentSize
     * @param extendedCapacity
     * @return T*
     */
    [[nodiscard]] static T* makeExtendedCopy(
        T* array, size_type currentSize, size_type extendedCapacity)
    {
        T* newArr = createArray(extendedCapacity);
        try {
            copyConstructElements(newArr, array, currentSize);
        } catch (...) {
            freeRawArray(newArr, extendedCapacity);
            throw;
        }
        return newArr;
    }
};

} // namespace Structures::STL
