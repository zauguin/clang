#ifndef REFLEXPR_BASE_HPP
#define REFLEXPR_BASE_HPP

struct __reflexpr_metaobject
{
	static constexpr const unsigned _cat_bits = 0x00000000;
	static constexpr const char _src_file[1] = "";
	static constexpr const unsigned _src_line = 0u;
	static constexpr const unsigned _src_column = 0u;
	static constexpr const bool _is_spcfr = false;
	static constexpr const bool _has_name = false;
	static constexpr const bool _has_type = false;
	static constexpr const bool _has_scope = false;
	static constexpr const bool _is_scope = false;
	static constexpr const bool _is_alias = false;
	static constexpr const bool _is_cls_mem = false;
	static constexpr const bool _is_lnkable = false;
	static constexpr const bool _is_seq = false;
};

struct __reflexpr_moseq_base
 : __reflexpr_metaobject
{
	static constexpr const bool _is_seq = true;
};

struct __reflexpr_meta_spc_base
 : __reflexpr_metaobject
{
	static constexpr const bool _is_spcfr = true;
};

struct __reflexpr_meta_g_s_base
 : __reflexpr_metaobject
{
	static constexpr const unsigned _cat_bits = 0x00000003;
	static constexpr const bool _has_name = true;
	struct _base_name
	{
		static constexpr const char _str[1] = "";
	};
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

struct __reflexpr_meta_var_base
 : __reflexpr_metaobject
{
	static constexpr const unsigned _cat_bits = 0x00000100;
	static constexpr const bool _has_name = true;
	static constexpr const bool _has_type = true;
	static constexpr const bool _is_lnkable = true;
};

#endif
