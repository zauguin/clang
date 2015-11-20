#include "reflexpr_base.hpp"

namespace foo {

struct bar { };

typedef bar baz;

} // namespace foo

int main(void)
{
	reflexpr(foo::baz) x;
	return sizeof(x);
}
