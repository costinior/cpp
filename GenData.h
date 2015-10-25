#ifndef GENDATA_H_20150419
#define GENDATA_H_20150419

#include "ScatterHierarchy.h"
#include "Transform.h"

namespace tpl
{
	enum class ClassMember
	{
		MEMBER_1,
		MEMBER_2,
		MEMBER_3,
		MEMBER_4,
		MEMBER_5
	};

	template <typename TypeValue>
	class Leaf
	{
	public:
		using T = typename TypeValue::type;
		static constexpr ClassMember classMem = TypeValue::value;

		const T& Get() const
		{
			return m;
		}

		void Set(const T& val)
		{
			m = val;
		}

	private:
		T m;
	};

	template<typename T, ClassMember M>
	struct TypeValue
	{
		using type = T;
		static constexpr ClassMember value = M;
	};

	template<typename T, std::size_t C>
	struct HirarchyTranformer
	{
		using type = TypeValue<T,static_cast<ClassMember>(C)>;
	};


	using Tup = std::tuple<int, float, double*, unsigned int, void*>;
	using HirarchyTup = Transform<Tup, HirarchyTranformer>::Result;

	struct Root : public ScatterHierarchy<HirarchyTup, Leaf>
	{
		template<ClassMember M> using ElemAt    = typename std::tuple_element<static_cast<std::size_t>(M), Tup>::type;
		template<ClassMember M> using LocalLeaf = Leaf<TypeValue<ElemAt<M>, M>>;

		template<ClassMember M>
		auto Get() const -> decltype(std::declval<LocalLeaf<M>>().Get())
		{
			return static_cast<const LocalLeaf<M>*>(this)->Get();
		}

		template<ClassMember M>
		void Set(const ElemAt<M>& val)
		{
			static_cast<LocalLeaf<M>*>(this)->Set(val);
		}
	};
}
#endif
