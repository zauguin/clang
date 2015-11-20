#include "reflexpr.hpp"
#include <iostream>

namespace foo {

struct bar { };

} // namespace foo

typedef int baz;

int main(void)
{
	using namespace std;

	typedef reflexpr(int) meta_int;
	typedef reflexpr(foo::bar) meta_foo_bar;
	typedef reflexpr(baz) meta_baz;
	typedef meta::get_scope_t<meta_int> meta_gs;
	typedef meta::get_scope_t<meta_foo_bar> meta_foo;

	static_assert(!is_metaobject_v<char>, "");
	static_assert(!is_metaobject_v<int>, "");
	static_assert(is_metaobject_v<meta_int>, "");
	static_assert(is_metaobject_v<meta_foo>, "");
	static_assert(is_metaobject_v<meta_foo_bar>, "");
	static_assert(is_metaobject_v<meta_baz>, "");

	static_assert(meta::is_global_scope_v<meta_gs>, "");
	static_assert(meta::is_namespace_v<meta_gs>, "");

	static_assert(meta::is_namespace_v<meta_foo>, "");

	static_assert(meta::is_type_v<meta_baz>, "");
	static_assert(meta::is_alias_v<meta_baz>, "");

	static_assert(meta::is_class_v<meta_foo_bar>, "");

	return 0;
}
