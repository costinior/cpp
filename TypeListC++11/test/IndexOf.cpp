#include "IndexOf.h"

void test()
{
	using Tup2 = std::tuple<int>;
	static_assert( IndexOf<Empty, int>::value == -1, "");
	static_assert( IndexOf<Tup2, int>::value == 0, "");
	static_assert( IndexOf<Tup, double*>::value == 2, "");
	static_assert( IndexOf<Tup, void*>::value == 4,   "");
	static_assert( IndexOf<Tuple_0, A<void*>>::value == 4, "");
}