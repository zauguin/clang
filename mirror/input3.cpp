template <unsigned I>
struct foo
{
	static constexpr const unsigned value = I;
};

int main(void)
{
	return foo<0>::value;
}
