#pragma once

#include "Empty.h"

#include <cstddef>
#include <type_traits>
#include <tuple>


template <typename Tup, template<typename T, std::size_t C> class BinaryPred, std::size_t N>
struct RemoveIfImpl
{
    using Tail = typename std::tuple_element<N, Tup>::type;
    using Head = typename RemoveIfImpl<Tup, BinaryPred, N-1>::Result;
    
    static_assert(! std::is_same<Tail, Empty>::value, "Cannot use Empty class in this context");
    
    using Result = typename std::conditional
    <
        BinaryPred<Tail,N>::value,
        Head,
        typename std::conditional
        <
            std::is_same<Head, std::tuple<Empty>>::value,  
            std::tuple<Tail>,
            typename Append<Head, Tail>::Result
        >::type
    >::type;
};

template <typename Tup, template<typename T, std::size_t C> class BinaryPred>
struct RemoveIfImpl<Tup, BinaryPred, 0>
{
    using Head = typename std::tuple_element<0, Tup>::type;
    
    static_assert(! std::is_same<Head, Empty>::value, "Cannot use Empty class in this context");
    
    using Result = typename std::conditional
    <
        BinaryPred<Head,0>::value,
        std::tuple<Empty>,
        std::tuple<Head>
    >::type;
};

template <typename Tup, template<typename T, std::size_t C> class BinaryPred>
struct RemoveIf
{
private:    
    using Temp = typename RemoveIfImpl<Tup, BinaryPred, std::tuple_size<Tup>::value-1>::Result;
public:    
    using Result = typename std::conditional
    <
        std::is_same<Temp, std::tuple<Empty>>::value,
        Empty,
        Temp
    >::type;
};

template <template<typename T, std::size_t C> class BinaryPred>
struct RemoveIf<Empty, BinaryPred>
{
    using Result = Empty;
};

///////
template<typename T, std::size_t C, std::size_t I> 
struct RemoveAtIndexPred
{
    constexpr static bool value = (I == C);
};

template <typename Tup, std::size_t I>
struct RemoveAtIndex
{
    template<typename CurT, std::size_t C> using RemoveAtIndexPredInternal = RemoveAtIndexPred<CurT, C, I>;
    using Result = typename RemoveIf<Tup, RemoveAtIndexPredInternal>::Result;
};

///////
template <typename Tup, typename T>
struct RemoveAll
{
    static_assert(! std::is_same<T, Empty>::value, "Cannot use Empty class in this context");
    
    template<typename CurT, std::size_t C> using Pred = std::is_same<CurT,T>;
    using Result = typename RemoveIf<Tup, Pred>::Result;
};