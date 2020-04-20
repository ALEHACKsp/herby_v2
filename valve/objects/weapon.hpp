#pragma once
#include "valve/auto.hpp"
class C_BaseCombatWeapon : public C_BaseEntity
{
public:
	NETVAR(int, m_iClip1, "CBaseCombatWeapon", "m_iClip1");
	NETVAR(int, m_iClip2, "CBaseCombatWeapon", "m_iClip2");
	NETVAR(int, m_iPrimaryAmmoType, "CBaseCombatWeapon", "m_iPrimaryAmmoType");
	NETVAR(int, m_iSecondaryAmmoType, "CBaseCombatWeapon", "m_iSecondaryAmmoType");
	NETVAR(ItemDefinitionIndex, m_iItemDefinitionIndex, "CBaseAttributableItem", "m_iItemDefinitionIndex");
	NETVAR(float, m_flNextPrimaryAttack, "CBaseCombatWeapon", "m_flNextPrimaryAttack");
	NETVAR(float, m_flNextSecondaryAttack, "CBaseCombatWeapon", "m_flNextSecondaryAttack");
};

class C_WeaponCSBase : public C_BaseCombatWeapon
{
public:
	bool IsFireTime();
	bool IsSecondaryFireTime();

	bool IsGun();
	bool IsPistol();

	CCSWeaponData* GetCSWeaponData();
public:
	NETVAR(float, m_fAccuracyPenalty, "CWeaponCSBase", "m_fAccuracyPenalty");
	NETVAR(float, m_flRecoilIndex, "CWeaponCSBase", "m_flRecoilIndex");
};