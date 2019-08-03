#pragma once
#include <Utils.hpp>

#include "../memory/local_types.hpp"

auto game_globals_get_campaign_difficulty_get_hook()
{
	auto game_globals = game_globals_get();
	if (game_globals->GameOptions.ScenarioType.value == e_scenario_type::_campaign)
		return game_globals->GameOptions.DifficultyLevel.value;
	return e_difficulty_level::_normal;
}

game_globals *game_globals_update_end_match_wait_time_hook(float a1)
{
	static auto game_time_ticks_per_second_delta_whole = (int(*)(float))(0x564BB0);
	auto game_globals = game_globals_get();
	if (game_globals->unknown24BE4 && game_globals->EndMatchWaitTime > 0)
		game_globals->EndMatchWaitTime += game_time_ticks_per_second_delta_whole(a1);
	return game_globals;
}

int game_globals_get_structure_bsp_index_hook()
{
	return game_globals_get()->StructureBspIndex;
}

game_globals *game_globals_set_playback_none_hook()
{
	auto game_globals = game_globals_get();
	game_globals->GameOptions.GamePlayback.value = e_game_playback::_none;
	return game_globals;
}

e_game_playback *__cdecl game_globals_get_playback_hook()
{
	return &game_globals_get()->GameOptions.GamePlayback;
}

e_game_playback __cdecl game_globals_set_playback_hook(e_game_playback a1)
{
	game_globals_get()->GameOptions.GamePlayback = a1;
	return a1;
}

int game_insertion_point_get_hook()
{
	auto game_globals = game_globals_get();
	if (game_globals->GameOptions.ScenarioType.value == e_scenario_type::_campaign)
		return game_globals->GameOptions.InsertionPoint.value;
	return 0;
}

game_globals *game_globals_set_cinematic_is_playing_false_hook()
{
	auto game_globals = game_globals_get();
	game_globals->CinematicIsPlaying = false;
	return game_globals;
}

game_globals *game_globals_set_cinematic_is_playing_true_hook()
{
	auto game_globals = game_globals_get();
	game_globals->CinematicIsPlaying = true;
	return game_globals;
}

s_progression game_globals_get_game_progression_hook()
{
	return game_progression_get();
}

char game_and_map_variant_initialize_after_load_hook()
{
	static auto game_options_verify_game_variant = (bool(*)(uint32_t *))(0x572920);
	static auto game_options_verify_map_variant = (bool(*)(uint32_t *))(0x586D00);
	auto game_globals = game_globals_get();
	game_options_verify_game_variant((uint32_t *)&game_globals->GameOptions.GameVariant);

	printf_s("initializing game_variant and map_variant: after_load\n");
	return game_options_verify_map_variant((uint32_t *)&game_globals->GameOptions.MapVariant);
}

uint32_t *active_camera_initialize_after_load_hook()
{
	static auto active_camera_initialize_after_load_internal = (uint32_t *(*)())(0x5937F0);

	printf_s("initializing active_camera: after_load\n");
	return active_camera_initialize_after_load_internal();
}

inline void SubmitGameGlobalsHooks(const char *name)
{
	if (ConfigManager.GetBool("Hooks", name))
	{
		HookManager.Submit({ 0x00530C70 }, &game_globals_get_campaign_difficulty_get_hook, "game_globals_get_campaign_difficulty");
		HookManager.Submit({ 0x00530FF0 }, &game_globals_update_end_match_wait_time_hook, "game_globals_update_end_match_wait_time");
		HookManager.Submit({ 0x00531150 }, &game_globals_get_structure_bsp_index_hook, "game_globals_get_structure_bsp_index");
		HookManager.Submit({ 0x00532280 }, &game_globals_set_playback_none_hook, "game_globals_set_playback_none");

		//HookManager.Submit({ 0x00532A80 }, &game_globals_get_playback_hook, "game_globals_get_playback");
		//HookManager.Submit({ 0x00532AA0 }, &game_globals_set_playback_hook, "game_globals_set_playback");

		HookManager.Submit({ 0x00532BB0 }, &game_globals_set_cinematic_is_playing_false_hook, "game_globals_set_cinematic_is_playing_false");
		HookManager.Submit({ 0x00532BD0 }, &game_globals_set_cinematic_is_playing_true_hook, "game_globals_set_cinematic_is_playing_true");
		HookManager.Submit({ 0x00532B90 }, &game_globals_get_game_progression_hook, "game_globals_get_game_progression");

		//HookManager.Submit({ 0x005326B0 }, &game_and_map_variant_initialize_after_load_hook, "game_and_map_variant_initialize_after_load");
		//HookManager.Submit({ 0x005917D0 }, &active_camera_initialize_after_load_hook, "active_camera_initialize_after_load");
	}
}

inline void SubmitGameGlobalsPatches(const char *name)
{
	if (ConfigManager.GetBool("Patches", name))
	{

	}
}