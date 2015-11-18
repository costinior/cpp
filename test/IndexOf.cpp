#include "IndexOf.h"

#include "Pack.h"

#define TEST_TYPE_IN(Tup, T, Index) \
	static_assert( tpl::IndexOf<Tup, T>::value == Index, "Expected type '"#T"' not found at index "#Index" in '"#Tup"'")

#define TEST_TYPE_NOT_IN(Tup, T) \
	static_assert( tpl::IndexOf<Tup, T>::value == -1, "Unexpected type '"#T"' found in '"#Tup"'")

void TestIndexOf()
{
	using namespace tpl;
	using Tup = std::tuple<int, float, double*, unsigned int, void*>;

	TEST_TYPE_NOT_IN(Empty, int);
	TEST_TYPE_IN(std::tuple<int>, int, 0);
	TEST_TYPE_IN(std::tuple<int>, int, 0);

	TEST_TYPE_IN(Tup, double*, 2);
	TEST_TYPE_IN(Tup, void*, 4);

	using TupPack = Pack<Tup>;
	TEST_TYPE_NOT_IN(Tup, Tup);
	TEST_TYPE_NOT_IN(Tup, TupPack);
	TEST_TYPE_NOT_IN(TupPack, TupPack);
	TEST_TYPE_IN(TupPack, Tup, 0);
	
	//next statements will result in a compile time error 
	//IndexOf<Empty, Empty>::value; 
	//IndexOf<Tup, Empty>::value;
	//IndexOf<std::tuple<int, float, Empty>, int>::value;
}
