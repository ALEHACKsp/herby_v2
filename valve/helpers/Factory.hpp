#pragma once
#include <unordered_map>
#include "valve/auto.hpp"

class Factory
{
	using factory_map_t = std::unordered_map< std::string, void* >;

public:
	Factory(const std::string& image_name);

public:
	template< typename T >
	inline T Get(const std::string& name)
	{
		auto factory = m_factory_map[name];
		return (T)factory;
	}

private:
	void CreateFactoryMap();

private:
	HMODULE m_image = nullptr;
	InterfaceReg* m_interface_array = nullptr;
	factory_map_t m_factory_map = { };
};