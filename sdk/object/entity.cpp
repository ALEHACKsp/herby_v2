#include "entity.hpp"
#include "csgo/engine.hpp"

C_BaseEntity* C_BaseEntity::GetBaseEntity(const int index)
{
	const auto client_entity = csgo::m_client_entity_list->GetClientEntity(index);
	return (C_BaseEntity*)(client_entity);
}

C_BaseEntity* C_BaseEntity::GetBaseEntityFromHandle(const ULONG& base_handle)
{
	const auto client_entity = csgo::m_client_entity_list->GetClientEntityFromHandle(base_handle);
	return (C_BaseEntity*)(client_entity);
}

bool C_BaseAnimating::GetBoneTransform(matrix3x4_t* bone_transform, const float time)
{
	const auto client_renderable = GetClientRenderable();

	if (!client_renderable)
		return false;

	return client_renderable->SetupBones(bone_transform, 128, 0x0100, time);
}

bool C_BaseAnimating::GetBonePosition(matrix3x4_t* bone_transform, const int bone, Vector& output)
{
	if (bone_transform)
	{
		for (auto i = 0; i < 3; i++)
			output[i] = bone_transform[bone][i][3];
	}

	return (!output.IsZero() && output.IsValid());
}

const Vector& C_BasePlayer::EyePosition() const
{
	return (m_vecOrigin() + m_vecViewOffset());
}

C_CSPlayer* C_CSPlayer::GetLocalCSPlayer()
{
	const auto base_entity = C_BaseEntity::GetBaseEntity(csgo::m_engine_client->GetLocalPlayer());
	return ToCSPlayer(base_entity);
}

C_CSPlayer* C_CSPlayer::GetCSPlayer(const int index)
{
	const auto base_entity = C_BaseEntity::GetBaseEntity(index);
	return ToCSPlayer(base_entity);
}

bool C_WeaponCSBase::IsFireTime()
{
	return (csgo::m_globals->cur_time >= m_flNextPrimaryAttack());
}

bool C_WeaponCSBase::IsSecondaryFireTime()
{
	return (csgo::m_globals->cur_time >= m_flNextSecondaryAttack());
}

bool C_WeaponCSBase::IsGun()
{
	auto data = GetCSWeaponData();

	if (!data)
		return false;

	return (data->m_type != WeaponTypes::WEAPONTYPE_KNIFE &&
		data->m_type != WeaponTypes::WEAPONTYPE_C4 &&
		data->m_type != WeaponTypes::WEAPONTYPE_GRENADE);
}

bool C_WeaponCSBase::IsPistol()
{
	auto data = GetCSWeaponData();
	return (data ? data->m_type == WeaponTypes::WEAPONTYPE_PISTOL : false);
}

CCSWeaponInfo* C_WeaponCSBase::GetCSWeaponData()
{
	static auto procedure = memory::scan< CCSWeaponInfo* (__thiscall*)(void*) >("client.dll", "55 8B EC 81 EC ? ? ? ? 53 8B D9 56 57 8D 8B");
	return procedure(this);
}
