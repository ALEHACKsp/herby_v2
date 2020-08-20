#pragma once

#include <windows.h>
#include <string>
#include <vector>
#include "shared/imgui/imgui.hpp"

namespace shared::option
{
	struct VisualData
	{

	};

	struct MiscData
	{
		
	};

	extern VisualData m_visual;
	extern MiscData m_misc;

	bool Create();
	void Destroy();
}