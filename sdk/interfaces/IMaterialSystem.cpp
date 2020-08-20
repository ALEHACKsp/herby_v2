#include "sdk/interfaces/IMaterialSystem.hpp"

IMaterial* IMaterialSystem::CreateMaterial(const char* pMaterialName, KeyValues* pVMTKeyValues)
{
	return memory::Call<83, IMaterial*>(this, pMaterialName, pVMTKeyValues);
}

IMaterial* IMaterialSystem::FindMaterial(char const* pMaterialName, const char* pTextureGroupName, bool complain, const char* pComplainPrefix)
{
	return memory::Call<84, IMaterial*>(this, pMaterialName, pTextureGroupName, complain, pComplainPrefix);
}

MaterialHandle_t IMaterialSystem::FirstMaterial()
{
	return memory::Call<86, MaterialHandle_t>(this);
}
MaterialHandle_t IMaterialSystem::NextMaterial(MaterialHandle_t MatHandle)
{
	return memory::Call<87, MaterialHandle_t>(this, MatHandle);
}
MaterialHandle_t IMaterialSystem::InvalidMaterial()
{
	return memory::Call<88, MaterialHandle_t>(this);
}
IMaterial* IMaterialSystem::GetMaterial(MaterialHandle_t MatHandle)
{
	return memory::Call<89, IMaterial*>(this, MatHandle);
}