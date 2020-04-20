#pragma once

#include <map>
#include <type_traits>
#include <cctype>
#include "valve/auto.hpp"

class NetvarManager
{
private:
	struct StoredPropData
	{
		RecvProp* prop_ptr;
		uint16_t class_relative_offset;
	};
public:
	static NetvarManager& Instance()
	{
		static NetvarManager instance;
		return instance;
	}

	unsigned short GetOffset(unsigned int hash) { return m_props[hash].class_relative_offset; }
	RecvProp* GetPropPtr(unsigned int hash) { return m_props[hash].prop_ptr; }

	// Prevent instruction cache pollution caused by automatic
	// inlining of Get and GetOffset every netvar usage when there
	// are a lot of netvars
	__declspec(noinline) static uint16_t GetOffsetByHash(fnv::hash hash)
	{
		return Instance().GetOffset(hash);
	}

	template<fnv::hash Hash>
	static std::uint16_t GetOffsetByHashCached()
	{
		static auto offset = std::uint16_t(0);
		if (!offset)
			offset = GetOffsetByHash(Hash);
		return offset;
	}
private:
	NetvarManager();
	void DumpRecursive(const char* base_class, RecvTable* table, uint16_t offset);
private:
	std::map<fnv::hash, StoredPropData> m_props;
};

#define PNETVAR_OFFSET(type, funcname, class_name, var_name, offset) \
auto funcname() -> std::add_pointer_t<type> \
{ \
	constexpr auto hash = fnv::hash_constexpr(class_name "->" var_name); \
	const auto addr = std::uintptr_t(this) + offset + NetvarManager::GetOffsetByHashCached<hash>(); \
	return reinterpret_cast<std::add_pointer_t<type>>(addr); \
}

#define PNETVAR(type, funcname, class_name, var_name) \
	PNETVAR_OFFSET(type, funcname, class_name, var_name, 0)

#define NETVAR_OFFSET(type, funcname, class_name, var_name, offset) \
auto funcname() -> std::add_lvalue_reference_t<type> \
{ \
	constexpr auto hash = fnv::hash_constexpr(class_name "->" var_name); \
	const auto addr = std::uintptr_t(this) + offset + NetvarManager::GetOffsetByHashCached<hash>(); \
	return *reinterpret_cast<std::add_pointer_t<type>>(addr); \
}

#define NETVAR(type, funcname, class_name, var_name) \
	NETVAR_OFFSET(type, funcname, class_name, var_name, 0)

#define NETPROP(funcname, class_name, var_name) \
static auto funcname() ->  RecvProp* \
{ \
	constexpr auto hash = fnv::hash_constexpr(class_name "->" var_name); \
	static auto prop_ptr = NetvarManager::Instance().GetPropPtr(hash); \
	return prop_ptr; \
}