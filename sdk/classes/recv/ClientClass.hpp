#pragma once
#include "recv.hpp"
#include "sdk/interfaces/IClientEntity.hpp"

typedef IClientNetworkable* (*CreateClientClassFn)(int iEntNum, int iSerialNum);
typedef IClientNetworkable* (*CreateEventFn)();

class ClientClass
{
public:
	CreateClientClassFn		m_pCreateFn;
	CreateEventFn			m_pCreateEventFn;
	char* m_pNetworkName;
	RecvTable* m_pRecvTable;
	ClientClass* m_pNext;
	int		m_ClassID;
};