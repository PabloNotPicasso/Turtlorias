#pragma once
#include <cstddef>
#include <functional>
#include <vector>

template<typename ValueType>
class ISegmentAccumulator {
public:
    using InternalValueType = ValueType;
    using AccumulateFunction = std::function<ValueType(const ValueType&, const ValueType&)>;

    virtual ~ISegmentAccumulator() = default;

    /**
     * @brief Initialize segment accumulator
     *
     * @param array - array for segmentation
     * @param accumulateFunction - accumulation function, should be associative!
     * @param zerro - zerro for function. It means accumulateFunction(a,zerro) = a
     */
    virtual void init(
        const std::vector<ValueType>& array,
        const AccumulateFunction& accumulateFunction,
        const ValueType& zerro)
        = 0;

    /**
     * @brief Returns accumulation value on a segment [l,r]
     *
     * @param l left border
     * @param r right border
     * @return resault of accumulation on a segment [l,r]. accumulateFunction(l,l+1,...,r)
     */
    virtual ValueType get(size_t l, size_t r) const = 0;

    /**
     * @brief Change element by newValue
     *
     * @param index number of value to change
     * @param newValue new value
     */
    virtual void update(size_t index, const ValueType& newValue) = 0;

    /**
     * @brief Returns True if segment accumulator was initialized
     */
    virtual bool isBuilt() const = 0;
};
