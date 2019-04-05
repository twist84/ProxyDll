#pragma once
#include "../utils/Utils.hpp"

#include "../memory/local_types.hpp"

static auto g_game_globals_set_cinematic_is_playing_false = (int(*)())0x532BB0;
static auto g_game_globals_set_cinematic_is_playing_true = (int(*)())0x532BD0;

static auto g_cinematic_skip_start = (int(*)())0x67E950;
static auto g_cinematic_skip_stop = (int(*)())0x67E970;

static auto g_cinematic_start = (int(*)())0x67E990;
static auto g_cinematic_stop = (int(*)())0x67EA60;

inline void AddCinematicHooks(const char *name)
{
	if (ConfigManager.GetBool("Hooks", name))
	{
		//AddHook({  }, &_hook, "");
	}
}

inline void AddCinematicPatches(const char *name)
{
	if (ConfigManager.GetBool("Patches", name))
	{
		//AddPatch({  }, &_patch, "");
	}
}