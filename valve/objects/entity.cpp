#include "valve/auto.hpp"

C_BaseEntity* C_BaseEntity::GetBaseEntity(int index)
{
	auto client_entity = csgo::m_client_entity_list->GetClientEntity(index);
	return (client_entity ? client_entity->GetBaseEntity() : nullptr);
}

