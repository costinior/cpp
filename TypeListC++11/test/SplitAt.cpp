#include "SplitAt.h"

void test()
{
	using Tup2 = std::tuple<char*>;
	static_assert( std::is_same<typename SplitAt<Empty, 0>::Left,  Empty>::value, "");
	static_assert( std::is_same<typename SplitAt<Empty, 0>::Right, Empty>::value, "");
	static_assert( std::is_same<typename SplitAt<Tup2, 0>::Left,  Empty>::value, "");
	static_assert( std::is_same<typename SplitAt<Tup2, 0>::Right, Tup2>::value, "");
	static_assert( std::is_same<typename SplitAt<Tup2, 1>::Left,  Tup2>::value, "");
	static_assert( std::is_same<typename SplitAt<Tup2, 1>::Right, Empty>::value, "");
	static_assert( std::is_same<typename SplitAt<Tup, 0>::Left,  Empty>::value, "");
	static_assert( std::is_same<typename SplitAt<Tup, 0>::Right, Tup>::value, "");
	static_assert( std::is_same<typename SplitAt<Tup, 5>::Left,  Tup>::value, "");
	static_assert( std::is_same<typename SplitAt<Tup, 5>::Right, Empty>::value, "");
	static_assert( std::is_same<typename SplitAt<Tup, 4>::Left,  std::tuple<int, float, double*, unsigned int>>::value, "");
	static_assert( std::is_same<typename SplitAt<Tup, 4>::Right, std::tuple<void*>>::value, "");
	static_assert( std::is_same<typename SplitAt<Tup, 3>::Left,  std::tuple<int, float, double*>>::value, "");
	static_assert( std::is_same<typename SplitAt<Tup, 3>::Right, std::tuple<unsigned int, void*>>::value, "");
	static_assert( std::is_same<typename SplitAt<Tup, 2>::Left,  std::tuple<int, float>>::value, "");
	static_assert( std::is_same<typename SplitAt<Tup, 2>::Right, std::tuple<double*, unsigned int, void*>>::value, "");
	static_assert( std::is_same<typename SplitAt<Tup, 1>::Left,  std::tuple<int>>::value, "");
	static_assert( std::is_same<typename SplitAt<Tup, 1>::Right, std::tuple<float, double*, unsigned int, void*>>::value, "");
}