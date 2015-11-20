#ifndef REFLEXPR_HPP
#define REFLEXPR_HPP

#include "reflexpr_base.hpp"
#include "int_sequence.hpp"

namespace std {

// this can be replaced for example with basic_string_literal from n4236
template <char ... C>
struct __reflexpr_string
{
	typedef __reflexpr_string type;

	typedef const char value_type [sizeof ... (C)];

	static constexpr const char value [sizeof ... (C)] = {C...};

	operator const char * (void) const noexcept { return value; }
	const char* operator()(void) const noexcept { return value; }
};

template <char ... C>
constexpr const char __reflexpr_string<C...>::value[sizeof ... (C)];

template <typename S, typename A>
struct __reflexpr_do_make_string;

template <typename S, typename IS>
struct __reflexpr_create_string;

template <typename S, std::size_t ... I>
struct __reflexpr_create_string<S, std::index_sequence<I...>>
 : __reflexpr_string<S::_str[I]...>
{ };

template <typename S, std::size_t N>
struct __reflexpr_do_make_string<S, const char[N]>
 : __reflexpr_create_string<S, std::make_index_sequence<N>>
{ };

template <typename S>
struct __reflexpr_do_make_string<S, const char[0]>
 : __reflexpr_string<'\0'>
{ };

template <typename S>
struct __reflexpr_make_string
 : __reflexpr_do_make_string<S, decltype(S::_str)>
{ };

// is_metaobject
template <typename X>
struct is_metaobject
 : std::integral_constant<bool, __is_metaobject(X)>
{ };

template <typename X>
using is_metaobject_t = typename is_metaobject<X>::type;

template <typename X>
constexpr bool is_metaobject_v = is_metaobject<X>::value;

namespace meta {

// get_category
template <typename X>
struct get_category
 : __reflexpr_mo_category<X::_cat_bits>
{ };

template <typename X>
using get_category_t = typename get_category<X>::type;

// has_category
template <typename X, typename C>
struct has_category;

template <typename X, unsigned B>
struct has_category<X, __reflexpr_mo_category<B>>
 : std::integral_constant<bool, (X::_cat_bits & B) == B>
{ };

template <typename X, typename C>
using has_category_t = typename has_category<X, C>::type;

template <typename X, typename C>
constexpr bool has_category_v = has_category<X, C>::value;

// is_namespace
template <typename X>
using is_namespace = has_category<X, namespace_tag>;

template <typename X>
constexpr bool is_namespace_v = is_namespace<X>::value;

// is_global_scope
template <typename X>
using is_global_scope = has_category<X, global_scope_tag>;

template <typename X>
constexpr bool is_global_scope_v = is_global_scope<X>::value;

// is_type
template <typename X>
using is_type = has_category<X, type_tag>;

template <typename X>
constexpr bool is_type_v = is_type<X>::value;

// is_class
template <typename X>
using is_class = has_category<X, class_tag>;

template <typename X>
constexpr bool is_class_v = is_class<X>::value;

// has_name
template <typename X>
struct has_name
 : std::integral_constant<bool, X::_has_name>
{ };

template <typename X>
using has_name_t = typename has_name<X>::type;

template <typename X>
constexpr bool has_name_v = has_name<X>::value;

// get_name
template <typename X>
struct get_name
 : __reflexpr_make_string<typename X::_base_name>
{ };

template <typename X>
constexpr auto& get_name_v = get_name<X>::value;

// has_scope
template <typename X>
struct has_scope
 : std::integral_constant<bool, X::_has_scope>
{ };

template <typename X>
using has_scope_t = typename has_scope<X>::type;

template <typename X>
constexpr bool has_scope_v = has_scope<X>::value;

// is_scope
template <typename X>
struct is_scope
 : std::integral_constant<bool, X::_is_scope>
{ };

template <typename X>
using is_scope_t = typename is_scope<X>::type;

template <typename X>
constexpr bool is_scope_v = is_scope<X>::value;

// get_scope
template <typename X>
struct get_scope
{
	typedef typename X::_scope type;
};

template <typename X>
using get_scope_t = typename get_scope<X>::type;

// source_file
template <typename X>
struct source_file
 : __reflexpr_make_string<typename X::_src_file>
{ };

template <typename X>
constexpr auto& source_file_v = source_file<X>::value;

// source_line
template <typename X>
struct source_line 
 : std::integral_constant<unsigned, X::_src_line>
{ };

template <typename X>
using source_line_t = typename source_line<X>::type;

template <typename X>
constexpr unsigned source_line_v = source_line<X>::value;

// source_column
template <typename X>
struct source_column
 : std::integral_constant<unsigned, X::_src_column>
{ };

template <typename X>
using source_column_t = typename source_column<X>::type;

template <typename X>
constexpr unsigned source_column_v = source_column<X>::value;

// get_type
template <typename X>
struct get_type
{
	typedef typename X::_orig_type type;
};

template <typename X>
using get_type_t = typename get_type<X>::type;

// is_alias
template <typename X>
struct is_alias
 : std::integral_constant<bool, X::_is_alias>
{ };

template <typename X>
using is_alias_t = typename is_alias<X>::type;

template <typename X>
constexpr bool is_alias_v = is_alias<X>::value;

// get_aliased 
template <typename X>
struct get_aliased
{
	typedef typename X::_aliased type;
};

template <typename X>
using get_aliased_t = typename get_aliased<X>::type;

// get_typedef_type
template <typename X>
struct get_typedef_type
 : get_aliased<X>
{
	static_assert(has_category_v<X, type_tag>, "");
};

template <typename X>
using get_typedef_type_t = typename get_typedef_type<X>::type;

} // namespace meta
} // namespace std

#endif
