#ifndef PACK_H_20150419
#define PACK_H_20150419

#include <tuple>

namespace tpl
{
	template<typename T> using Pack = std::tuple<T>;
}
#endif