#include "Insert.h"
#include "Pack.h"

#include "TestHelpers.h"

void TestInsert()
{
    using Tup = std::tuple<int,char, double, void*>;
	using Tup1 = std::tuple<int, char, void, double>;
	using Tup2 = std::tuple<A<int>, volatile char, const double* const>;

	static_assert( std::is_same<typename Insert<Empty, Empty, 0>::Result, Empty>::value, "");
	static_assert( std::is_same<typename Insert<Empty, char, 0>::Result, std::tuple<char>>::value, "");
	static_assert( std::is_same<typename Insert<Empty, Tup1, 0>::Result, Tup1>::value, "");
	static_assert(std::is_same<typename Insert<Tup, Empty, 0>::Result, Tup>::value, "");
	static_assert(std::is_same<typename Insert<Tup, Empty, 1>::Result, Tup>::value, "");
	static_assert(std::is_same<typename Insert<Tup, Empty, 2>::Result, Tup>::value, "");
	static_assert(std::is_same<typename Insert<Tup, Empty, 3>::Result, Tup>::value, "");
	static_assert(std::is_same<typename Insert<Tup, Empty, 4>::Result, Tup>::value, "");
	static_assert( std::is_same<typename Insert<Tup1, char, 0>::Result,
								std::tuple<char, int, char, void, double>>::value, "");
	static_assert( std::is_same<typename Insert<Tup2, char, 0>::Result,
								std::tuple<char, A<int>, volatile char, const double* const>>::value, "");
	static_assert( std::is_same<typename Insert<Tup1, Tup2, 0>::Result,
								std::tuple<A<int>, volatile char, const double* const, int, char, void, double>>::value, "");
	static_assert( std::is_same<typename Insert<Tup1, Pack<Tup2>, 0>::Result,
								std::tuple<std::tuple<A<int>, volatile char, const double* const>, int, char, void, double>>::value, "");

	static_assert( std::is_same<typename Insert<Tup1, char, 4>::Result,
								std::tuple<int, char, void, double, char>>::value, "");
	static_assert( std::is_same<typename Insert<Tup2, char, 3>::Result,
								std::tuple<A<int>, volatile char, const double* const, char>>::value, "");
	static_assert( std::is_same<typename Insert<Tup1, Tup2, 4>::Result,
								std::tuple<int, char, void, double, A<int>, volatile char, const double* const>>::value, "");
	static_assert( std::is_same<typename Insert<Tup1, Pack<Tup2>, 4>::Result,
								std::tuple<int, char, void, double, std::tuple<A<int>, volatile char, const double* const>>>::value, "");


	static_assert(std::is_same<typename Insert<Empty, char, 0>::Result, std::tuple<char>>::value, "");
	static_assert(std::is_same<typename Insert<Empty, Pack<std::tuple<char>>, 0>::Result, std::tuple<std::tuple<char>> >::value, "");


	static_assert(std::is_same<typename Insert<Tup, char, 0>::Result, std::tuple<char, int,char, double, void*>>::value, "");
	static_assert(std::is_same<typename Insert<Tup, char, 1>::Result, std::tuple<int, char, char, double, void*>>::value, "");
	static_assert(std::is_same<typename Insert<Tup, char, 2>::Result, std::tuple<int, char, char, double, void*>>::value, "");
	static_assert(std::is_same<typename Insert<Tup, char, 3>::Result, std::tuple<int, char, double, char, void*>>::value, "");
    static_assert(std::is_same<typename Insert<Tup, char, 4>::Result, std::tuple<int, char, double, void*, char>>::value, "");

	static_assert(std::is_same<typename Insert<Tup, Tup, 4>::Result, std::tuple<int,char, double, void*, int,char, double, void*>>::value, "");
	static_assert(std::is_same<typename Insert<Tup, Tup, 0>::Result, std::tuple<int,char, double, void*, int,char, double, void*>>::value, "");
	static_assert(std::is_same<typename Insert<Tup, Tup, 1>::Result, std::tuple<int, int,char, double, void*, char, double, void*>>::value, "");

	static_assert(std::is_same<typename Insert<Tup, Pack<Tup>, 0>::Result, std::tuple<Tup, int, char, double, void*>>::value, "");
	static_assert(std::is_same<typename Insert<Tup, Pack<Tup>, 4>::Result, std::tuple<int, char, double, void*, std::tuple<int,char, double, void*>>>::value, "");
    static_assert(std::is_same<typename Insert<Tup, Pack<Tup>, 1>::Result, std::tuple<int, std::tuple<int,char, double, void*>, char, double, void*>>::value, "");
}

