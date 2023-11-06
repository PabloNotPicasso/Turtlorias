#pragma once

#include "DequeHelper.h"
#include "DequeSize.h"
#include "iterator/BaseRandomAccessIterator.h"

namespace Structures::STL {

template<typename T, typename Allocator = std::allocator<T>>
class Deque {
public:
    static constexpr size_t initialBlockCount = 3;
    static constexpr size_t initialBeginBlockIdx = initialBlockCount / 2;

    using Helper = DequeHelper<T, Allocator>;

    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = size_t;

    using iterator = BaseRandomAccessIterator<T>;
    using const_iterator = BaseRandomAccessIterator<const T>;

public:
    Deque()
        : _size(0)
        , _beginOffset(0)
        , _endOffset(0)
        , _beginBlockIdx(initialBeginBlockIdx)
        , _endBlockIdx(initialBeginBlockIdx)
        , _blocksCount(initialBlockCount)
    {
        _blocks = Helper::createBlocksArray(initialBlockCount);
    }

    explicit Deque(size_type count)
        : Deque()
    {
        for (size_type i = 0; i != count; ++i) {
            emplace_back();
        }
    }

    Deque(size_type count, const value_type& value)
        : Deque()
    {
        for (size_type i = 0; i != count; ++i) {
            emplace_back(value);
        }
    }

    Deque(const Deque& toCopy)
        : _size(toCopy._size)
        , _beginOffset(toCopy._beginOffset)
        , _endOffset(toCopy._endOffset)
        , _beginBlockIdx(toCopy._beginBlockIdx)
        , _endBlockIdx(toCopy._endBlockIdx)
        , _blocksCount(toCopy._blocksCount)
    {
        _blocks = Helper::copyBlocksArray(
            toCopy._blocks,
            toCopy._blocksCount,
            toCopy._beginBlockIdx,
            toCopy._endBlockIdx,
            toCopy._beginOffset);
    }

    Deque(Deque&& toMove)
    {
        _size = toMove._size;
        _beginOffset = toMove._beginOffset;
        _endOffset = toMove._endOffset;
        _beginBlockIdx = toMove._beginBlockIdx;
        _endBlockIdx = toMove._endBlockIdx;
        _blocksCount = toMove._blocksCount;
        _blocks = toMove._blocks;

        toMove._size = 0;
        toMove._beginOffset = 0;
        toMove._endOffset = 0;
        toMove._beginBlockIdx = 0;
        toMove._endBlockIdx = 0;
        toMove._blocksCount = 0;
        toMove._blocks = nullptr;
    }

    explicit Deque(std::initializer_list<T> iList)
        : Deque()
    {
        for (auto ilIt = iList; ilIt != iList.end(); ++ilIt) {
            push_back(*ilIt);
        }
    }

    Deque& operator=(const Deque& toCopy)
    {
        Deque copy(toCopy);
        swap(copy);
        return *this;
    }

    Deque& operator=(Deque&& toMove)
    {
        swap(toMove);
        return *this;
    }

    Deque& operator=(std::initializer_list<T> iList)
    {
        Deque toCopy(iList);
        swap(toCopy);
        return *this;
    }

    ~Deque()
    {
        Helper::destroyElements(_blocks, _size, _beginBlockIdx, _endBlockIdx, _beginOffset);
        Helper::freeBlocksPointersArray(_blocks, _size);
    }

    void push_back(const value_type& value)
    {
        emplace_back(value);
    }

    void push_back(value_type&& value)
    {
        emplace_back(std::move(value));
    }

    template<typename... Args>
    void emplace_back(Args&&... args)
    {
        useNextBlock();
        Helper::constructElement(_blocks[_endBlockIdx] + _endOffset, std::forward<Args>(args)...);
        ++_endOffset;
        if (_endOffset == DequeBlockSize) {
            _endOffset = 0;
            ++_endBlockIdx;
        }
        ++_size;
    }

    void pop_back()
    {
        if (empty()) {
            throw "pop_back on empty deque";
        }
        --_size;
        if (_endOffset == 0) {
            _endOffset = DequeBlockSize;
            --_endBlockIdx;
        }
        --_endOffset;
        Helper::destroyElement(_blocks[_endBlockIdx] + _endOffset);
    }

    void pop_front()
    {
        if (empty()) {
            throw "pop_back on empty deque";
        }
        --_size;

        Helper::destroyElement(_blocks[_beginBlockIdx] + _beginOffset);
        ++_beginOffset;
        if (_beginOffset == DequeBlockSize) {
            _beginOffset = 0;
            ++_beginBlockIdx;
        }
    }

    reference operator[](size_type idx)
    {
        auto absoluteIdx = _beginOffset + idx;
        return _blocks[_beginBlockIdx + absoluteIdx / DequeBlockSize][absoluteIdx % DequeBlockSize];
    }

