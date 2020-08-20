#pragma once
#include "csgo/engine/net_prop_system.hpp"

class C_BaseEntity : public IClientEntity
{
public:
	static C_BaseEntity* GetBaseEntity(const int index);
	static C_BaseEntity* GetBaseEntityFromHandle(const ULONG& base_handle);

public:
	NET_PROP(int, m_iTeamNum, "DT_BaseEntity", "m_iTeamNum");

	NET_PROP(float, m_flSimulationTime, "DT_BaseEntity", "m_flSimulationTime");

	NET_PROP(Vector, m_vecOrigin, "DT_BaseEntity", "m_vecOrigin");

	NET_PROP(QAngle, m_angRotation, "DT_BaseEntity", "m_angRotation");

public:
	NET_PROP_EX(const matrix3x4_t, m_rgflCoordinateFrame, "DT_BaseEntity", "m_CollisionGroup", -0x0030);
};


class CCSWeaponInfo
{
public:
	PAD(0x0088);
	const char* m_hud_name = nullptr;
	const char* m_weapon_name = nullptr;
	PAD(0x0038);
	WeaponTypes m_type = WeaponTypes::WEAPONTYPE_UNKNOWN;
	PAD(0x0020);
	int m_damage = 0;
	float m_armor_ratio = 0.f;
	int m_bullets = 0;
	float m_penetration = 0.f;
	PAD(0x0008);
	float m_range = 0.f;
	float m_range_modifier = 0.f;
	PAD(0x0030);
	float m_inaccuracy_crouch = 0.f;
	PAD(0x0030);
	float m_inaccuracy_move = 0.f;
};

class C_BaseCombatWeapon : public C_BaseEntity
{
public:
	NET_PROP(short, m_iItemDefinitionIndex, "DT_BaseAttributableItem", "m_iItemDefinitionIndex");

	NET_PROP(int, m_iClip1, "DT_BaseCombatWeapon", "m_iClip1");
	NET_PROP(int, m_iClip2, "DT_BaseCombatWeapon", "m_iClip2");
	NET_PROP(int, m_iPrimaryAmmoType, "DT_BaseCombatWeapon", "m_iPrimaryAmmoType");
	NET_PROP(int, m_iSecondaryAmmoType, "DT_BaseCombatWeapon", "m_iSecondaryAmmoType");

	NET_PROP(float, m_flNextPrimaryAttack, "DT_BaseCombatWeapon", "m_flNextPrimaryAttack");
	NET_PROP(float, m_flNextSecondaryAttack, "DT_BaseCombatWeapon", "m_flNextSecondaryAttack");
};

class C_WeaponCSBase : public C_BaseCombatWeapon
{
public:
	bool IsFireTime();
	bool IsSecondaryFireTime();

	bool IsGun();
	bool IsPistol();

	CCSWeaponInfo* GetCSWeaponData();

public:
	NET_PROP(float, m_fAccuracyPenalty, "DT_WeaponCSBase", "m_fAccuracyPenalty");
	NET_PROP(float, m_flRecoilIndex, "DT_WeaponCSBase", "m_flRecoilIndex");
};

class C_BaseAnimating : public C_BaseEntity
{
public:
	bool GetBoneTransform(matrix3x4_t* bone_transform, const float time);
	bool GetBonePosition(matrix3x4_t* bone_transform, const int bone, Vector& output);

public:
	NET_PROP(bool, m_bClientSideAnimation, "DT_BaseAnimating", "m_bClientSideAnimation");
	NET_PROP(bool, m_bClientSideFrameReset, "DT_BaseAnimating", "m_bClientSideFrameReset");

	NET_PROP(int, m_nSequence, "DT_BaseAnimating", "m_nSequence");
	NET_PROP(int, m_nForceBone, "DT_BaseAnimating", "m_nForceBone");
	NET_PROP(int, m_nSkin, "DT_BaseAnimating", "m_nSkin");
	NET_PROP(int, m_nBody, "DT_BaseAnimating", "m_nBody");
	NET_PROP(int, m_nHitboxSet, "DT_BaseAnimating", "m_nHitboxSet");

	NET_PROP(float, m_flCycle, "DT_BaseAnimating", "m_flCycle");
	NET_PROP(float, m_flPlaybackRate, "DT_BaseAnimating", "m_flPlaybackRate");

	NET_PROP(Vector, m_vecForce, "DT_BaseAnimating", "m_vecForce");
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
		const auto base_entity = C_BaseEntity::GetBaseEntityFromHandle(m_hActiveWeapon());

		if (!base_entity)
			return nullptr;

		return reinterpret_cast<C_WeaponCSBase*>(base_entity);
	}

