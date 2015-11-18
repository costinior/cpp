#ifndef INDEXOF_H_20150419
#define INDEXOF_H_20150419

#include "Empty.h"
#include "TupleSize.h"

#include <tuple>
#include <type_traits>

namespace tpl
{
	template<typename Tup, typename T, typename CurType, int I>
	struct IndexOfImpl
	{
		using Head = typename std::tuple_element<I-1, Tup>::type;
		
		static_assert(!std::is_same<CurType, Empty>::value, "Cannot use Empty class in this context");

		constexpr static int value = std::is_same<T, CurType>::value ? I :
																	   IndexOfImpl<Tup, T, Head, I-1>::value;
	};

	template<typename Tup, typename T, typename CurType>
	struct IndexOfImpl<Tup, T, CurType, 0>
	{
		constexpr static int value = std::is_same<T, CurType>::value ? 0 : -1;
	};

	template<typename Tup, typename T>
	struct IndexOf
	{
	private:
		constexpr static int sz = TupleSize<Tup>::value;

		using Head = typename std::tuple_element<sz-1, Tup>::type;

		static_assert(! std::is_same<T, Empty>::value, "Cannot use Empty class in this context");

	public:
		constexpr static int value = IndexOfImpl<Tup, T, Head, sz-1>::value;
	};

	template<typename T>
	struct IndexOf<Empty, T>
	{
		static_assert(!std::is_same<T, Empty>::value, "Cannot use Empty class in this context");
		constexpr static int value = -1;
	};
}
#endif