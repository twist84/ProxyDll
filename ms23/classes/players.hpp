#pragma once
#include <Utils.hpp>

#include "../memory/local_types.hpp"

struct s_player_datum
{
	uint8_t unknown0[0x2F08];

	s_player_datum(uint8_t *a1)
	{
		memset(this, *a1, 0x2F08);
	}

	uint8_t *__cdecl player_datum_get_active_armor_loadout_customization()
	{
		return (uint8_t *)(this + 0x20 * *(uint32_t *)(this + 0x4C) + 0x738);
	}
};

uint8_t *__cdecl player_datum_get_active_armor_loadout_customization_hook(uint8_t *player_datum)
{
	return (uint8_t *)((player_datum + 0x738) + (0x20 * *(uint32_t *)(player_datum + 0x4C)));
}

inline void SubmitPlayersHooks(const char *name)
{
	if (ConfigManager.GetBool("Hooks", name))
	{
		HookManager.Submit({ 0x136020 }, &player_datum_get_active_armor_loadout_customization_hook, "player_datum_get_active_armor_loadout_customization");
	}
}

inline void SubmitPlayersPatches(const char *name)
{
	if (ConfigManager.GetBool("Patches", name))
	{

	}
}