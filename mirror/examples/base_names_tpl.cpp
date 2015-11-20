#include "reflexpr.hpp"
#include <iostream>

template <typename T>
void print_base_name(void)
{
	using namespace std;

	typedef reflexpr(T) meta_T;

	cout << meta::get_name_v<meta_T> << endl;
	cout << meta::get_name_v<meta::get_aliased_t<meta_T>> << endl;
}

int main(void)
{
	print_base_name<int>();
	print_base_name<double>();
	print_base_name<std::istream>();

	return 0;
}
