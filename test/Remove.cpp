#include "Remove.h"

#include "Pack.h"

#include <vector>

void TestRemove()
{
	using namespace tpl;
   {
        using Tup = std::tuple<char, std::vector<int const *>>;
        static_assert(std::is_same<RemoveAtIndex<std::tuple<int>,0>::result, Empty>::value, "");
        static_assert(std::is_same<RemoveAtIndex<Tup,0>::result, std::tuple<std::vector<int const *>>>::value, "");
        static_assert(std::is_same<RemoveAtIndex<Tup,1>::result, std::tuple<char>>::value, "");
        static_assert(std::is_same<RemoveAtIndex<Pack<Tup>,0>::result, Empty>::value, "");
    }

    //
    {
        using Tup = std::tuple<char, double, float, std::vector<int>, char, char, int>;
        static_assert(std::is_same<RemoveAll<Empty, char>::result, Empty>::value, "");
        static_assert(std::is_same<RemoveAll<Tup, char>::result, std::tuple<double, float, std::vector<int>, int>>::value, "");
        static_assert(std::is_same<RemoveAll<Tup, int>::result, std::tuple<char, double, float, std::vector<int>, char, char>>::value, "");
    }
}
