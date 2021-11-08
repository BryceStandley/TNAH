#pragma once
#define _CRT_SECURE_NO_WARNINGS

#pragma warning(push, 0) // Disable warnings for all files within the push/pop

#ifdef TNAH_PLATFORM_WINDOWS
#include <Windows.h>
#endif

// --- TNAH Precompiled Header File --- //
#include <memory>
#include <vector>
#include <string>
#include <array>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <random>

#include <fstream>



// --- 3rd Party headers --- //
#include <glm/glm.hpp>

#pragma warning(pop) // Disable warnings for all files within the push/pop

// --- Our Headers that don't change --- //
#include "TNAH/Core/Core.h"
#include "TNAH/Core/Ref.h"
#include "TNAH/Core/Log.h"
#include "TNAH/Core/Utility.h"
#include "TNAH/Core/Math.h"

