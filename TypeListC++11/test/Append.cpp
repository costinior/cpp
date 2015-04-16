#include "Append.h"
#include "Pack.h"
#include "IndexOf.h"

void TestAppend()
{
    using Tup = std::tuple<int, float, double*, unsigned int, void*>;
	static_assert(std::is_same<typename Append<Empty,Empty>::Result, Empty>::value, "");
    static_assert(std::is_same<typename Append<Empty,Tup>::Result, Tup>::value, "");
    static_assert(std::is_same<typename Append<Tup,Empty>::Result, Tup>::value, "");
    static_assert(std::is_same<typename Append<int,char>::Result, std::tuple<int,char>>::value, "");
    static_assert(std::is_same<typename Append<int,Empty>::Result, std::tuple<int>>::value, "");
    static_assert(std::is_same<typename Append<Empty,int>::Result, std::tuple<int>>::value, "");
    static_assert(std::is_same<typename Append<std::tuple<int>,std::tuple<char>>::Result, std::tuple<int,char>>::value, "");
    static_assert(std::is_same<typename Append<Pack<std::tuple<int>>, Pack<std::tuple<char>>>::Result,
                                               std::tuple<std::tuple<int>,std::tuple<char>>>::value, "");
    static_assert(std::is_same<typename Append<Pack<Tup>, Pack<Tup>>::Result,
                                               std::tuple<Tup,Tup>>::value, "");
    static_assert(std::is_same<typename Append<Tup, Tup>::Result,
                                               std::tuple<int, float, double*, unsigned int, void*, int, float, double*, unsigned int, void*>>::value, "");
    using Tup_1 = typename Append<std::tuple<int>, char>::Result;
    static_assert( IndexOf<Tup_1, char>::value == 1, "");
    using Tup_2 = typename Append<Tup, char>::Result;
    static_assert( IndexOf<Tup_2, char>::value == 5, "");
    using Tup_3 = typename Append<Tup, Tup_2>::Result;
    static_assert( std::tuple_size<Tup_3>::value == 11, "");
}
