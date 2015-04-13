#pragma once

#include "Empty.h"
#include "Append.h"

#include <cstddef>
#include <type_traits>
#include <tuple>

template 
<
    typename Tuple, 
    template<typename T, std::size_t C> class Trans, 
    int N
> struct TransformImpl;

template<typename T>
struct IdentityTranformer
{
    using TransformedType = T;
};

template <typename Tup, template<typename T, std::size_t C> class BinaryTrans>
struct TransformImpl<Tup, BinaryTrans, 0>
{
    using Type   = typename std::tuple_element<0, Tup>::type;
    using Head   = typename BinaryTrans<Type,0>::type; 
    
    static_assert(! std::is_same<Type, Empty>::value, "Cannot use Empty class in this context");
    static_assert(! std::is_same<Head, Empty>::value, "Cannot use Empty class in this context");
    
    using Result = std::tuple<Head>;
};

template <typename Tup, template<typename T, std::size_t C> class BinaryTrans, int N>
struct TransformImpl
{
    using Type = typename std::tuple_element<N, Tup>::type;
    
    using Head = typename TransformImpl<Tup, BinaryTrans, N-1>::Result;
    using Tail = typename BinaryTrans<Type,N>::type; 
    
    static_assert(! std::is_same<Type, Empty>::value, "Cannot use Empty class in this context");
    static_assert(! std::is_same<Tail, Empty>::value, "Cannot use Empty class in this context");
    
    using Result = typename Append<Head, Tail>::Result;
};

template <typename Tup, template<typename T, std::size_t C> class BinaryTrans>
struct Transform
{
    using Result = typename TransformImpl<Tup, BinaryTrans, std::tuple_size<Tup>::value-1>::Result;
};

template <template<typename T, std::size_t C> class BinaryTrans>
struct Transform<Empty, BinaryTrans>
{
    using Result = Empty;
};
