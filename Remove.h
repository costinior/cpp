#ifndef REMOVE_H_20150419
#define REMOVE_H_20150419

#include "Empty.h"
#include "Append.h"

#include <cstddef>
#include <type_traits>
#include <tuple>

namespace tpl 
{
	template <typename Tup, template<typename T, std::size_t C> class BinaryPred, std::size_t N>
	struct RemoveIfImpl
	{
		using Tail = typename std::tuple_element<N, Tup>::type;
		using Head = typename RemoveIfImpl<Tup, BinaryPred, N-1>::result;

		static_assert(! std::is_same<Tail, Empty>::value, "Cannot use Empty class in this context");

		using result = typename std::conditional
		<
			BinaryPred<Tail,N>::value,
			Head,
			typename std::conditional
			<
				std::is_same<Head, std::tuple<Empty>>::value,
				std::tuple<Tail>,
				typename Append<Head, Tail>::result
			>::type
		>::type;
	};

	template <typename Tup, template<typename T, std::size_t C> class BinaryPred>
	struct RemoveIfImpl<Tup, BinaryPred, 0>
	{
		using Head = typename std::tuple_element<0, Tup>::type;

		static_assert(! std::is_same<Head, Empty>::value, "Cannot use Empty class in this context");

		using result = typename std::conditional
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
		using Temp = typename RemoveIfImpl<Tup, BinaryPred, std::tuple_size<Tup>::value-1>::result;
	public:
		using result = typename std::conditional
		<
			std::is_same<Temp, std::tuple<Empty>>::value,
			Empty,
			Temp
		>::type;
	};

	template <template<typename T, std::size_t C> class BinaryPred>
	struct RemoveIf<Empty, BinaryPred>
	{
		using result = Empty;
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
		using result = typename RemoveIf<Tup, RemoveAtIndexPredInternal>::result;
	};

	///////
	template <typename Tup, typename T>
	struct RemoveAll
	{
		static_assert(! std::is_same<T, Empty>::value, "Cannot use Empty class in this context");

		template<typename CurT, std::size_t C> using Pred = std::is_same<CurT,T>;
		using result = typename RemoveIf<Tup, Pred>::result;
	};
}
#endif