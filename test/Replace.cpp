#include "Replace.h"

#include <tuple>

void TestReplace()
{
	using namespace tpl;
    using Tup = std::tuple<int, float, double*, unsigned int, void*>;

	//
    static_assert(std::is_same<Empty, ReplaceAll<Empty, float, int>::result>::value, "");

    using Tuple_1 = ReplaceAll<Tup, float, int>::result;
    static_assert(std::is_same<Tuple_1, std::tuple<int, int, double*, unsigned int,void*>>::value, "");

    using Tuple_2 = ReplaceAll<Tuple_1, double*, int>::result;
    static_assert(std::is_same<Tuple_2, std::tuple<int, int, int, unsigned int,void*>>::value, "");

    using Tuple_3 = ReplaceAll<Tuple_2, int, const int*>::result;
    static_assert(std::is_same<Tuple_3, std::tuple<const int*, const int*, const int*, unsigned int,void*>>::value, "");

    using Tuple_4 = ReplaceAtIndex<Tuple_3, 2, long long const>::result;
    static_assert(std::is_same<Tuple_4, std::tuple<const int*, const int*, long long const, unsigned int,void*>>::value, "");
}
