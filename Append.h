#ifndef APPEND_H_20150419
#define APPEND_H_20150419

#include "Empty.h"
#include "Misc.h"

#include <tuple>

namespace tpl 
{
	template <typename T1, typename T2>
	struct Append
	{
	private:
		template<typename T> using MakeTup = std::conditional<is_instantiation_of<std::tuple, T>::value, T, std::tuple<T>>;
		using Tup1 = typename MakeTup<T1>::type;
		using Tup2 = typename MakeTup<T2>::type;

	public:
		//TODO: make this code portable

	#if defined(__GNUC__) || defined(__GNUG__)
		using result = typename std::__tuple_cat_result<Tup1, Tup2>::__type;
	#elif defined(_MSC_VER)
		using result = typename std::_Tuple_cat1<Tup1, Tup2>::type;
	#endif
	};

	template <typename... Args> struct Append<Empty, std::tuple<Args...>> { using result = std::tuple<Args...>; };
	template <typename... Args> struct Append<std::tuple<Args...>, Empty> { using result = std::tuple<Args...>; };

	template <typename T> struct Append<Empty, T> { using result = std::tuple<T>; };
	template <typename T> struct Append<T, Empty> { using result = std::tuple<T>; };

	template <> struct Append<Empty, Empty> { using result = Empty; };
}

#endif