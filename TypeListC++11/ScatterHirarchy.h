#ifndef SCATTERHIERARCHY_H
#define SCATTERHIERARCHY_H

#include "Empty.h"
#include "SplitAt.h"
#include "TupleSize.h"

template<typename Tup, template<typename> class Leaf, std::size_t TupSz>
class ScatterHierarchyImpl : public ScatterHierarchyImpl<typename SplitAt<Tup, 1>::Left, Leaf, 1>,
                             public ScatterHierarchyImpl<typename SplitAt<Tup, 1>::Right, Leaf, TupSz-1>
{};

template<typename Tup, template<typename> class Leaf>
class ScatterHierarchyImpl<Tup, Leaf, 1> : public Leaf<typename std::tuple_element<0,Tup>::type>
{};

template<template<typename> class Leaf>
class ScatterHierarchyImpl<Empty, Leaf, 0>
{};

template<typename Tup, template<typename> class Leaf>
class ScatterHierarchy : public ScatterHierarchyImpl<Tup, Leaf, TupleSize<Tup>::value>
{};

#endif