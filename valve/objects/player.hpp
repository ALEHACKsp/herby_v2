#pragma once
#include "valve/auto.hpp"
class C_BasePlayer;

inline C_BasePlayer* ToBasePlayer(C_BaseEntity* base_entity)
{
	if (!base_entity)
		return nullptr;

	return reinterpret_cast<C_BasePlayer*>(base_entity);
}

inline C_CSPlayer* ToCSPlayer(C_BaseEntity* base_entity)
{
	return reinterpret_cast<C_CSPlayer*>(ToBasePlayer(base_entity));
}

class C_BasePlayer : public C_BaseCombatCharacter
{
public:
	static C_BasePlayer* GetBasePlayer(int index);

public:
	Vector EyePosition();

	CUserCmd*& m_pCurrentCommand();

public:
	NETVAR(char, m_lifeState, "CBasePlayer", "m_lifeState");
	NETVAR(int, m_fFlags, "CBasePlayer", "m_fFlags");
	NETVAR(int, m_iHealth, "CBasePlayer", "m_iHealth");
	NETVAR(int, m_nTickBase, "CBasePlayer", "m_nTickBase");
	NETVAR(Vector, m_vecVelocity, "CBasePlayer", "m_vecVelocity[0]");
	NETVAR(Vector, m_vecViewOffset, "CBasePlayer", "m_vecViewOffset[0]");
	NETVAR(QAngle, m_aimPunchAngle, "CBasePlayer", "m_aimPunchAngle");
	NETVAR(QAngle, m_viewPunchAngle, "CBasePlayer", "m_viewPunchAngle");
	NETVAR_OFFSET(QAngle, v_angle, "CBasePlayer", "deadflag", 0x04);
};

class C_CSPlayer : public C_BasePlayer
{
public:
	static C_CSPlayer* GetPlayer(int index);
	static C_CSPlayer* GetLocalPlayer();
public:
	NETVAR(bool, m_bIsDefusing, "CCSPlayer", "m_bIsDefusing");
	NETVAR(bool, m_bHasHelmet, "CCSPlayer", "m_bHasHelmet");
	NETVAR(bool, m_bHasHeavyArmor, "CCSPlayer", "m_bHasHeavyArmor");
	NETVAR(int, m_ArmorValue, "CCSPlayer", "m_ArmorValue");
	NETVAR(int, m_iShotsFired, "CCSPlayer", "m_iShotsFired");
	NETVAR(float, m_flFlashMaxAlpha, "CCSPlayer", "m_flFlashMaxAlpha");
	NETVAR(float, m_flLowerBodyYawTarget, "CCSPlayer", "m_flLowerBodyYawTarget");
	NETVAR(QAngle, m_angEyeAngles, "CCSPlayer", "m_angEyeAngles[0]");
};