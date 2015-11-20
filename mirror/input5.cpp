#include "reflexpr.hpp"
#include <iostream>
#include <iomanip>

namespace foo {

struct bar
{
	typedef int baz;
};

} // namespace foo

typedef long fubar;

int main(void)
{
	std::cout << std::boolalpha;
	std::cout << std::meta::has_scope_v<reflexpr(int)> << std::endl;
	std::cout << std::meta::has_scope_v<reflexpr(foo::bar)> << std::endl;
	std::cout << std::meta::has_scope_v<reflexpr(foo::bar::baz)> << std::endl;
	std::cout << std::meta::has_scope_v<reflexpr(fubar)> << std::endl;

	std::cout << std::meta::get_name_v<std::meta::scope_t<reflexpr(foo::bar)>> << std::endl;
	std::cout << std::meta::get_name_v<std::meta::scope_t<reflexpr(foo::bar::baz)>> << std::endl;

	return 0;
}
