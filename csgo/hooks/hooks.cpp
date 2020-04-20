#include "csgo/hooks/hooks.hpp"
namespace Hooks
{
	void Initialize()
	{
		direct_hook = std::make_unique<VFTableHook>(csgo::m_direct_device);
		surface_hook = std::make_unique<VFTableHook>(csgo::m_surface);

		direct_hook->Hook(16, &Reset);
		direct_hook->Hook(42, &EndScene);

		//surface_hook->Hook(67, &LockCursor);

		
	}
	void Restore()
	{
		direct_hook->RestoreTable();
		surface_hook->RestoreTable();

		Input::Get().Restore();
		System::Get().Restore();
		Renderer::Get().Restore();
	}
}