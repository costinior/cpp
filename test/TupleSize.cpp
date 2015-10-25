#include "TupleSize.h"

void TestTupleSize()
{
	using namespace tpl;
    static_assert(TupleSize<Empty>::value == 0, "");
    static_assert(TupleSize<std::tuple<char>>::value == 1, "");
    static_assert(TupleSize<std::tuple<char, char>>::value == 2, "");
}
