struct foo
{
	int x;
};

struct bar
{
	static constexpr int foo::*px = &foo::x;
};

int main(void)
{
	return sizeof(bar);
}
