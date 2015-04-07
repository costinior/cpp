#pragma once

#include "Empty.h"
#include "Misc.h"

#include <tuple>


template <typename T1, typename T2>
struct Append
{
private:    
    template<typename T> using MakeTup = std::conditional<is_instantiation_of<std::tuple, T>::value, T, std::tuple<T>>;
    using Tup1 = typename MakeTup<T1>::type;
    using Tup2 = typename MakeTup<T2>::type;
                                               
public:                                               
    using Result = typename std::__tuple_cat_result<Tup1, Tup2>::__type;
    //using Result = decltype(std::tie(std::declval<Tup1>(), std::declval<Tup2>()));
};

template <typename... Args> struct Append<Empty, std::tuple<Args...>> { using Result = std::tuple<Args...>; };
template <typename... Args> struct Append<std::tuple<Args...>, Empty> { using Result = std::tuple<Args...>; };

template <typename T> struct Append<Empty, T> { using Result = std::tuple<T>; };
template <typename T> struct Append<T, Empty> { using Result = std::tuple<T>; };

template <> struct Append<Empty, Empty> { using Result = Empty; };