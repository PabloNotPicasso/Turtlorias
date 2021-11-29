#include <functional>

template<
    typename ValueType,
    typename AccumulateFunction = std::function<ValueType(const ValueType&, const ValueType&)>>
class ISegmentAccumulator {
public:
    virtual ~ISegmentAccumulator() = default;

    virtual void init(
        const std::vector<ValueType>& array,
        const AccumulateFunction& accumulateFunction,
        const ValueType& zerro)
        = 0;

    virtual ValueType get(const int& l, const int& r) const = 0;

    virtual void update(const int& index, const ValueType& newValue) = 0;

    virtual bool isBuilt() const = 0;
};