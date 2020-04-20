#pragma once
#include <Windows.h>
#include <Psapi.h>
#include "valve/auto.hpp"
namespace Utils
{
	void FlashTaskbarIcon();
	bool WorldToScreen(const Vector& origin, Vector& screen);
}