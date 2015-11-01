#include "Append.h"

#include "Pack.h"
#include "IndexOf.h"

void TestAppend()
{
	using namespace tpl;
	
    using Tup = std::tuple<int, float, double*, unsigned int, void*>;
	static_assert(std::is_same<Append<Empty,Empty>::result, Empty>::value, "");
    static_assert(std::is_same<Append<Empty,Tup>::result, Tup>::value, "");
    static_assert(std::is_same<Append<Tup,Empty>::result, Tup>::value, "");
    static_assert(std::is_same<Append<int,char>::result, std::tuple<int,char>>::value, "");
    static_assert(std::is_same<Append<int,Empty>::result, std::tuple<int>>::value, "");
    static_assert(std::is_same<Append<Empty,int>::result, std::tuple<int>>::value, "");
    static_assert(std::is_same<Append<std::tuple<int>,std::tuple<char>>::result, std::tuple<int,char>>::value, "");
    static_assert(std::is_same<Append<Pack<std::tuple<int>>, Pack<std::tuple<char>>>::result,
                                      std::tuple<std::tuple<int>,std::tuple<char>>>::value, "");
    static_assert(std::is_same<Append<Pack<Tup>, Pack<Tup>>::result,
                                      std::tuple<Tup,Tup>>::value, "");
    static_assert(std::is_same<Append<Tup, Tup>::result,
                                               std::tuple<int, float, double*, unsigned int, void*, int, float, double*, unsigned int, void*>>::value, "");
    using Tup_1 = Append<std::tuple<int>, char>::result;
    static_assert( IndexOf<Tup_1, char>::value == 1, "");
    using Tup_2 = Append<Tup, char>::result;
    static_assert( IndexOf<Tup_2, char>::value == 5, "");
    using Tup_3 = Append<Tup, Tup_2>::result;
    static_assert( std::tuple_size<Tup_3>::value == 11, "");
}
