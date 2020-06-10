#pragma once
#define NOMINMAX
#include <Windows.h>
#include <string>
#include <vector>
#include <TlHelp32.h>
#include <Psapi.h>
namespace memory {
	template< std::size_t N, typename T >
	T vget(void* object) {
		const auto procedure_array = *(uintptr_t**)(object);
		return (T)(procedure_array[N]);
	}

	template< std::size_t N, typename T, typename... ArgsT >
	T Call(void* object, ArgsT... args) {
		const auto procedure = vget< N, T(__thiscall*)(void*, ArgsT...) >(object);
		return procedure(object, args...);
	}
	//@credits:Ducarii
	uintptr_t find_ida_sig(std::string module,std::string signature);
}
#define VFUNC( index, func, sig,args,raw) auto func = { memory::Call<index,sig>(this,args)##raw}
#define OFFSET( type, func, offset ) type& func() { return *reinterpret_cast< type* >( reinterpret_cast< uintptr_t >( this ) + offset); }