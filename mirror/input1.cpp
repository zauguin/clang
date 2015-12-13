#include "reflexpr_base.hpp"

template <typename X, unsigned I>
struct foo
{
	typedef __reflexpr_element(X, I) type;
};

struct bar
{
	typedef bar _type;
	int i;
	static float f;
};

struct baz
{
	typedef reflexpr(bar)::_all_data_mems mems;
};

int main(void)
{
	return sizeof(foo<baz::mems, 0>::type);
}