    const_reference operator[](size_type idx) const
    {
        auto absoluteIdx = _beginOffset + idx;
        return _blocks[_beginBlockIdx + absoluteIdx / DequeBlockSize][absoluteIdx % DequeBlockSize];
    }

    reference at(size_type idx)
    {
        if (idx < _size) {
            return (*this)[idx];
        }
        throw "out_of_scope exception";
    }
    const_reference at(size_type idx) const
    {
        if (idx < _size) {
            return (*this)[idx];
        }
        throw "out_of_scope exception";
    }

    reference back()
    {
        return at(_size - 1);
    }
    const_reference back() const
    {
        return at(_size - 1);
    }

    reference front()
    {
        return at(0);
    }
    const_reference front() const
    {
        return at(0);
    }

    bool empty() const noexcept
    {
        return _size == 0;
    }

    size_type size() const noexcept
    {
        return _size;
    }

    iterator begin()
    {
        return iterator(_blocks + _beginBlockIdx, _beginOffset);
    }
    const_iterator begin() const
    {
        return const_iterator(_blocks + _beginBlockIdx, _beginOffset);
    }
    const_iterator cbegin() const
    {
        return const_iterator(_blocks + _beginBlockIdx, _beginOffset);
    }

    iterator end()
    {
        return iterator(_blocks + _endBlockIdx, _endOffset);
    }
    const_iterator end() const
    {
        return const_iterator(_blocks + _endBlockIdx, _endOffset);
    }
    const_iterator cend() const
    {
        return const_iterator(_blocks + _endBlockIdx, _endOffset);
    }

    /**
     * @brief Clears vector calling destructors for elements. Allocated data will not be released
     */
    void clear()
    {
        Helper::destroyAll(_blocks, _size, _beginBlockIdx, _endBlockIdx, _beginOffset);
        _size = 0;

        _beginOffset = 0;
        _endOffset = _beginOffset;

        _beginBlockIdx = _blocksCount / 2;
        _endBlockIdx = _beginBlockIdx;
    }

    /**
     * @brief Swap all data members to \p toSwap
     *
     * @param toSwap
     */
    void swap(Deque& toSwap) noexcept
    {
        std::swap(_size, toSwap._size);

        std::swap(_beginOffset, toSwap._beginOffset);
        std::swap(_endOffset, toSwap._endOffset);

        std::swap(_beginBlockIdx, toSwap._beginBlockIdx);
        std::swap(_endBlockIdx, toSwap._endBlockIdx);

        std::swap(_blocksCount, toSwap._blocksCount);
        std::swap(_blocks, toSwap._blocks);
    }

private:
    void useNextBlock()
    {
        // Check if reallocation is needed
        if (_endBlockIdx == _blocksCount) {
            constexpr size_type blocksToAdd = 4;
            constexpr size_type moveOffset = 0;
            size_type newBlocksCount = _blocksCount + blocksToAdd;

            auto newBlocks = Helper::createBlocksPointersArray(newBlocksCount);

            for (size_type beforeMainBlock = 0; beforeMainBlock != moveOffset; ++beforeMainBlock) {
                newBlocks[beforeMainBlock] = Helper::createBlock();
            }

            Helper::moveToBlocksPointersArray(
                _blocks, _beginBlockIdx, _endBlockIdx, newBlocks, moveOffset);
            for (size_type afterMainBlock = _endBlockIdx + moveOffset;
                 afterMainBlock != newBlocksCount;
                 ++afterMainBlock) {
                newBlocks[afterMainBlock] = Helper::createBlock();
            }

            Helper::freeBlocksPointersArray(_blocks, _blocksCount);

            _blocks = newBlocks;
            _blocksCount = newBlocksCount;
            _beginBlockIdx = _beginBlockIdx + moveOffset;
            _endBlockIdx = _endBlockIdx + moveOffset;
        }
    }

private:
    size_type _size;

    // _blocks[_beginBlockIdx][_beginOffset] - is valid if deque is not empty
    size_type _beginOffset;

    // _blocks[_endBlockIdx][_endOffset] - is not valid
    size_type _endOffset;

    size_type _beginBlockIdx; // begin is _blocks[_beginBlockIdx][_beginOffset]
    size_type _endBlockIdx; // end is _blocks[_endBlockIdx][_endBlockIdx]

    size_type _blocksCount;
    T** _blocks;
};
/*

[] - null
[] - null
       <- _beginOffset ->
[] -> [_,_,_,_,_,_,_,-1]
[] -> [0,1,2,3,4,5,6,7,8,9]
[] -> [10,11,_,_,_,_,_,_,_,_]
             <-_endOffset->
[] - null
[] - null

*/

} // namespace Structures::STL