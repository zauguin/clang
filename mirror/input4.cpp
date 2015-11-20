#include "reflexpr_base.hpp"

template <typename T>
int foo(void)
{
	reflexpr(T) x;
	return int(sizeof(x));
}

template <typename T>
int bar(void)
{
	reflexpr(T) x;
	return int(sizeof(x));
}

int main(void)
{
	return foo<int>()+bar<int>();
}
