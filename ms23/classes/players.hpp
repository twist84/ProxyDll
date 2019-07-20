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

signed int player_mapping_get_hook()
{
	auto unknownB8 = (uint32_t *)thread_local_storage(thread_local_storage::_player_mapping).GetDefinition<uint8_t[0xEB]>(0xB8);
	signed int index = 0;
	while (*unknownB8 == -1)
	{
		++index;
		++unknownB8;
		if (index >= 4)
			return -1;
	}
	return index;
}
signed int player_mapping_iterator_hook(signed int _index)
{
	signed int index = _index == -1 ? 0 : _index + 1;
	if (index >= 4)
		return -1;

	auto unknownB8 = (uint32_t *)thread_local_storage(thread_local_storage::_player_mapping).GetDefinition<uint8_t[0xEB]>(0xB8 + (4 * index));
	while (*unknownB8 == -1)
	{
		++index;
		++unknownB8;
		if (index >= 4)
			return -1;
	}
	return index;
}

inline void SubmitPlayersHooks(const char *name)
{
	if (ConfigManager.GetBool("Hooks", name))
	{
		HookManager.Submit({ 0x136020 }, &player_datum_get_active_armor_loadout_customization_hook, "player_datum_get_active_armor_loadout_customization");

		HookManager.Submit({ 0x189A30 }, &player_mapping_get_hook, "player_mapping_get");
		HookManager.Submit({ 0x189EB0 }, &player_mapping_iterator_hook, "player_mapping_iterator");
	}
}

inline void SubmitPlayersPatches(const char *name)
{
	if (ConfigManager.GetBool("Patches", name))
	{

	}
}