public:
	NET_PROP(ULONG, m_hActiveWeapon, "DT_BaseCombatCharacter", "m_hActiveWeapon");
	NET_PROP(float, m_flNextAttack, "DT_BaseCombatCharacter", "m_flNextAttack");
};

class C_BasePlayer : public C_BaseCombatCharacter
{
public:
	const Vector& EyePosition() const;

public:
	NET_PROP(char, m_lifeState, "DT_BasePlayer", "m_lifeState");

	NET_PROP(bool, m_bDucked, "DT_BasePlayer", "m_bDucked");
	NET_PROP(bool, m_bDucking, "DT_BasePlayer", "m_bDucking");
	NET_PROP(bool, m_bInDuckJump, "DT_BasePlayer", "m_bInDuckJump");
	NET_PROP(bool, m_bDrawViewmodel, "DT_BasePlayer", "m_bDrawViewmodel");

	NET_PROP(int, m_iAmmo, "DT_BasePlayer", "m_iAmmo");
	NET_PROP(int, m_nTickBase, "DT_BasePlayer", "m_nTickBase");
	NET_PROP(int, m_nWaterLevel, "DT_BasePlayer", "m_nWaterLevel");
	NET_PROP(int, m_iFOV, "DT_BasePlayer", "m_iFOV");
	NET_PROP(int, m_iDefaultFOV, "DT_BasePlayer", "m_iDefaultFOV");
	NET_PROP(int, m_iHealth, "DT_BasePlayer", "m_iHealth");
	NET_PROP(int, m_fFlags, "DT_BasePlayer", "m_fFlags");
	NET_PROP(int, m_iObserverMode, "DT_BasePlayer", "m_iObserverMode");

	NET_PROP(float, m_flFallVelocity, "DT_BasePlayer", "m_flFallVelocity");
	NET_PROP(float, m_flStepSize, "DT_BasePlayer", "m_flStepSize");
	NET_PROP(float, m_flFriction, "DT_BasePlayer", "m_flFriction");
	NET_PROP(float, m_flDeathTime, "DT_BasePlayer", "m_flDeathTime");
	NET_PROP(float, m_flLaggedMovementValue, "DT_BasePlayer", "m_flLaggedMovementValue");
	NET_PROP(float, m_flMaxspeed, "DT_BasePlayer", "m_flMaxspeed");

	NET_PROP(Vector, m_vecViewOffset, "DT_BasePlayer", "m_vecViewOffset[0]");
	NET_PROP(Vector, m_vecVelocity, "DT_BasePlayer", "m_vecVelocity[0]");
	NET_PROP(Vector, m_vecBaseVelocity, "DT_BasePlayer", "m_vecBaseVelocity");

	NET_PROP(QAngle, m_aimPunchAngle, "DT_BasePlayer", "m_aimPunchAngle");
	NET_PROP(QAngle, m_vecPunchAngle, "DT_BasePlayer", "m_vecPunchAngle");
	NET_PROP(QAngle, m_vecPunchAngleVel, "DT_BasePlayer", "m_vecPunchAngleVel");

	NET_PROP(ULONG, m_hLastWeapon, "DT_BasePlayer", "m_hLastWeapon");
	NET_PROP(ULONG, m_hGroundEntity, "DT_BasePlayer", "m_hGroundEntity");
	NET_PROP(ULONG, m_hObserverTarget, "DT_BasePlayer", "m_hObserverTarget");
};

class C_CSPlayer : public C_BasePlayer
{
public:
	static C_CSPlayer* GetLocalCSPlayer();
	static C_CSPlayer* GetCSPlayer(const int index);

public:
	NET_PROP(bool, m_bIsDefusing, "DT_CSPlayer", "m_bIsDefusing");

	NET_PROP(int, m_ArmorValue, "DT_CSPlayer", "m_ArmorValue");
	NET_PROP(int, m_iShotsFired, "DT_CSPlayer", "m_iShotsFired");
};

API_INLINE C_BasePlayer* ToBasePlayer(C_BaseEntity* base_entity)
{
	if (!base_entity)
		return nullptr;

	const auto player = (C_BasePlayer*)(base_entity);

	if (player->m_iHealth() <= 0)
		return nullptr;

	if (player->IsDormant())
		return nullptr;

	return player;
}

API_INLINE C_CSPlayer* ToCSPlayer(C_BaseEntity* base_entity)
{
	if (!base_entity)
		return nullptr;

	const auto player = (C_CSPlayer*)(base_entity);

	if (player->m_iHealth() <= 0)
		return nullptr;

	if (player->IsDormant())
		return nullptr;

	return player;
}