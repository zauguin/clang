template <size_t I>
struct foo
{
	static constexpr size_t x = sizeof(I);
};

int main(void)
{
	return foo<int>::x?0:1;
}
