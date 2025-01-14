#pragma once

#include <cstddef>

namespace Structures::STL {

template<typename Head, typename... Args>
struct Tuple : Tuple<Args...> {
    Head value;
};

template<typename Head>
struct Tuple<Head> {
    Head value;
};

// TupleComparator
template<typename... Tail>
struct TupleComparator;

template<typename Head, typename... Tail>
struct TupleComparator<Head, Tail...> {
    constexpr static bool areEqual(const Tuple<Head, Tail...>& t1, const Tuple<Head, Tail...>& t2)
    {
        return t1.value == t2.value && TupleComparator<Tail...>::areEqual(t1, t2);
    }
    constexpr static bool less(const Tuple<Head, Tail...>& t1, const Tuple<Head, Tail...>& t2)
    {
        return t1.value < t2.value
            || (t1.value == t2.value && TupleComparator<Tail...>::less(t1, t2));
    }
};

template<typename Head>
struct TupleComparator<Head> {
    constexpr static bool areEqual(const Tuple<Head>& t1, const Tuple<Head>& t2)
    {
        return t1.value == t2.value;
    }

    constexpr static bool less(const Tuple<Head>& t1, const Tuple<Head>& t2)
    {
        return t1.value < t2.value;
    }
};

template<typename... Args>
bool operator==(const Tuple<Args...>& t1, const Tuple<Args...>& t2)
{
    return TupleComparator<Args...>::areEqual(t1, t2);
}
template<typename... Args>
bool operator!=(const Tuple<Args...>& t1, const Tuple<Args...>& t2)
{
    return !TupleComparator<Args...>::areEqual(t1, t2);
}
template<typename... Args>
bool operator<(const Tuple<Args...>& t1, const Tuple<Args...>& t2)
{
    return TupleComparator<Args...>::less(t1, t2);
}

// TupleElement
template<int I, typename... Types>
struct TupleElement;

template<typename Head, typename... Tail>
struct TupleElement<0, Head, Tail...> {
    typedef Head type;
};

template<int I, typename Head, typename... Tail>
struct TupleElement<I, Head, Tail...> {
    static_assert(I > 0, "Index out of bounds");
    using type = typename TupleElement<I - 1, Tail...>::type;
};

// TupleElementGetter
template<int I, typename Head, typename... Tail>
struct TupleElementGetter {
    static typename TupleElement<I, Head, Tail...>::type& get(Tuple<Head, Tail...>& tuple)
    {
        static_assert(I > 0, "Index out of bounds");
        return TupleElementGetter<I - 1, Tail...>::get(tuple);
    }
};

template<typename Head, typename... Tail>
struct TupleElementGetter<0, Head, Tail...> {
    static typename TupleElement<0, Head, Tail...>::type& get(Tuple<Head, Tail...>& tuple)
    {
        return tuple.value;
    }
};

// get function
template<int I, typename... Args>
typename TupleElement<I, Args...>::type& get(Tuple<Args...>& tuple)
{
    static_assert(I < sizeof...(Args), "Index out of bounds");
    return TupleElementGetter<I, Args...>::get(tuple);
}

} // namespace Structures::STL