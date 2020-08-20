#pragma once
#include "sdk/definitions.hpp"
#include "sdk/interfaces/IClientEntity.hpp"

class IClientEntityList
{
public:
	virtual IClientNetworkable* GetClientNetworkable(int Index) = 0;
	virtual IClientNetworkable* GetClientNetworkable(CBaseHandle hEnt) = 0;
	virtual IClientUnknown* GetClientUnknownFromHandle(CBaseHandle hEnt) = 0;
	virtual IClientEntity* GetClientEntity(int Index) = 0;
	virtual IClientEntity*	GetClientEntityFromHandle(CBaseHandle hEntity) = 0;
	virtual int                   NumberOfEntities(bool bIncludeNonNetworkable) = 0;
	virtual int                   GetHighestEntityIndex(void) = 0;
	virtual void                  SetMaxEntities(int MaxEntities) = 0;
	virtual int                   GetMaxEntities() = 0;
};
