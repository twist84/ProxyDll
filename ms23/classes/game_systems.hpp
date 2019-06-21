#pragma once
#include <Utils.hpp>

#include "../memory/local_types.hpp"

#include "filo.hpp"

void PrintGameSystems(int game_system = -1, bool print_null = false)
{
	for (int i = 0; i < e_game_system::k_number_of_game_systems; i++)
	{
		if (game_system == -1 || game_system == i)
		{
			printf_s("%s\n", e_game_system(i).GetName());
			for (size_t j = 0; j < e_game_system_member::k_number_of_game_system_members; j++)
			{
				auto member = e_game_system(i).GetMember(j);
				if (print_null || *(size_t *)member)
					printf_s("[0x%08X, 0x%08X]: %s\n", member, *(size_t *)member, e_game_system_member(j).GetName());
			}
		}
	}
}

inline void AddGameSystemsHooks(const char *name)
{
	if (ConfigManager.GetBool("Hooks", name))
	{

	}
}

void levels_initialize()
{
	printf_s("levels_initialize hooked!\n");
	((void(*)())0x0054C110)();
}
void levels_dispose()
{
	printf_s("levels_dispose hooked!\n");
	((void(*)())0x0054ADF0)();
}
void levels_initialize_for_new_map()
{
	printf_s("levels_initialize_for_new_map hooked!\n");
	((void(*)())0x0054C2D0)();
}
void levels_dispose_from_old_map()
{
	printf_s("levels_dispose_from_old_map hooked!\n");
	((void(*)())0x0054AEA0)();
}
void levels_game_system()
{
	e_game_system(e_game_system::_levels).ReplaceMember(e_game_system_member::_initialize, &levels_initialize);
	e_game_system(e_game_system::_levels).ReplaceMember(e_game_system_member::_dispose, &levels_dispose);
	e_game_system(e_game_system::_levels).ReplaceMember(e_game_system_member::_initialize_for_new_map, &levels_initialize_for_new_map);
	e_game_system(e_game_system::_levels).ReplaceMember(e_game_system_member::_dispose_from_old_map, &levels_dispose_from_old_map);
}

void AddGameSystemsPatches(const char *name)
{
	if (ConfigManager.GetBool("Patches", name))
	{
		PatchManager.AddPatch(&levels_game_system, "levels_game_system");
	}
}