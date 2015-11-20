#include "reflexpr.hpp"

int main(void)
{
	using namespace std;

	typedef reflexpr(::) meta_gs;

	static_assert(is_metaobject_v<meta_gs>, "");

	static_assert(meta::is_global_scope_v<meta_gs>, "");
	static_assert(meta::is_namespace_v<meta_gs>, "");
	static_assert(!meta::is_type_v<meta_gs>, "");
	static_assert(!meta::is_alias_v<meta_gs>, "");

	static_assert(meta::has_name_v<meta_gs>, "");
	static_assert(!meta::has_scope_v<meta_gs>, "");

	return 0;
}
