#pragma once
#include <Utils.hpp>

#include "../memory/local_types.hpp"

#include "filo.hpp"

void PrintGameSystems(int game_system = -1, bool print_noref = false, bool print_badref = false, bool print_hooks = true)
{
	for (int i = 0; i < e_game_system::k_number_of_game_systems; i++)
	{
		if (game_system == -1 || game_system == i)
		{
			auto system = e_game_system(i);
			if ((print_noref || system.AnyMemberHasRef()) && (print_badref || system.AnyMemberRefIsGood()) && (print_hooks && system.AnyMemberRefIsHook()))
				printf_s("%s\n", system.GetName());
			for (size_t j = 0; j < e_game_system_member::k_number_of_game_system_members; j++)
			{
				auto state = !system.MemberHasRef(j) ? "NonRef" : system.MemberRefIsGood(j) ? system.MemberRefIsHook(j) ? "IsHook" : "IsGood" : "IsNull";
				if ((print_noref || system.MemberHasRef(j)) && (print_badref || system.MemberRefIsGood(j)) && (print_hooks && system.MemberRefIsHook(j)))
					printf_s("[0x%08X, 0x%08X, %s]: %s\n", system.GetMember(j), system.MemberGetRef(j), state, e_game_system_member(j).GetName());
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