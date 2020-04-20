#include "csgo/hooks/hooks.hpp"
#include <intrin.h>
namespace Hooks
{
	HRESULT   __stdcall EndScene(IDirect3DDevice9* device)
	{
		static auto original = direct_hook->GetOriginal<decltype(&EndScene)>(42);

		static auto wanted_ret_address = _ReturnAddress();

		if (_ReturnAddress() != wanted_ret_address) //Panorama fix credits to NuII from UC
			return original(device);
		
		auto& renderer = Renderer::Get();
		if (renderer.Begin())
		{
			renderer.DrawText({ 20.f, 10.f }, TextLeft, { 1.f, 1.f, 1.f }, "overlay");
			renderer.End();
		}
		GUI::Get().Render();
		renderer.Present();

		return original(device);
	}
}