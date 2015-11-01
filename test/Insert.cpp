#include "Insert.h"
#include "Pack.h"

#include "TestHelpers.h"

void TestInsert()
{
	using namespace tpl;
    using Tup = std::tuple<int,char, double, void*>;
	using Tup1 = std::tuple<int, char, void, double>;
	using Tup2 = std::tuple<A<int>, volatile char, const double* const>;

	static_assert(std::is_same<Insert<Empty, Empty, 0>::result, Empty>::value, "");
	static_assert(std::is_same<Insert<Empty, char, 0>::result, std::tuple<char>>::value, "");
	static_assert(std::is_same<Insert<Empty, Tup1, 0>::result, Tup1>::value, "");
	static_assert(std::is_same<Insert<Tup, Empty, 0>::result, Tup>::value, "");
	static_assert(std::is_same<Insert<Tup, Empty, 1>::result, Tup>::value, "");
	static_assert(std::is_same<Insert<Tup, Empty, 2>::result, Tup>::value, "");
	static_assert(std::is_same<Insert<Tup, Empty, 3>::result, Tup>::value, "");
	static_assert(std::is_same<Insert<Tup, Empty, 4>::result, Tup>::value, "");
	static_assert( std::is_same<Insert<Tup1, char, 0>::result,
								std::tuple<char, int, char, void, double>>::value, "");
	static_assert( std::is_same<Insert<Tup2, char, 0>::result,
								std::tuple<char, A<int>, volatile char, const double* const>>::value, "");
	static_assert( std::is_same<Insert<Tup1, Tup2, 0>::result,
								std::tuple<A<int>, volatile char, const double* const, int, char, void, double>>::value, "");
	static_assert( std::is_same< Insert<Tup1, Pack<Tup2>, 0>::result,
								std::tuple<std::tuple<A<int>, volatile char, const double* const>, int, char, void, double>>::value, "");

	static_assert( std::is_same<Insert<Tup1, char, 4>::result,
								std::tuple<int, char, void, double, char>>::value, "");
	static_assert( std::is_same<Insert<Tup2, char, 3>::result,
								std::tuple<A<int>, volatile char, const double* const, char>>::value, "");
	static_assert( std::is_same<Insert<Tup1, Tup2, 4>::result,
								std::tuple<int, char, void, double, A<int>, volatile char, const double* const>>::value, "");
	static_assert( std::is_same<Insert<Tup1, Pack<Tup2>, 4>::result,
								std::tuple<int, char, void, double, std::tuple<A<int>, volatile char, const double* const>>>::value, "");


	static_assert(std::is_same<Insert<Empty, char, 0>::result, std::tuple<char>>::value, "");
	static_assert(std::is_same<Insert<Empty, Pack<std::tuple<char>>, 0>::result, std::tuple<std::tuple<char>> >::value, "");


	static_assert(std::is_same<Insert<Tup, char, 0>::result, std::tuple<char, int,char, double, void*>>::value, "");
	static_assert(std::is_same<Insert<Tup, char, 1>::result, std::tuple<int, char, char, double, void*>>::value, "");
	static_assert(std::is_same<Insert<Tup, char, 2>::result, std::tuple<int, char, char, double, void*>>::value, "");
	static_assert(std::is_same<Insert<Tup, char, 3>::result, std::tuple<int, char, double, char, void*>>::value, "");
    static_assert(std::is_same<Insert<Tup, char, 4>::result, std::tuple<int, char, double, void*, char>>::value, "");

	static_assert(std::is_same<Insert<Tup, Tup, 4>::result, std::tuple<int,char, double, void*, int,char, double, void*>>::value, "");
	static_assert(std::is_same<Insert<Tup, Tup, 0>::result, std::tuple<int,char, double, void*, int,char, double, void*>>::value, "");
	static_assert(std::is_same<Insert<Tup, Tup, 1>::result, std::tuple<int, int,char, double, void*, char, double, void*>>::value, "");

	static_assert(std::is_same<Insert<Tup, Pack<Tup>, 0>::result, std::tuple<Tup, int, char, double, void*>>::value, "");
	static_assert(std::is_same<Insert<Tup, Pack<Tup>, 4>::result, std::tuple<int, char, double, void*, std::tuple<int,char, double, void*>>>::value, "");
    static_assert(std::is_same<Insert<Tup, Pack<Tup>, 1>::result, std::tuple<int, std::tuple<int,char, double, void*>, char, double, void*>>::value, "");
}

