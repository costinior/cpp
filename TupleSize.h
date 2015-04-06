#pragma once

#include "Empty.h"

#include <tuple>
#include <cstddef>

template<typename Tup>
struct TupleSize
{
    constexpr static std::size_t value = std::tuple_size<Tup>::value;
};

template<>
struct TupleSize<Empty>
{
    constexpr static std::size_t value = 0;
};