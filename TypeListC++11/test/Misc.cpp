#include "Misc.h"

void test()
{
    static_assert( is_instantiation_of<std::tuple, Tuple_2>::value == true, "");
    static_assert( is_instantiation_of<std::tuple, Tuple_4>::value == true, "");
    static_assert( is_instantiation_of<std::tuple, int>::value == false, "");
    static_assert( is_instantiation_of<std::tuple, Empty>::value == false, "");
    static_assert( is_instantiation_of<std::tuple, std::tuple<Empty>>::value == true, "");
    
}