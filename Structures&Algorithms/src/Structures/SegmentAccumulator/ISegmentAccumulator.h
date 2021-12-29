#pragma once
#include <functional>

template<
    typename ValueType,
    typename AccumulateFunction = std::function<ValueType(const ValueType&, const ValueType&)>>
class ISegmentAccumulator {
public:
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
    virtual ValueType get(const int& l, const int& r) const = 0;

    /**
     * @brief Change element by newValue
     *
     * @param index number of value to change
     * @param newValue new value
     */
    virtual void update(const int& index, const ValueType& newValue) = 0;

    /**
     * @brief Returns True if segment accumulator was initialized
     */
    virtual bool isBuilt() const = 0;
};