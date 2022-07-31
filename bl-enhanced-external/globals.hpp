#pragma once

#include "osmium/Memory/Process/process.hpp"
#include "bl_cheat.hpp"
#include "bl_overlay.hpp"

namespace Globals
{
	inline std::unique_ptr< process > g_pProcess = std::make_unique< process >();

	inline std::unique_ptr< bl_cheat > g_pCheat = std::make_unique< bl_cheat >();

	inline std::unique_ptr< bl_overlay > g_pOverlay = std::make_unique< bl_overlay >();
}
