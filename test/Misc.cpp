#include "Misc.h"

#include "Empty.h"

#include <tuple>

void TestMisc()
{
    using Tuple_1= std::tuple<int>;
    using Tuple_2= std::tuple<int, char, int*, const int>;

    static_assert( is_instantiation_of<std::tuple, Tuple_1>::value == true, "");
    static_assert( is_instantiation_of<std::tuple, Tuple_2>::value == true, "");
    static_assert( is_instantiation_of<std::tuple, int>::value == false, "");
    static_assert( is_instantiation_of<std::tuple, Empty>::value == false, "");
    static_assert( is_instantiation_of<std::tuple, std::tuple<Empty>>::value == true, "");

}
