#include "IndexOf.h"

void TestIndexOf()
{
	using namespace tpl;
	using Tup = std::tuple<int, float, double*, unsigned int, void*>;;

	static_assert( IndexOf<Empty, int>::value == -1, "");
	static_assert( IndexOf<std::tuple<int>, int>::value == 0, "");

	static_assert( IndexOf<Tup, double*>::value == 2, "");
	static_assert( IndexOf<Tup, void*>::value == 4,   "");

	//static_assert( IndexOf<Tuple_0, A<void*>>::value == 4, "");
}
