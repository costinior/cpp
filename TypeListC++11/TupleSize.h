#ifndef TUPLESIZE_H_20150419
#define TUPLESIZE_H_20150419

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

#endif