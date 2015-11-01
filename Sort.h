#ifndef SORT_H_20150419
#define SORT_H_20150419

#include "Empty.h"
#include "SplitAt.h"
#include "Append.h"
#include "TupleSize.h"

#include <cstddef>
#include <type_traits>
#include <tuple>

namespace tpl 
{
	template <typename SortedLeftTup, typename SortedRightTup,
			  template<typename LT, typename RT> class BinaryPred,
			  std::size_t LeftTupSz, std::size_t RightTupSz >
	struct MergeImpl
	{
		using LeftInternalSplit  = SplitAt<SortedLeftTup, 1>;
		using RightInternalSplit = SplitAt<SortedRightTup, 1>;

		using LeftHead  = typename LeftInternalSplit::Left;
		using RightHead = typename RightInternalSplit::Left;

		constexpr static bool isLeftHeadLessThanRightHead = BinaryPred<typename std::tuple_element<0, LeftHead>::type,
																	   typename std::tuple_element<0, RightHead>::type>::value;

		using LeftTail  = typename std::conditional<  isLeftHeadLessThanRightHead, typename LeftInternalSplit::Right,  SortedLeftTup>::type;
		using RightTail = typename std::conditional<! isLeftHeadLessThanRightHead, typename RightInternalSplit::Right, SortedRightTup>::type;

		constexpr static std::size_t leftTailSz  = TupleSize<LeftTail>::value;
		constexpr static std::size_t rightTailSz = TupleSize<RightTail>::value;

		using PartialResult = typename std::conditional
		<
			 isLeftHeadLessThanRightHead,
			 LeftHead,
			 RightHead
		>::type;

		using Return = typename MergeImpl<LeftTail, RightTail, BinaryPred, leftTailSz, rightTailSz>::result;

		using result = typename Append
		<
			PartialResult,
			Return
		>::result;
	};

	template <typename SortedRightTup, template<typename LeftTupSz, typename RightTupSz> class BinaryPred, std::size_t RI>
	struct MergeImpl<Empty, SortedRightTup, BinaryPred, 0, RI>
	{
		using result = SortedRightTup;
	};

	template <typename SortedLeftTup, template<typename LeftTupSz, typename RightTupSz> class BinaryPred, std::size_t LI>
	struct MergeImpl<SortedLeftTup, Empty, BinaryPred, LI, 0>
	{
		using result = SortedLeftTup;
	};

	template < template<typename LeftTupSz, typename RightTupSz> class BinaryPred>
	struct MergeImpl<Empty, Empty, BinaryPred, 0, 0>
	{
		using result = Empty;
	};

	template <typename SortedLeftTup, typename SortedRightTup, template<typename LeftTupSz, typename RightTupSz> class BinaryPred>
	struct Merge
	{
		constexpr static std::size_t leftSz  = TupleSize<SortedLeftTup>::value;
		constexpr static std::size_t rightSz = TupleSize<SortedRightTup>::value;

		using result = typename MergeImpl<SortedLeftTup, SortedRightTup, BinaryPred, leftSz, rightSz>::result;
	};

	template <typename Tup, template<typename LT, typename RT> class BinaryPred, std::size_t TupSz>
	struct MergeSort
	{
		constexpr static std::size_t sz = std::tuple_size<Tup>::value;
		constexpr static std::size_t middle = sz/2;

		using InternalSplit = SplitAt<Tup, middle>;

		using Left  = typename InternalSplit::Left;
		using Right = typename InternalSplit::Right;

		constexpr static std::size_t leftSz  = std::tuple_size<Left>::value;
		constexpr static std::size_t rightSz = std::tuple_size<Right>::value;

		using SortedLeft  = typename MergeSort<Left,  BinaryPred, leftSz>::result;
		using SortedRight = typename MergeSort<Right, BinaryPred, rightSz>::result;

		using result = typename Merge<SortedLeft, SortedRight, BinaryPred>::result;
	};

	template <typename Tup, template<typename LT, typename RT> class BinaryPred>
	struct MergeSort<Tup, BinaryPred, 1>
	{
		using result = Tup;
	};

	template <template <typename LT, typename RT> class BinaryPred>
	struct MergeSort<Empty, BinaryPred, 0>
	{
		using result = Empty;
	};

	template <typename Tup, template<typename LT, typename RT> class BinaryPred>
	struct Sort
	{
		using result = typename MergeSort<Tup, BinaryPred, std::tuple_size<Tup>::value>::result;
	};

	template <template<typename LT, typename RT> class BinaryPred>
	struct Sort<Empty, BinaryPred>
	{
		using result = Empty;
	};
}
#endif