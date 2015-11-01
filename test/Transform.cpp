#include "Transform.h"

#include "TestHelpers.h"

void TestTransform()
{
	using namespace tpl;
    using Tup = std::tuple<int, float, double*, unsigned int, void*>;
    using Tuple_0 = Transform<Tup, MyTranformer>::Result;

    static_assert(std::is_same<Tuple_0, std::tuple<A<int>, A<float>, A<double*>, A<unsigned int>, A<void*>>>::value, "");
    static_assert(std::is_same<Transform<Empty, MyTranformer>::Result, Empty>::value, "");
    static_assert(std::is_same<Transform<std::tuple<A<int>>, MyTranformer>::Result, std::tuple<A<A<int>>> >::value, "");
}
