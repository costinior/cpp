#ifndef TRANSFORM_H_20150419
#define TRANSFORM_H_20150419

#include "Empty.h"
#include "Append.h"

#include <cstddef>
#include <type_traits>
#include <tuple>

namespace tpl
{
	template
	<
		typename Tuple,
		template<typename T, std::size_t C> class Trans,
		int N
	> struct TransformImpl;

	template<typename T>
	struct IdentityTranformer
	{
		using TransformedType = T;
	};

	template <typename Tup, template<typename T, std::size_t C> class BinaryTrans>
	struct TransformImpl<Tup, BinaryTrans, 0>
	{
		using Type   = typename std::tuple_element<0, Tup>::type;
		using Head   = typename BinaryTrans<Type, 0>::type;

		static_assert(! std::is_same<Type, Empty>::value, "Cannot use Empty class in this context");
		static_assert(! std::is_same<Head, Empty>::value, "Cannot use Empty class in this context");

		using result = std::tuple<Head>;
	};

	template <typename Tup, template<typename T, std::size_t C> class BinaryTrans, int N>
	struct TransformImpl
	{
		using Type = typename std::tuple_element<N, Tup>::type;

		using Head = typename TransformImpl<Tup, BinaryTrans, N-1>::result;
		using Tail = typename BinaryTrans<Type, N>::type;

		static_assert(! std::is_same<Type, Empty>::value, "Cannot use Empty class in this context");
		static_assert(! std::is_same<Tail, Empty>::value, "Cannot use Empty class in this context");

		using result = typename Append<Head, Tail>::result;
	};

	template <typename Tup, template<typename T, std::size_t C> class BinaryTrans>
	struct Transform
	{
		using result = typename TransformImpl<Tup, BinaryTrans, std::tuple_size<Tup>::value-1>::result;
	};

	template <template<typename T, std::size_t C> class BinaryTrans>
	struct Transform<Empty, BinaryTrans>
	{
		using result = Empty;
	};
}
#endif