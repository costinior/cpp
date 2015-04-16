#include "Transform.h"

#include "TestHelpers.h"

void test()
{
    using Tuple_0 = typename Transform<Tup, MyTranformer>::Result;
    static_assert(std::is_same<Tuple_0, std::tuple<A<int>, A<float>, A<double*>, A<unsigned int>, A<void*>>>::value, "");
    static_assert(std::is_same<typename Transform<Empty, MyTranformer>::Result, Empty>::value, "");
    static_assert(std::is_same<typename Transform<std::tuple<A<int>>, MyTranformer>::Result, std::tuple<A<A<int>>> >::value, "");
}
