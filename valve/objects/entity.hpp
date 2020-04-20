#pragma once
#include "valve/auto.hpp"

class C_WeaponCSBase;

class C_BaseEntity : public IClientEntity
{
public:
	static C_BaseEntity* GetBaseEntity(int index);
public:
	NETVAR(int, m_iTeamNum, "CBaseEntity", "m_iTeamNum");
	NETVAR(float, m_flSimulationTime, "CBaseEntity", "m_flSimulationTime");
	NETVAR(CBaseHandle, m_hOwnerEntity, "CBaseEntity", "m_hOwnerEntity");
	NETVAR(Vector, m_vecOrigin, "CBaseEntity", "m_vecOrigin");
public:
	NETVAR_OFFSET(const matrix3x4_t, m_rgflCoordinateFrame, "CBaseEntity", "m_CollisionGroup", -0x0030);
};

class C_BaseAnimating : public C_BaseEntity
{
public:
	NETVAR(int, m_nHitboxSet, "CBaseAnimating", "m_nHitboxSet");
	NETVAR(int, m_nSequence, "CBaseAnimating", "m_nSequence");
	NETVAR(float, m_flCycle, "CBaseAnimating", "m_flCycle");
	PNETVAR(float*, m_flPoseParameter, "CBaseAnimating", "m_flPoseParameter");
};

class C_BaseAnimatingOverlay : public C_BaseAnimating
{
public:
};

class C_BaseCombatCharacter : public C_BaseAnimatingOverlay
{
public:
	C_WeaponCSBase* GetActiveWeapon()
	{
		auto handle = m_hActiveWeapon();
		return reinterpret_cast<C_WeaponCSBase*>(csgo::m_client_entity_list->GetClientEntityFromHandle(handle));
	}
public:
	NETVAR(CBaseHandle, m_hActiveWeapon, "CBaseCombatCharacter", "m_hActiveWeapon");
	NETVAR(float, m_flNextAttack, "CBaseCombatCharacter", "m_flNextAttack");
};