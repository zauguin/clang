#include "reflexpr_rt.hpp"
#include <iostream>
#include <iomanip>

#include <typeindex>
#include <map>

static 
std::map<std::type_index, std::meta_rt::meta_type>&
meta_types(void)
{
	static std::map<std::type_index, std::meta_rt::meta_type> _map;
	return _map;
}

static
void add_meta_type(std::type_index key, std::meta_rt::meta_type mt)
{
	meta_types()[key] = mt;
}

static
const std::meta_rt::meta_type& get_meta_type(std::type_index key)
{
	return meta_types()[key];
}

void print_meta_info(const std::meta_rt::meta_type& mo)
{
	using namespace std;

	if(mo.is_metaobject())
	{
		cout << boolalpha;
		cout << "is_namespace:    " << mo.is_namespace() << endl;
		cout << "is_type:         " << mo.is_type() << endl;
		cout << "is_class:        " << mo.is_class() << endl;
		cout << "has_name:        " << mo.has_name() << endl;
		cout << "has_scope:       " << mo.has_scope() << endl;
		cout << "is_scope:        " << mo.is_scope() << endl;
		cout << "is_alias:        " << mo.is_alias() << endl;
		cout << "in global_scope: "
			<< mo.get_scope().is_global_scope() << endl;
		cout << "in namespace:    "
			<< mo.get_scope().is_namespace() << endl;

		cout << "get_name:        '" << mo.get_name() << "'" << endl;

		cout << "scope name:      '"
			<< mo.get_scope().get_name() << "'" << endl;
	}
	else cout << "Not a metaobject" << endl;
}

namespace foo {

struct base
{
	struct nested { };

	virtual ~base(void) = default;
};

struct derived : base
{
	virtual ~derived(void) = default;
};

} // namespace foo

typedef foo::base baz;

void register_types(void)
{
	using std::meta_rt::meta_type;

	add_meta_type(
		typeid(int),
		meta_type::create<reflexpr(int)>()
	);
	add_meta_type(
		typeid(unsigned),
		meta_type::create<reflexpr(unsigned)>()
	);
	add_meta_type(
		typeid(foo::base),
		meta_type::create<reflexpr(foo::base)>()
	);
	add_meta_type(
		typeid(foo::base::nested),
		meta_type::create<reflexpr(foo::base::nested)>()
	);
	add_meta_type(
		typeid(foo::derived),
		meta_type::create<reflexpr(foo::derived)>()
	);
}

int main(void)
{
	using namespace std;
	using std::meta_rt::meta_type;

	register_types();

	foo::base b;
	const foo::base& d = foo::derived();

	cout << "-----------------------------------" << endl;
	print_meta_info(get_meta_type(typeid(void)));
	cout << "-----------------------------------" << endl;
	print_meta_info(get_meta_type(typeid(int)));
	cout << "-----------------------------------" << endl;
	print_meta_info(get_meta_type(typeid(unsigned)));
	cout << "-----------------------------------" << endl;
	print_meta_info(get_meta_type(typeid(b)));
	cout << "-----------------------------------" << endl;
	print_meta_info(get_meta_type(typeid(d)));
	cout << "-----------------------------------" << endl;
	print_meta_info(get_meta_type(typeid(foo::base::nested)));
	cout << "-----------------------------------" << endl;
	print_meta_info(meta_type::create<reflexpr(baz)>());
	cout << "-----------------------------------" << endl;

	return 0;
}
