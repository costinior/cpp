#ifndef SPLITAT_H
#define SPLITAT_H

#include "Empty.h"
#include "Append.h"

#include <cstddef>
#include <tuple>
#include <type_traits>

template<typename Tup, std::size_t N, std::size_t Counter>
struct SplitAtImpl
{
    using Head = typename SplitAtImpl<Tup, N-1, Counter-1>::Result;
    using Tail = typename std::tuple_element<N, Tup>::type;

    static_assert(! std::is_same<Tail, Empty>::value, "Cannot use Empty class in this context");

    using Result = typename Append<Head, std::tuple<Tail>>::Result;
};

template<typename Tup, std::size_t N>
struct SplitAtImpl<Tup,N,0>
{
    using Head = typename std::tuple_element<N, Tup>::type;
    using Result = std::tuple<Head>;
};

template<typename Tup, std::size_t I>
struct SplitAt
{
private:
    constexpr static std::size_t sz = std::tuple_size<Tup>::value;
    static_assert(I <= sz, "Index out of range");

    constexpr static std::size_t leftCounter  = I == 0  ? 0 : I-1;
    constexpr static std::size_t rightCounter = I == sz ? 0 : sz-I-1;

public:
    using Left  = typename std::conditional
    <
        I == 0,
        Empty,
        typename SplitAtImpl<Tup, leftCounter, leftCounter>::Result
    >::type;

    using Right = typename std::conditional
    <
        I == sz,
        Empty,
        typename SplitAtImpl<Tup, sz-1, rightCounter>::Result
    >::type;
};

template<>
struct SplitAt<Empty,0>
{
    using Left  = Empty;
    using Right = Empty;
};

#endif