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
	static_assert(std::is_same<Merge<Empty, Empty, AscXBinaryPred>::result, Empty >::value, "");

	static_assert(std::is_same<Merge<Empty,
									 std::tuple<X<1>, X<4>, X<5>>,
									 AscXBinaryPred>::result, std::tuple<X<1>, X<4>, X<5>> >::value, "");

	static_assert(std::is_same<Merge<std::tuple<X<1>, X<4>, X<5>>,
									 Empty,
									 AscXBinaryPred>::result, std::tuple<X<1>, X<4>, X<5>> >::value, "");

	using AscSortedResult = std::tuple<X<1>, X<2>, X<3>, X<4>, X<5>, X<6>>;
	static_assert(std::is_same<Merge<std::tuple<X<2>, X<3>, X<6>>,
									 std::tuple<X<1>, X<4>, X<5>>,
								     AscXBinaryPred>::result, AscSortedResult>::value, "");

	using DescSortedResult = std::tuple<X<6>, X<5>, X<4>, X<3>, X<2>, X<1>>;
	static_assert(std::is_same<Merge<std::tuple<X<4>, X<2>, X<1>>,
									 std::tuple<X<6>, X<5>, X<3>>,
									 DescXBinaryPred>::result, DescSortedResult>::value, "");


	static_assert(std::is_same<Sort<Empty, AscXBinaryPred>::result, Empty>::value, "");

	static_assert(std::is_same<Sort<std::tuple<X<1>>, AscXBinaryPred>::result, std::tuple<X<1>>>::value, "");

	static_assert(std::is_same<Sort<std::tuple<X<1>, X<2>>, AscXBinaryPred>::result, std::tuple<X<1>, X<2>>>::value, "");
	static_assert(std::is_same<Sort<std::tuple<X<2>, X<1>>, AscXBinaryPred>::result, std::tuple<X<1>, X<2>>>::value, "");

	static_assert(std::is_same<Sort<std::tuple<X<1>, X<2>>, DescXBinaryPred>::result, std::tuple<X<2>, X<1>>>::value, "");
	static_assert(std::is_same<Sort<std::tuple<X<2>, X<1>>, DescXBinaryPred>::result, std::tuple<X<2>, X<1>>>::value, "");

	static_assert(std::is_same<Sort<std::tuple<X<4>, X<2>, X<1>, X<6>, X<5>, X<3>>, AscXBinaryPred>::result,
									std::tuple<X<1>, X<2>, X<3>, X<4>, X<5>, X<6>>>::value, "");

	static_assert(std::is_same<Sort<std::tuple<X<4>, X<2>, X<1>, X<6>, X<5>, X<3>>, DescXBinaryPred>::result,
									std::tuple<X<6>, X<5>, X<4>, X<3>, X<2>, X<1>>>::value, "");

	static_assert(std::is_same<Sort<std::tuple<M, N, O, P>, IsDerivedFromBinaryPred>::result, std::tuple<M, P, N, O>>::value, "");
	static_assert(std::is_same<Sort<std::tuple<M, O, N, P>, IsDerivedFromBinaryPred>::result, std::tuple<M, P, N, O>>::value, "");
	static_assert(std::is_same<Sort<std::tuple<M, N, O, P>, IsNotDerivedFromBinaryPred>::result, std::tuple<O, N, P, M>>::value, "");
	static_assert(std::is_same<Sort<std::tuple<M, O, N, P>, IsNotDerivedFromBinaryPred>::result, std::tuple<O, N, P, M>>::value, "");

	static_assert(std::is_same<Sort<std::tuple<M, N, O, P, R>, IsDerivedFromBinaryPred>::result, std::tuple<M, N, O, R, P>>::value, "");
	static_assert(std::is_same<Sort<std::tuple<M, O, N, P, R>, IsDerivedFromBinaryPred>::result, std::tuple<M, N, O, R, P>>::value, "");
}
