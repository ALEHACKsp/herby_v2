#include "SDK.hpp"
#include "valve/helpers/Factory.hpp"
#include "valve/helpers/Memory.hpp"
namespace csgo
{
	void Initialize()
	{
		Factory factory_client("client_panorama.dll");
		Factory factory_engine("engine.dll");
		Factory factory_vstdlib("vstdlib.dll");
		Factory factory_vphysics("vphysics.dll");
		Factory factory_materialsystem("materialsystem.dll");
		Factory factory_vgui("vguimatsurface.dll");

		m_base_client = factory_client.Get< IBaseClientDLL* >("VClient");
		m_client_entity_list = factory_client.Get< IClientEntityList* >("VClientEntityList");
		m_game_movement = factory_client.Get< CGameMovement* >("GameMovement");
		m_prediction = factory_client.Get< CPrediction* >("VClientPrediction");
		m_engine_client = factory_engine.Get< IVEngineClient* >("VEngineClient");
		m_model_info_client = factory_engine.Get< IVModelInfoClient* >("VModelInfoClient");
		m_render_view = factory_engine.Get< IVRenderView* >("VEngineRenderView");
		m_model_render = factory_engine.Get< IVModelRender* >("VEngineModel");
		m_engine_trace = factory_engine.Get< IEngineTrace* >("EngineTraceClient");
		m_cvar = factory_vstdlib.Get< ICvar* >("VEngineCvar");
		m_material_system = factory_materialsystem.Get< IMaterialSystem* >("VMaterialSystem");
		m_game_event_manager = factory_engine.Get< IGameEventManager2* >("GAMEEVENTSMANAGER");
		m_physics_surface_props = factory_vphysics.Get< IPhysicsSurfaceProps* >("VPhysicsSurfaceProps");
		m_surface = factory_vgui.Get< ISurface* >("VGUI_Surface");
		m_move_helper = memory::scan< CMoveHelper* >("client_panorama.dll", "8B 0D ? ? ? ? 8B 45 ? 51 8B D4 89 02 8B 01", 2, 2u);
		m_view_render = memory::scan< CViewRender* >("client_panorama.dll", "A1 ? ? ? ? B9 ? ? ? ? C7 05 ? ? ? ? ? ? ? ? FF 10", 1, 1u);
		m_input = memory::scan< CInput* >("client_panorama.dll", "B9 ? ? ? ? F3 0F 11 04 24 FF 50 10", 1, 1u);
		m_globals = memory::scan< CGlobalVarsBase* >("client_panorama.dll", "A1 ? ? ? ? 0F 57 ED", 1, 2);
		m_direct_device = memory::scan< IDirect3DDevice9* >("shaderapidx9.dll", "A1 ? ? ? ? 50 8B 08 FF 51 0C", 1, 2);
	}
}