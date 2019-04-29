#pragma once
#include <iostream>

#include <Utils.hpp>

#include "../memory/local_types.hpp"

s_content_catalogue *content_catalogue_get_hook(int a1)
{
	//printf_s("Getting content_catalogue[%d] data\n", a1);
	return GetStructure<s_content_catalogue>(0x240A348, a1);
}

s_player_profile *c_player_profile__get_hook(int a1)
{
	//printf_s("Getting player[%d] profile data\n", a1);
	return GetStructure<s_player_profile>(0x524EC48, a1);
}

/*
.text:00530620 ; char __cdecl game_award_level_complete_achievements()
.text:0056D480 ; void __cdecl achievements::sub_56D480(int local_user_index, e_achievement achievement_index)
.text:0056FE00 ; char __cdecl achievements::sub_56FE00(int local_user_index, int a2)
.text:0056FF00 ; void __cdecl achievements::sub_56FF00(int local_user_index, e_achievement achievement_index)
.text:00606940 ; signed int __cdecl achievement_grant_level(int local_user_index, int map_id, int campaign_difficulty)
.text:00696210 ; int __cdecl achievements::sub_696210(int player_datum, e_achievement achievement_index)
.text:00696310 ; int __cdecl achievement_globals_get_achievement_information_block_get_unkC(e_achievement achievement_index)
.text:00696410 ; char __cdecl achievement_grant_vidmaster(int local_user_index, e_achievement achievement_index)
.text:006964C0 ; _DWORD *__cdecl achievement_globals_get_achievement_information_block(e_achievement achievement_index)
.text:00696510 ; char __cdecl achievements::sub_696510(int player_datum, int unit, int classification)
.text:00696550 ; char __cdecl achievements::sub_696550(int player_datum, int a2)
.text:006965A0 ; char __cdecl achievements::sub_6965A0(int player_datum, int medal_index)
.text:00696640 ; void __cdecl achievements::sub_696640(int player_datum)
.text:00696680 ; char __cdecl achievements::sub_696680(int player_index, e_achievement achievement_index, int a3)
.text:00696750 ; void __cdecl achievement_post_chud_progression(int a1, int achievement_string_id, int a3)
.text:00696820 ; char __cdecl game_progression_achievement_sub_696820(unsigned int local_user_index, e_achievement achievement_index)
.text:00A95950 ; datum_handle __cdecl achievements::chud::sub_A95950(datum_handle chud_handle, e_achievement achievement_index, int a3)
.text:00A96BB0 ; int __thiscall achievements::chud::sub_A96BB0(s_chud_persistent_user_data_offset_29D4 *this, e_achievement achievement_index, int a3, float a4)
.text:014E2140 ; _DWORD *__thiscall c_achievement_write_overlapped_task::sub_14E2140(_DWORD *thisptr, int a2, int a3)
.text:014E2180 ; _DWORD *__thiscall c_achievements_enumerate_overlapped_task::sub_14E2180(_DWORD *thisptr, int a2, int a3)
.text:014E2200 ; void *__thiscall c_achievement_write_overlapped_task::vftable00(void *thisptr, char a2)
.text:014E2230 ; void *__thiscall c_achievements_enumerate_overlapped_task::vftable00(void *thisptr, char a2)
.text:014E2260 ; signed int __cdecl achievements_get_index_from_string_id(int achievement_string_id)
.text:014E2290 ; int __cdecl achievements::sub_14E2290(e_achievement achievement_index)
.text:014E22B0 ; int __cdecl achievement_score_get(e_achievement achievement_index)
.text:014E22D0 ; void __cdecl achievement_dispose()
.text:014E2320 ; void __cdecl __noreturn achievement_initialize()
.text:014E2450 ; void __thiscall c_achievement_write_overlapped_task::vftable06(_DWORD *thisptr)
.text:014E2480 ; char __thiscall c_achievements_enumerate_overlapped_task::vftable06(_DWORD *thisptr)
.text:014E24B0 ; char *__cdecl controller_achievement_state_get_string(unsigned int controller_achievement_state)
.text:014E24D0 ; signed int __cdecl achievements::sub_14E24D0(int local_user_index, int achievement_index, char a3)
.text:014E25C0 ; void __thiscall c_achievements_enumerate_overlapped_task::vftable05(_DWORD *thisptr, int a2, int a3, int a4)
.text:014E2630 ; bool __cdecl achievements::sub_14E2630(int local_user_index, int achievement_index, char a3)
.text:014E2650 ; signed int __cdecl achievements::sub_14E2650(int local_user_index, e_achievement achievement_index)
.text:014E2690 ; signed int __cdecl achievements::sub_14E2690(int local_user_index, int achievement_string_id)
.text:014E26F0 ; bool __cdecl c_player_profile::get::achievement(int local_user_index, e_achievement achievement_index)
.text:014E2740 ; bool __cdecl c_player_profile::has::achievement(int local_user_index, int achievement_string_id)
.text:014E2780 ; const char *__cdecl c_achievement_write_overlapped_task::get_name()
.text:014E2790 ; const char *__cdecl c_achievements_enumerate_overlapped_task::get_name()
.text:014E27E0 ; bool __cdecl achievements_sub_14E27E0(datum_handle object_handle, int achievement_string_id)
.text:014E2860 ; char __cdecl achievement_grant_to_player(datum_handle a1, int achievement_string_id)
.text:014E28D0 ; BOOL __cdecl achievement_grant_to_all_players(int achievement_string_id)
.text:014E2980 ; int __thiscall c_achievement_write_overlapped_task::vftable02(int *thisptr, int a2)
.text:014E29D0 ; int __thiscall c_achievements_enumerate_overlapped_task::vftable02(int *thisptr, int a2)
.text:014E2A20 ; void __stdcall c_achievements_enumerate_overlapped_task::vftable04(int a1)
*/

signed int __cdecl achievement_grant_level_hook(int local_user_index, int map_id, int campaign_difficulty)
{
	e_achievement achievement;
	return achievement.grant_level(local_user_index, map_id, campaign_difficulty);
}

signed int __cdecl achievements_get_index_from_string_id_hook(int achievement_string_id)
{
	e_achievement achievement;
	return achievement.get_from_string_id(achievement_string_id);
}

const char *__cdecl controller_achievement_state_to_string_hook(e_controller_achievement_state controller_achievement_state)
{
	const char *result = "";
	if (controller_achievement_state.value < e_controller_achievement_state::k_number_of_controller_achievement_states)
		result = controller_achievement_state.GetName();

	printf_s("controller achievement state: %s\n", result);
	return result;
}

inline void AddPlayerProfileHooks(const char *name)
{
	if (ConfigManager.GetBool("Hooks", name))
	{
		HookManager.AddHook({ 0x1A5600 }, &content_catalogue_get_hook, "content_catalogue::get");
		HookManager.AddHook({ 0x67CD50 }, &c_player_profile__get_hook, "c_player_profile::get");
		HookManager.AddHook({ 0x10E2260 }, &achievements_get_index_from_string_id_hook, "achievements_get_index_from_string_id");
		HookManager.AddHook({ 0x10E24B0 }, &controller_achievement_state_to_string_hook, "controller_achievement_state_to_string");
	}
}

inline void AddPlayerProfilePatches(const char *name)
{
	if (ConfigManager.GetBool("Patches", name))
	{

	}
}