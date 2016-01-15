#include "reflexpr.hpp"
#include <iostream>

int main(void)
{
	using namespace std;

	// reflected type unsigned
	typedef reflexpr(unsigned) meta_unsigned;

	static_assert(is_metaobject_v<meta_unsigned>, "");
	static_assert(meta::is_type_v<meta_unsigned>, "");
	static_assert(!meta::is_alias_v<meta_unsigned>, "");

	static_assert(is_same<
		meta::get_reflected_type_t<meta_unsigned>,
		unsigned
	>::value, "");

	static_assert(meta::has_name_v<meta_unsigned>, "");
	cout << meta::get_name_v<meta_unsigned> << endl;
	// prints "unsigned int"

	typedef reflexpr(unsigned*) meta_ptr_unsigned;
	cout << meta::get_name_v<meta_ptr_unsigned> << endl;

	return 0;
}
