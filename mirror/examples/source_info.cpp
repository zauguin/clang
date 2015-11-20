#include "reflexpr.hpp"
#include <iostream>

struct foo { };

int main(void)
{
	using namespace std;

	// reflected foo
	typedef reflexpr(foo) meta_foo;

	static_assert(is_metaobject_v<meta_foo>, "");

	cout << "name: " << meta::get_name_v<meta_foo> << endl;
	cout << "file: " << meta::source_file_v<meta_foo> << endl;
	cout << "line: " << meta::source_line_v<meta_foo> << endl;
	cout << "col: "<< meta::source_column_v<meta_foo> << endl;

	return 0;
}
