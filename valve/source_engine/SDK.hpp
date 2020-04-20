#pragma once

#include <cassert>
#include <algorithm>
#include <cfloat>
#include <d3d9.h>
#include "Definitions.hpp"

#include "CRC.hpp"
#include "Vector.hpp"
#include "Vector2D.hpp"
#include "Vector4D.hpp"
#include "QAngle.hpp"
#include "CHandle.hpp"
#include "CGlobalVarsBase.hpp"
#include "ClientClass.hpp"
#include "Color.hpp"
#include "IBaseClientDll.hpp"
#include "IClientEntity.hpp"
#include "IClientEntityList.hpp"
#include "IClientNetworkable.hpp"
#include "IClientRenderable.hpp"
#include "IClientThinkable.hpp"
#include "IClientUnknown.hpp"
#include "IPanel.hpp"
#include "ISurface.hpp"
#include "IMaterialSystem.hpp"
#include "IVEngineClient.hpp"
#include "IVModelInfo.hpp"
#include "IVRenderView.hpp"
#include "IVModelRender.hpp"
#include "IVEffects.hpp"
#include "IEngineTrace.hpp"
#include "IEngineSound.hpp"
#include "PlayerInfo.hpp"
#include "Recv.hpp"
#include "VMatrix.hpp"
#include "IClientMode.hpp"
#include "CInput.hpp"
#include "ICvar.hpp"
#include "IGameEvents.hpp"
#include "Convar.hpp"
#include "CCSWeaponData.hpp"
#include "GameMovement.hpp"
#include "IPhysicsSurfaceProps.hpp"

namespace csgo
{
	inline IBaseClientDLL* m_base_client = nullptr;
	inline IClientEntityList* m_client_entity_list = nullptr;
	inline CGameMovement* m_game_movement = nullptr;
	inline CPrediction* m_prediction = nullptr;
	inline IVEngineClient* m_engine_client = nullptr;
	inline IVModelInfoClient* m_model_info_client = nullptr;
	inline IVRenderView* m_render_view = nullptr;
	inline IVModelRender* m_model_render = nullptr;
	inline IEngineTrace* m_engine_trace = nullptr;
	inline ICvar* m_cvar = nullptr;
	inline IMaterialSystem* m_material_system = nullptr;
	inline CMoveHelper* m_move_helper = nullptr;
	inline CViewRender* m_view_render = nullptr;
	inline CInput* m_input = nullptr;
	inline IGameEventManager2* m_game_event_manager = nullptr;
	inline IPhysicsSurfaceProps* m_physics_surface_props = nullptr;
	inline ISurface* m_surface = nullptr;
	inline CGlobalVarsBase* m_globals = nullptr;
	inline IDirect3DDevice9* m_direct_device = nullptr;
	void Initialize();
}