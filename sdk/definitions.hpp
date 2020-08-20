#pragma once

#include <Windows.h>
#include <smmintrin.h>
#include <cstdint>
#include <cmath>
#include <limits>
#include <iostream>
#include <sstream>

using VPANEL = unsigned int;
using HFont = unsigned long;
using HScheme = unsigned long;
using HTexture = unsigned long;
using HCursor = unsigned long;
using HPanel = unsigned long;

static constexpr HPanel INVALID_PANEL = 0xFFFFFFFF;
static constexpr HFont INVALID_FONT = 0; // the value of an invalid font handle
static constexpr int MAX_CLIENTS = 64;

#include "enums.hpp"