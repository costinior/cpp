#ifndef _TEST_HELPERS_160420151105_
#define _TEST_HELPERS_160420151105_

#include <cstddef>

template <typename T>
class A
{
    T m;
};

template<typename T, std::size_t C>
struct MyTranformer
{
    using type = A<T>;
};

#endif
