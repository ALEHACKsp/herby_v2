#pragma once
#include "sdk/definitions.hpp"
#include "sdk/math/base.hpp"
#include "sdk/interfaces/IAppSystem.hpp"
#include "sdk/classes/CGlobalVarsBase.hpp"
#include "sdk/classes/recv/ClientClass.hpp"

class IBaseClientDLL
{
public:
	virtual int              Connect(CreateInterfaceFn appSystemFactory, CGlobalVarsBase* pGlobals) = 0;
	virtual int              Disconnect() = 0;
	virtual int              Init(CreateInterfaceFn appSystemFactory, CGlobalVarsBase* pGlobals) = 0;
	virtual void             PostInit() = 0;
	virtual void             Shutdown() = 0;
	virtual void             LevelInitPreEntity(char const* pMapName) = 0;
	virtual void             LevelInitPostEntity() = 0;
	virtual void             LevelShutdown() = 0;
	virtual ClientClass*	 GetAllClasses() = 0;
};