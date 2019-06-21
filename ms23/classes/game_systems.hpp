#pragma once
#include <Utils.hpp>

#include "../memory/local_types.hpp"

#include "filo.hpp"

void PrintGameSystems( bool print_null = false)
{
	for (int i = 0; i < e_game_system::k_number_of_game_systems; i++)
	{
		printf_s("%s\n", e_game_system(i).GetName());
		for (size_t j = 0; j < e_game_system_member::k_number_of_game_system_members; j++)
		{
			auto member = e_game_system(i).GetAddress(j);
			if (print_null)
				printf_s("[0x%08X, 0x%08X]: %s\n", member, *(size_t *)member, e_game_system_member(j).GetName());
			else if (*(size_t *)member)
				printf_s("[0x%08X, 0x%08X]: %s\n", member, *(size_t *)member, e_game_system_member(j).GetName());
		}
	}
}

void cheats_initialize_hook()
{
	printf_s("initialize hooked!\n");
}

void cheats_dispose_hook()
{
	printf_s("dispose hooked!\n");
}

void cheats_initialize_for_new_map_hook()
{
	printf_s("initialize_for_new_map hooked!\n");
}

void cheats_dispose_from_old_map_hook()
{
	printf_s("dispose_from_old_map hooked!\n");
}

inline void AddGameSystemsHooks(const char *name)
{
	if (ConfigManager.GetBool("Hooks", name))
	{	
		HookManager.AddHook({ 0x1301C0 }, &cheats_initialize_hook, "cheats_initialize");
		HookManager.AddHook({ 0x1301D0 }, &cheats_dispose_hook, "cheats_dispose");
		HookManager.AddHook({ 0x1301E0 }, &cheats_initialize_for_new_map_hook, "cheats_initialize_for_new_map");
		HookManager.AddHook({ 0x1301F0 }, &cheats_dispose_from_old_map_hook, "cheats_dispose_from_old_map");
	}
}

void AddGameSystemsPatches(const char *name)
{
	if (ConfigManager.GetBool("Patches", name))
	{

	}
}