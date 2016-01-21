#include "reflexpr.hpp"
#include <iostream>

struct foo { };
using bar = foo;

int main(void)
{
	using namespace std;

	// reflected typedef bar
	typedef reflexpr(bar) meta_bar;

	static_assert(is_metaobject_v<meta_bar>, "");
	static_assert(meta::is_type_v<meta_bar>, "");
	static_assert(meta::is_class_v<meta_bar>, "");
	static_assert(meta::is_alias_v<meta_bar>, "");

	static_assert(is_same<
		meta::get_reflected_type_t<meta_bar>,
		bar
	>::value, "");

	static_assert(meta::has_name_v<meta_bar>, "");
	cout << meta::get_name_v<meta_bar> << endl;
	// prints "bar"

	// getting the reflected struct foo
	typedef meta::get_aliased_t<meta_bar> meta_foo;

	static_assert(is_metaobject_v<meta_foo>, "");
	static_assert(meta::is_type_v<meta_foo>, "");
	static_assert(meta::is_class_v<meta_foo>, "");
	static_assert(!meta::is_alias_v<meta_foo>, "");

	static_assert(is_same<
		meta::get_reflected_type_t<meta_foo>,
		foo
	>::value, "");

	static_assert(meta::has_name_v<meta_foo>, "");
	cout << meta::get_name_v<meta_foo> << endl;
	// prints "foo"

	return 0;
}
