#include "reflexpr.hpp"
#include <iostream>

struct A
{
	int a;
};

class B : public A
{
private:
	bool b;
};

class C : public B
{
public:
	char c;
};

int main(void)
{
	using namespace std;

	typedef reflexpr(A) meta_A;
	typedef reflexpr(B) meta_B;
	typedef reflexpr(C) meta_C;

	cout << meta::get_size_v<meta::get_data_members_t<meta_A>> << endl;
	cout << meta::get_size_v<meta::get_data_members_t<meta_B>> << endl;
	cout << meta::get_size_v<meta::get_data_members_t<meta_C>> << endl;

	cout << meta::get_size_v<meta::get_all_data_members_t<meta_A>> << endl;
	cout << meta::get_size_v<meta::get_all_data_members_t<meta_B>> << endl;
	cout << meta::get_size_v<meta::get_all_data_members_t<meta_C>> << endl;

	return 0;
}
