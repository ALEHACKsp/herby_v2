#pragma once
#include <Windows.h>
#include "valve/auto.hpp"
#include "csgo/renderer\renderer.hpp"
#include "csgo/features/Gui.hpp"

namespace Hooks
{
	inline std::unique_ptr< VFTableHook > direct_hook;
	inline std::unique_ptr< VFTableHook > surface_hook;
	inline std::unique_ptr< VFTableHook > client_hook;

	void Initialize();
	void Restore();

	HRESULT   __stdcall EndScene(IDirect3DDevice9*);
	HRESULT   __stdcall Reset(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
	void      __stdcall CreateMove(int, float, bool, bool&);
	void      __stdcall CreateMove_Proxy(int, float, bool);
}

