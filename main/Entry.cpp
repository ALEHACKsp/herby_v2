#include "valve/auto.hpp"
#include "csgo/hooks/hooks.hpp"
#include "csgo/features/Gui.hpp"
void Initialize()
{
	csgo::Initialize();
	Input::Get().Initialize();
	System::Get().Initialize();
	Renderer::Get().Initialize(csgo::m_direct_device);
	GUI::Get().Initialize();
	Hooks::Initialize();
}

void Restore()
{
	Input::Get().Restore();
	System::Get().Restore();
	Renderer::Get().Restore();
	Hooks::Restore();
}
BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		Initialize();
		break;
	case DLL_PROCESS_DETACH:
		Restore();
		break;
	}
	return TRUE;
}