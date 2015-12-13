struct foo
{
	const int i;
	float f;
	static bool b;
	static constexpr const char c = 'x';
};


int main(void)
{
	return sizeof(foo);
}
