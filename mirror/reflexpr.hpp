#ifndef REFLEXPR_HPP
#define REFLEXPR_HPP

#include "reflexpr_base.hpp"
#include "int_sequence.hpp"

namespace std {

// is_metaobject
template <typename X>
struct is_metaobject
 : integral_constant<bool, __is_metaobject(X)>
{ };

template <typename X>
using is_metaobject_t = typename is_metaobject<X>::type;

template <typename X>
constexpr bool is_metaobject_v = is_metaobject<X>::value;

// namespace meta
namespace meta {

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

template <typename S, size_t ... I>
struct __reflexpr_create_string<S, index_sequence<I...>>
 : __reflexpr_string<S::_str[I]...>
{ };

template <typename S, size_t N>
struct __reflexpr_do_make_string<S, const char[N]>
 : __reflexpr_create_string<S, make_index_sequence<N>>
{ };

template <typename S>
struct __reflexpr_do_make_string<S, const char[0]>
 : __reflexpr_string<'\0'>
{ };

template <typename S>
struct __reflexpr_make_string
 : __reflexpr_do_make_string<S, decltype(S::_str)>
{ };

// mo_category
template <unsigned Bits>
struct __reflexpr_mo_category
{
	static constexpr const unsigned _bits = Bits;
	typedef __reflexpr_mo_category type;
};

// tags
typedef __reflexpr_mo_category<0x00000001> namespace_tag;
typedef __reflexpr_mo_category<0x00000003> global_scope_tag;
typedef __reflexpr_mo_category<0x00000010> type_tag;
typedef __reflexpr_mo_category<0x00000030> class_tag;
typedef __reflexpr_mo_category<0x00000050> enum_tag;
typedef __reflexpr_mo_category<0x00000100> variable_tag;

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
 : integral_constant<bool, (X::_cat_bits & B) == B>
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

// is_variable
template <typename X>
using is_variable = has_category<X, variable_tag>;

template <typename X>
constexpr bool is_variable_v = is_variable<X>::value;


// is_specifier
template <typename X>
struct is_specifier
 : integral_constant<bool, X::_is_spcfr>
{ };

template <typename X>
using is_specifier_t = typename is_specifier<X>::type;

template <typename X>
constexpr bool is_specifier_v = is_specifier<X>::value;


// is_sequence
template <typename X>
struct is_sequence
 : integral_constant<bool, X::_is_seq>
{ };

template <typename X>
using is_sequence_t = typename is_sequence<X>::type;

template <typename X>
constexpr bool is_sequence_v = is_sequence<X>::value;



// has_type
template <typename X>
struct has_type
 : integral_constant<bool, X::_has_type>
{ };

template <typename X>
using has_type_t = typename has_type<X>::type;

template <typename X>
constexpr bool has_type_v = has_type<X>::value;

// get_type
template <typename X>
struct get_type
{
	static_assert(has_type_v<X>, "");

	typedef typename X::_type type;
};

template <typename X>
using get_type_t = typename get_type<X>::type;



// has_name
template <typename X>
struct has_name
 : integral_constant<bool, X::_has_name>
{ };

template <typename X>
using has_name_t = typename has_name<X>::type;

template <typename X>
constexpr bool has_name_v = has_name<X>::value;

// get_name
template <typename X>
struct get_name
 : __reflexpr_make_string<typename X::_base_name>
{
	static_assert(has_name_v<X>, "");
};

template <typename X>
constexpr auto& get_name_v = get_name<X>::value;

// get_keyword
template <typename X>
struct get_keyword
 : __reflexpr_make_string<typename X::_keyword>
{
	static_assert(is_specifier_v<X>, "");
};

template <typename X>
constexpr auto& get_keyword_v = get_keyword<X>::value;

// has_scope
template <typename X>
struct has_scope
 : integral_constant<bool, X::_has_scope>
{ };

template <typename X>
using has_scope_t = typename has_scope<X>::type;

template <typename X>
constexpr bool has_scope_v = has_scope<X>::value;

// is_scope
template <typename X>
struct is_scope
 : integral_constant<bool, X::_is_scope>
{ };

template <typename X>
using is_scope_t = typename is_scope<X>::type;

template <typename X>
constexpr bool is_scope_v = is_scope<X>::value;

// get_scope
template <typename X>
struct get_scope
{
	static_assert(has_scope_v<X>, "");

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
 : integral_constant<unsigned, X::_src_line>
{ };

template <typename X>
using source_line_t = typename source_line<X>::type;

template <typename X>
constexpr unsigned source_line_v = source_line<X>::value;

// source_column
template <typename X>
struct source_column
 : integral_constant<unsigned, X::_src_column>
{ };

template <typename X>
using source_column_t = typename source_column<X>::type;

template <typename X>
constexpr unsigned source_column_v = source_column<X>::value;

// get_reflected_type
template <typename X>
struct get_reflected_type
{
	static_assert(is_type_v<X>, "");

	typedef typename X::_orig_type type;
};

template <typename X>
using get_reflected_type_t = typename get_reflected_type<X>::type;

// is_alias
template <typename X>
struct is_alias
 : integral_constant<bool, X::_is_alias>
{ };

template <typename X>
using is_alias_t = typename is_alias<X>::type;

template <typename X>
constexpr bool is_alias_v = is_alias<X>::value;

// get_aliased 
template <typename X>
struct get_aliased
{
	static_assert(is_alias_v<X>, "");

	typedef typename X::_aliased type;
};

template <typename X>
using get_aliased_t = typename get_aliased<X>::type;

// get_typedef_type
template <typename X>
struct get_typedef_type
 : get_aliased<X>
{
	static_assert(is_type_v<X>, "");
};

template <typename X>
using get_typedef_type_t = typename get_typedef_type<X>::type;


// is_class_member
template <typename X>
struct is_class_member
 : integral_constant<bool, X::_is_cls_mem>
{ };

template <typename X>
using is_class_member_t = typename is_class_member<X>::type;

template <typename X>
constexpr bool is_class_member_v = is_class_member<X>::value;


// get_elaborated_type_specifier
template <typename X>
struct get_elaborated_type_specifier
{
	typedef typename X::_tag_spc type;
};

template <typename X>
using get_elaborated_type_specifier_t =
	typename get_elaborated_type_specifier<X>::type;

// get_data_members
template <typename X>
struct get_data_members
{
	static_assert(is_class_v<X>, "");

	typedef typename X::_pub_data_mems type;
};

template <typename X>
using get_data_members_t = typename get_data_members<X>::type;

// get_all_data_members
template <typename X>
struct get_all_data_members
{
	static_assert(is_class_v<X>, "");

	typedef typename X::_all_data_mems type;
};

template <typename X>
using get_all_data_members_t = typename get_all_data_members<X>::type;


// get_size
template <typename X>
struct get_size
 : integral_constant<size_t, __reflexpr_size(X)>
{
	static_assert(is_sequence_v<X>, "");
};

template <typename X>
using get_size_t = typename get_size<X>::type;

template <typename X>
constexpr size_t get_size_v = get_size<X>::value;


// get_element
template <typename X, size_t I>
struct get_element
{
	static_assert(is_sequence_v<X>, "");
	typedef __reflexpr_element(X, I) type;
};

template <typename X, size_t I>
using get_element_t = typename get_element<X, I>::type;

} // namespace meta
} // namespace std

#endif
