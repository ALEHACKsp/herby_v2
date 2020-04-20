#include "valve/auto.hpp"

C_BasePlayer* C_BasePlayer::GetBasePlayer(int index)
{
	auto base_entity = C_BaseEntity::GetBaseEntity(index);
	return ToBasePlayer(base_entity);
}

Vector C_BasePlayer::EyePosition()
{
	return m_vecOrigin() + m_vecViewOffset();
}

CUserCmd*& C_BasePlayer::m_pCurrentCommand()
{
	static auto offset = memory::scan< std::intptr_t >("client_panorama.dll", "89 BE ? ? ? ? E8 ? ? ? ? 85 FF", 2, 1u);
	return *(CUserCmd**)(this + offset);
}

C_CSPlayer* C_CSPlayer::GetPlayer(int index)
{
	auto base_entity = C_BaseEntity::GetBaseEntity(index);
	return ToCSPlayer(base_entity);
}

C_CSPlayer* C_CSPlayer::GetLocalPlayer()
{
	auto index = csgo::m_engine_client->GetLocalPlayer();
	return GetPlayer(index);
}

