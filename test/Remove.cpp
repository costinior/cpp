#include "Remove.h"

#include "Pack.h"

#include <vector>

void TestRemove()
{
	using namespace tpl;
   {
        using Tup = std::tuple<char, std::vector<int const *>>;
        static_assert(std::is_same<typename RemoveAtIndex<std::tuple<int>,0>::Result, Empty>::value, "");
        static_assert(std::is_same<typename RemoveAtIndex<Tup,0>::Result, std::tuple<std::vector<int const *>>>::value, "");
        static_assert(std::is_same<typename RemoveAtIndex<Tup,1>::Result, std::tuple<char>>::value, "");
        static_assert(std::is_same<typename RemoveAtIndex<Pack<Tup>,0>::Result, Empty>::value, "");
    }

    //
    {
        using Tup = std::tuple<char, double, float, std::vector<int>, char, char, int>;
        static_assert(std::is_same<typename RemoveAll<Empty, char>::Result, Empty>::value, "");
        static_assert(std::is_same<typename RemoveAll<Tup, char>::Result, std::tuple<double, float, std::vector<int>, int>>::value, "");
        static_assert(std::is_same<typename RemoveAll<Tup, int>::Result, std::tuple<char, double, float, std::vector<int>, char, char>>::value, "");
    }
}
