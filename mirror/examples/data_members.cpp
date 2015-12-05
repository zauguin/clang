#include "reflexpr.hpp"
#include <iostream>

struct point
{
	float x, y, z;
};

struct triangle
{
	point a, b, c;
};

int main(void)
{
	using namespace std;

	// reflected type unsigned
	typedef reflexpr(triangle) meta_triangle;

	typedef meta::get_data_members_t<meta_triangle> meta_data_mems;

	static_assert(is_metaobject_v<meta_data_mems>, "");
	static_assert(meta::is_sequence_v<meta_data_mems>, "");

	return 0;
}
