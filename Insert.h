#ifndef INSERT_H_20150419
#define INSERT_H_20150419

#include "Empty.h"
#include "Append.h"
#include "SplitAt.h"

#include <cstddef>
#include <type_traits>

namespace tpl 
{
	template<typename Tup, typename T, std::size_t I>
	struct Insert
	{
	private:
		constexpr static std::size_t sz = std::tuple_size<Tup>::value;

		using InternalSplit = SplitAt<Tup,I>;

		using Left  = typename std::conditional<I == 0,  T, typename InternalSplit::Left>::type;
		using Right = typename std::conditional<I == sz, T, typename InternalSplit::Right>::type;

		using LeftTemp = typename std::conditional
		<
			I == 0 || I == sz,
			Left,
			typename Append<Left, T>::result
		>::type;

		//static_assert(! std::is_same<T, Empty>::value, "Cannot use Empty class in this context");

	public:
		using result = typename Append<LeftTemp, Right>::result;
	};

	template<typename T>
	struct Insert<Empty, T, 0>
	{
		using result = typename Append<Empty, T>::result;
	};
}
#endif