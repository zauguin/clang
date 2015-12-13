#include "reflexpr_base.hpp"

template <typename X>
struct foo
{
	//static constexpr const unsigned value = sizeof(X);
	static constexpr const unsigned value = __reflexpr_size(X);
};

struct bar
{
	int i;
	static float f;
};

int main(void)
{
	return int(foo<reflexpr(bar)::_data_mems>::value);
}
