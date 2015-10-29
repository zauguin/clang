namespace foo {

struct bar { };

} // namespace foo

int main(void)
{
	reflexpr(foo::bar) x;
	return sizeof(x);
}
