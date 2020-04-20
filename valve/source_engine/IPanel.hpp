#pragma once

#include "Definitions.hpp"

class IPanel
{
public:
	bool IsVisible(VPANEL vguiPanel)
	{
		using IsEnabled_t = const char *(__thiscall*)(PVOID, VPANEL);
		return GetVirtualFunction<IsEnabled_t>(this, 15)(this, vguiPanel);
	}

	const char* GetName(VPANEL vguiPanel)
	{
		using GetName_t = const char *(__thiscall*)(PVOID, VPANEL);
		return GetVirtualFunction<GetName_t>(this, 36)(this, vguiPanel);
	}
#ifdef GetClassName
#undef GetClassName
#endif
	const char* GetClassName(VPANEL vguiPanel)
	{
		using GetClassName_t = const char *(__thiscall*)(PVOID, VPANEL);
		return GetVirtualFunction<GetClassName_t>(this, 37)(this, vguiPanel);
	}
};