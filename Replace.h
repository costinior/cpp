#ifndef REPLACE_H_20150419
#define REPLACE_H_20150419

#include "Empty.h"
#include "Transform.h"

#include <cstddef>
#include <type_traits>
#include <tuple>

namespace tpl
{
	template<typename Tup, typename S, typename R>
	struct ReplaceAll
	{
	private:
		template<typename T, std::size_t C> using BinaryTrans = typename std::conditional<std::is_same<T, S>::value, R, T>;

		static_assert(! std::is_same<S, Empty>::value, "Cannot use Empty class in this context");
		static_assert(! std::is_same<R, Empty>::value, "Cannot use Empty class in this context");

	public:
		using result = typename Transform<Tup, BinaryTrans>::result;
	};



	template<typename Tup, std::size_t I, typename R>
	struct ReplaceAtIndex
	{
	private:
		template<typename T, std::size_t C> using BinaryTrans = typename std::conditional<I == C, R, T>;

		static_assert(I < std::tuple_size<Tup>::value, "Index out of range");
		static_assert(! std::is_same<R, Empty>::value, "Cannot use Empty class in this context");

	public:
		using result = typename Transform<Tup, BinaryTrans>::result;
	};
}
#endif