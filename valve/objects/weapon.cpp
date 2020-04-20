#include "valve/auto.hpp"

bool C_WeaponCSBase::IsFireTime()
{
	return csgo::m_globals->curtime >= m_flNextPrimaryAttack();
}

bool C_WeaponCSBase::IsSecondaryFireTime()
{
	return csgo::m_globals->curtime >= m_flNextSecondaryAttack();
}

bool C_WeaponCSBase::IsGun()
{
	auto data = GetCSWeaponData();

	if (!data)
		return false;

	return (data->WeaponType != WEAPONTYPE_KNIFE &&
		data->WeaponType != WEAPONTYPE_C4 &&
		data->WeaponType != WEAPONTYPE_GRENADE);
}

bool C_WeaponCSBase::IsPistol()
{
	auto data = GetCSWeaponData();
	return (data ? data->WeaponType == WEAPONTYPE_PISTOL : false);
}

CCSWeaponData* C_WeaponCSBase::GetCSWeaponData()
{
	using Fn = CCSWeaponData* (__thiscall*)(void*);
	static auto original = memory::scan< Fn >("client_panorama.dll", "55 8B EC 81 EC ? ? ? ? 53 8B D9 56 57 8D 8B");
	return original(this);
}