#include "reflexpr.hpp"
#include <iostream>

struct foo { };

int main(void)
{
	using namespace std;

	// reflected int
	typedef reflexpr(int) meta_int;

	static_assert(is_metaobject_v<meta_int>, "");

	cout << "name: '" << meta::get_name_v<meta_int> << "'" << endl;
	cout << "file: '" << meta::get_source_file_v<meta_int> << "'" << endl;
	cout << "line: " << meta::get_source_line_v<meta_int> << endl;
	cout << "col: "<< meta::get_source_column_v<meta_int> << endl;

	// reflected foo
	typedef reflexpr(foo) meta_foo;

	static_assert(is_metaobject_v<meta_foo>, "");

	cout << "name: '" << meta::get_name_v<meta_foo> << "'" << endl;
	cout << "file: '" << meta::get_source_file_v<meta_foo> << "'" << endl;
	cout << "line: " << meta::get_source_line_v<meta_foo> << endl;
	cout << "col: "<< meta::get_source_column_v<meta_foo> << endl;

	return 0;
}
