#include "reflexpr_base.hpp"

template <typename T>
int foo(void)
{
	return int(sizeof(reflexpr(T)));
}

int main(void)
{
	return foo<int>();
}
