#include "valve/auto.hpp"


#define DUMP_NETVARS

#ifdef DUMP_NETVARS
#define IF_DUMPING(...) __VA_ARGS__
#else
#define IF_DUMPING(...)
#endif

IF_DUMPING(static FILE* s_fp;)

NetvarManager::NetvarManager()
{
	IF_DUMPING(fopen_s(&s_fp, "netvar_dump.txt", "w"););
	for (auto clazz = csgo::m_base_client->GetAllClasses(); clazz; clazz = clazz->m_pNext)
		if (clazz->m_pRecvTable)
			DumpRecursive(clazz->m_pNetworkName, clazz->m_pRecvTable, 0);
	IF_DUMPING(fclose(s_fp);)
}

void NetvarManager::DumpRecursive(const char* base_class, RecvTable* table, uint16_t offset)
{
	for (auto i = 0; i < table->m_nProps; ++i)
	{
		auto prop_ptr = &table->m_pProps[i];

		//Skip trash array items
		if (!prop_ptr || isdigit(prop_ptr->m_pVarName[0]))
			continue;

		//We dont care about the base class, we already know that
		if (strcmp(prop_ptr->m_pVarName, "baseclass") == 0)
			continue;

		if (prop_ptr->m_RecvType == DPT_DataTable &&
			prop_ptr->m_pDataTable != nullptr &&
			prop_ptr->m_pDataTable->m_pNetTableName[0] == 'D') // Skip shitty tables
		{
			DumpRecursive(base_class, prop_ptr->m_pDataTable, offset + prop_ptr->m_Offset);
		}

		char hash_name[256];

		strcpy_s(hash_name, base_class);
		strcat_s(hash_name, "->");
		strcat_s(hash_name, prop_ptr->m_pVarName);

		// Need to cast it to prevent FnvHash using the recursive hasher
		// which would hash all 256 bytes
		auto hash = fnv::hash_runtime(hash_name);
		const auto total_offset = std::uint16_t(offset + prop_ptr->m_Offset);

		IF_DUMPING(fprintf(s_fp, "%s\t0x%04X\t%s\n", base_class, total_offset, prop_ptr->m_pVarName);)

		m_props[hash] = { prop_ptr,total_offset };
	}
}