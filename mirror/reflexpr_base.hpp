#ifndef REFLEXPR_BASE_HPP
#define REFLEXPR_BASE_HPP

template <unsigned Bits>
struct __reflexpr_mo_category
{
	static constexpr const unsigned _bits = Bits;
	typedef __reflexpr_mo_category type;
};

namespace std {

// tags
typedef __reflexpr_mo_category<0x00000001> namespace_tag;
typedef __reflexpr_mo_category<0x00000003> global_scope_tag;
typedef __reflexpr_mo_category<0x00000010> type_tag;
typedef __reflexpr_mo_category<0x00000030> class_tag;
typedef __reflexpr_mo_category<0x00000050> enum_tag_tag;

} // namespace std

struct __reflexpr_metaobject
{
	static constexpr const char _src_file[1] = "";
	static constexpr const unsigned _src_line = 0u;
	static constexpr const unsigned _src_column = 0u;
	static constexpr const bool _has_name = false;
	static constexpr const bool _has_scope = false;
	static constexpr const bool _is_scope = false;
	static constexpr const bool _is_alias = false;
};

struct __reflexpr_meta_g_s_base
 : __reflexpr_metaobject
{
	static constexpr const unsigned _cat_bits = 0x00000003;
	static constexpr const bool _has_name = true;
	static constexpr const char _base_name[1] = "";
	static constexpr const bool _has_scope = false;
	static constexpr const bool _is_scope = true;
};

struct __reflexpr_meta_ns_base
 : __reflexpr_metaobject
{
	static constexpr const unsigned _cat_bits = 0x00000001;
	static constexpr const bool _has_name = true;
	static constexpr const bool _has_scope = true;
	static constexpr const bool _is_scope = true;
};

#endif
