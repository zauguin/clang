#ifndef REFLEXPR_RT_HPP
#define REFLEXPR_RT_HPP

#include "reflexpr.hpp"
#include <type_traits>

namespace std {
namespace meta_rt {

enum class metaobject_category : unsigned char
{
	namespace_tag = 0x01,
	global_scope_tag = 0x03,
	type_tag = 0x10,
	class_tag = 0x30,
	enum_tag = 0x50,
	none = 0x00
};

class metaobject
{
private:
#define REFLEXPR_RT_MAKE_CAT(CAT) \
	static constexpr \
	metaobject_category _make_cat(meta::CAT##_tag) \
	noexcept \
	{ \
		return metaobject_category::CAT##_tag; \
	}
	REFLEXPR_RT_MAKE_CAT(namespace)
	REFLEXPR_RT_MAKE_CAT(global_scope)
	REFLEXPR_RT_MAKE_CAT(type)
	REFLEXPR_RT_MAKE_CAT(class)
	REFLEXPR_RT_MAKE_CAT(enum)

#undef REFLEXPR_RT_MAKE_CAT

	metaobject_category _category;
	bool _has_name : 1;
	bool _has_scope : 1;
	bool _is_scope : 1;
	bool _is_alias : 1;

	constexpr inline
	metaobject(
		metaobject_category mo_category,
		bool mo_has_name,
		bool mo_has_scope,
		bool mo_is_scope,
		bool mo_is_alias
	) noexcept
	 : _category(mo_category)
	 , _has_name(mo_has_name)
	 , _has_scope(mo_has_scope)
	 , _is_scope(mo_is_scope)
	 , _is_alias(mo_is_alias)
	{ }

protected:
	constexpr inline
	metaobject(void)
	noexcept
	 : _category(metaobject_category::none)
	 , _has_name(false)
	 , _has_scope(false)
	 , _is_scope(false)
	 , _is_alias(false)
	{ }

public:
	template <
		typename Metaobject,
		typename=typename enable_if<is_metaobject_v<Metaobject>>::type
	>
	static constexpr
	metaobject create(void)
	noexcept
	{
		return {
			_make_cat(meta::get_category_t<Metaobject>()),
			meta::has_name_v<Metaobject>,
			meta::has_scope_v<Metaobject>,
			meta::is_scope_v<Metaobject>,
			meta::is_alias_v<Metaobject>
		};
	}

	constexpr
	metaobject_category get_category(void) const
	noexcept
	{
		return _category;
	}

	constexpr
	bool has_category(metaobject_category cat) const
	noexcept
	{
		typedef std::underlying_type<metaobject_category>::type B;
		return (B(_category) & B(cat)) == B(cat);
	}

	constexpr
	bool is_metaobject(void) const
	noexcept
	{
		return _category != metaobject_category::none;
	}

	constexpr
	bool is_namespace(void) const
	noexcept
	{
		return has_category(metaobject_category::namespace_tag);
	}

	constexpr
	bool is_global_scope(void) const
	noexcept
	{
		return has_category(metaobject_category::global_scope_tag);
	}

	constexpr
	bool is_type(void) const
	noexcept
	{
		return has_category(metaobject_category::type_tag);
	}

	constexpr
	bool is_class(void) const
	noexcept
	{
		return has_category(metaobject_category::class_tag);
	}

	constexpr
	bool is_enum(void) const
	noexcept
	{
		return has_category(metaobject_category::enum_tag);
	}

	constexpr
	bool has_name(void) const
	noexcept
	{
		return _has_name;
	}

	constexpr
	bool has_scope(void) const
	noexcept
	{
		return _has_scope;
	}

	constexpr
	bool is_scope(void) const
	noexcept
	{
		return _is_scope;
	}

	constexpr
	bool is_alias(void) const
	noexcept
	{
		return _is_alias;
	}
};

class meta_named
 : virtual public metaobject
{
private:
	const char* _name;

	meta_named(
		metaobject base,
		const char* name
	) noexcept
	 : metaobject(base)
	 , _name(name)
	{ }

public:
	meta_named(void)
	noexcept
	 : metaobject()
	 , _name(nullptr)
	{ }

	template <
		typename Metaobject,
		typename=typename enable_if<is_metaobject_v<Metaobject>>::type,
		typename=typename enable_if<meta::has_name_v<Metaobject>>::type
	>
	static
	meta_named create(void)
	noexcept
	{
		return {
			metaobject::create<Metaobject>(),
			meta::get_name_v<Metaobject>
		};
	}

	const char* get_name(void) const
	noexcept
	{
		return _name;
	}
};

class meta_scoped
 : virtual public metaobject
{
private:
	meta_named _scope;

	meta_scoped(
		metaobject base,
		meta_named scope_mo
	) noexcept
	 : metaobject(base)
	 , _scope(scope_mo)
	{ }
protected:
	meta_scoped(void)
	noexcept
	 : metaobject()
	 , _scope()
	{ }
public:
	template <
		typename Metaobject,
		typename=typename enable_if<is_metaobject_v<Metaobject>>::type,
		typename=typename enable_if<meta::has_scope_v<Metaobject>>::type
	>
	static
	meta_scoped create(void)
	noexcept
	{
		return {
			metaobject::create<Metaobject>(),
			meta_named::create<meta::get_scope_t<Metaobject>>()
		};
	}

	const meta_named& get_scope(void) const
	noexcept
	{
		return _scope;
	}
};

class meta_type
 : public meta_named
 , public meta_scoped
{
private:
	meta_type(
		metaobject base_mo,
		meta_named base_mn,
		meta_scoped base_msd
	) noexcept
	 : metaobject(base_mo)
	 , meta_named(base_mn)
	 , meta_scoped(base_msd)
	{ }
public:
	meta_type(void)
	 : metaobject()
	 , meta_named()
	 , meta_scoped()
	{ }

	template <
		typename Metaobject,
		typename=typename enable_if<is_metaobject_v<Metaobject>>::type,
		typename=typename enable_if<meta::is_type_v<Metaobject>>::type
	>
	static
	meta_type create(void)
	noexcept
	{
		return {
			metaobject::create<Metaobject>(),
			meta_named::create<Metaobject>(),
			meta_scoped::create<Metaobject>()
		};
	}
};

} // namespace meta_rt
} // namespace std

#endif
