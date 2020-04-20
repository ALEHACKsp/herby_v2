#include "csgo/hooks/hooks.hpp"
namespace Hooks
{
	HRESULT   __stdcall Reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* presentation_parameters)
	{
		static auto result = direct_hook->GetOriginal<decltype(&Reset)>(16)(device, presentation_parameters);
		Renderer::Get().Lost();
		Renderer::Get().Reset(result);
		return result;
	}
}