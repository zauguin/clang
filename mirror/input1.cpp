#include "reflexpr_base.hpp"

template <typename X, unsigned I>
struct foo
{
	typedef __reflexpr_element(X, I) type;
};

int main(void)
{
	return sizeof(foo<reflexpr(int), 0>::type);
}
