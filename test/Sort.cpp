#include "Sort.h"

template<int No>
struct X
{
    constexpr static int val = No;
};

struct M {};
struct N : public M{};
struct O : public N{};
struct R : public O{};
struct P : public M{};

template<typename LT, typename RT> struct AscXBinaryPred  { constexpr static bool value = LT::val < RT::val; };
template<typename LT, typename RT> struct DescXBinaryPred { constexpr static bool value = LT::val > RT::val; };

template<typename LT, typename RT> struct IsDerivedFromBinaryPred { constexpr static bool value = std::is_base_of<LT, RT>::value; };
template<typename LT, typename RT> struct IsNotDerivedFromBinaryPred { constexpr static bool value = ! IsDerivedFromBinaryPred<LT, RT>::value; };

void TestSort()
{
	using namespace tpl;
	static_assert(std::is_same<typename Merge<Empty, Empty, AscXBinaryPred>::Result, Empty >::value, "");

	static_assert(std::is_same<typename Merge<Empty,
											  std::tuple<X<1>, X<4>, X<5>>,
											  AscXBinaryPred>::Result, std::tuple<X<1>, X<4>, X<5>> >::value, "");

	static_assert(std::is_same<typename Merge<std::tuple<X<1>, X<4>, X<5>>,
											  Empty,
											  AscXBinaryPred>::Result, std::tuple<X<1>, X<4>, X<5>> >::value, "");

	using AscSortedResult = std::tuple<X<1>, X<2>, X<3>, X<4>, X<5>, X<6>>;
	static_assert(std::is_same<typename Merge<std::tuple<X<2>, X<3>, X<6>>,
											  std::tuple<X<1>, X<4>, X<5>>,
											  AscXBinaryPred>::Result, AscSortedResult>::value, "");

	using DescSortedResult = std::tuple<X<6>, X<5>, X<4>, X<3>, X<2>, X<1>>;
	static_assert(std::is_same<typename Merge<std::tuple<X<4>, X<2>, X<1>>,
											  std::tuple<X<6>, X<5>, X<3>>,
											  DescXBinaryPred>::Result, DescSortedResult>::value, "");


	static_assert(std::is_same<typename Sort<Empty, AscXBinaryPred>::Result, Empty>::value, "");

	static_assert(std::is_same<typename Sort<std::tuple<X<1>>, AscXBinaryPred>::Result, std::tuple<X<1>>>::value, "");

	static_assert(std::is_same<typename Sort<std::tuple<X<1>, X<2>>, AscXBinaryPred>::Result, std::tuple<X<1>, X<2>>>::value, "");
	static_assert(std::is_same<typename Sort<std::tuple<X<2>, X<1>>, AscXBinaryPred>::Result, std::tuple<X<1>, X<2>>>::value, "");

	static_assert(std::is_same<typename Sort<std::tuple<X<1>, X<2>>, DescXBinaryPred>::Result, std::tuple<X<2>, X<1>>>::value, "");
	static_assert(std::is_same<typename Sort<std::tuple<X<2>, X<1>>, DescXBinaryPred>::Result, std::tuple<X<2>, X<1>>>::value, "");

	static_assert(std::is_same<typename Sort<std::tuple<X<4>, X<2>, X<1>, X<6>, X<5>, X<3>>, AscXBinaryPred>::Result,
											 std::tuple<X<1>, X<2>, X<3>, X<4>, X<5>, X<6>>>::value, "");

	static_assert(std::is_same<typename Sort<std::tuple<X<4>, X<2>, X<1>, X<6>, X<5>, X<3>>, DescXBinaryPred>::Result,
											 std::tuple<X<6>, X<5>, X<4>, X<3>, X<2>, X<1>>>::value, "");

	static_assert(std::is_same<typename Sort<std::tuple<M, N, O, P>, IsDerivedFromBinaryPred>::Result, std::tuple<M, P, N, O>>::value, "");
	static_assert(std::is_same<typename Sort<std::tuple<M, O, N, P>, IsDerivedFromBinaryPred>::Result, std::tuple<M, P, N, O>>::value, "");
	static_assert(std::is_same<typename Sort<std::tuple<M, N, O, P>, IsNotDerivedFromBinaryPred>::Result, std::tuple<O, N, P, M>>::value, "");
	static_assert(std::is_same<typename Sort<std::tuple<M, O, N, P>, IsNotDerivedFromBinaryPred>::Result, std::tuple<O, N, P, M>>::value, "");

	static_assert(std::is_same<typename Sort<std::tuple<M, N, O, P, R>, IsDerivedFromBinaryPred>::Result, std::tuple<M, N, O, R, P>>::value, "");
	static_assert(std::is_same<typename Sort<std::tuple<M, O, N, P, R>, IsDerivedFromBinaryPred>::Result, std::tuple<M, N, O, R, P>>::value, "");
}
