#pragma once
#include <iostream>

#include <Utils.hpp>
#include "../memory/local_types.hpp"

#include "preferences.hpp"
#include "print.hpp"


void SetFpsTarget(int16_t *FrameLimit, int fps)
{
	if (preferences.VSync.value.value && fps > 60)
		fps = 60;

	FrameLimit[0] = fps;
	SetMemory<0x165C83C>((float)fps);
}

void *NewGameOptions(s_game_options *data)
{
	if (data->ScenarioType.value == e_scenario_type::_campaign)
	{
		SetFpsTarget(&data->FrameLimit, 30);
		data->DifficultyLevel.value = e_difficulty_level::_easy;
		data->InsertionPoint.value = e_insertion_point::_mission_start;
		data->MetagameScoringOption.value = e_metagame_scoring_option::_off;
		data->MetagameEnabled = false;
		data->SurvivalModeEnabled = false;
	}
	else
	{
		SetFpsTarget(&data->FrameLimit, 120);
	}

	return (void *)data;
}

void *__cdecl game_options_get_hook()
{
	return NewGameOptions(game_options_get());
}

void CustomLevelLoadHook(s_game_options *data)
{
	//printf_s("Successfully hooked nullsub_97 at address 0x530440\n");
	//printf_s("nullsub_618A10: beginning map load\n");
}


int nullsub_618A10_hook(const char *a1, int a2)
{
	//printf_s("nullsub_618A10: \n");
	return 0;
}

int nullsub_618A20_hook(const char *a1, float *a2)
{
	//printf_s("nullsub_618A20: \n");
	return 0;
}

int nullsub_618A30_hook(const char *a1, const char *a2)
{
	//printf_s("nullsub_618A30: \n");
	return 0;
}

int nullsub_618A50_hook(const char *a1, const char *a2)
{
	//printf_s("nullsub_618A50: \n");
	return 0;
}

void PrintLevelInfo(s_levels *level, const char *type)
{
	//printf_s("level info: %s\n%ls\n%ls\n%s\n%s\n", type, level->map_name, level->map_description, level->map_path, level->map_image_path);
}

auto g_levels = GetStructure<s_levels_unknown>(0x189E2D4);
static const auto levels_try_and_get_by_map_id = (char(*)(int *, int, s_levels *))0x54C910; // todo: hook this also
char campaign_levels_try_and_get_by_map_id_hook(int map_id, s_levels *level)
{
	auto result = levels_try_and_get_by_map_id(g_levels->CampaignLevels, map_id, level);

	PrintLevelInfo(level, "campaign");
	return result;
}

char multiplayer_levels_try_and_get_by_map_id_hook(int map_id, s_levels *level)
{
	auto result = levels_try_and_get_by_map_id(g_levels->MultiplayerLevels, map_id, level);

	PrintLevelInfo(level, "multiplayer");
	return result;
}

int levels_get_default_map_id_hook()
{
	return 320; // guardian
}

bool initial_map_load_called = false;
int __cdecl GameOptions__LoadIntoGlobalGameOptions_hook(s_game_options *game_options)
{
	bool is_force_loaded = false;
	if (ConfigManager.GetBool("ForceLoad", "OnStartup") && !initial_map_load_called)
		is_force_loaded = true;

	initial_map_load_called = true;
	return game_options->LoadIntoGlobalGameOptions(is_force_loaded);
}

inline void SubmitLevelHooks(const char *name)
{
	if (ConfigManager.GetBool("Hooks", name))
	{
		HookManager.Submit({ 0x130440 }, &CustomLevelLoadHook, "CustomLevelLoad");
		HookManager.Submit({ 0x1322D0 }, &game_options_get_hook, "game_options_get");

		//HookManager.Submit({ 0x218A10 }, &nullsub_618A10_hook, "nullsub_618A10");
		//HookManager.Submit({ 0x218A20 }, &nullsub_618A20_hook, "nullsub_618A20");
		//HookManager.Submit({ 0x218A30 }, &nullsub_618A30_hook, "nullsub_618A30");
		//HookManager.Submit({ 0x218A50 }, &nullsub_618A50_hook, "nullsub_618A50"); // crashes, most likely wrong args

		HookManager.Submit({ 0x14CAB0 }, &campaign_levels_try_and_get_by_map_id_hook, "campaign_levels_try_and_get_by_map_id");
		HookManager.Submit({ 0x14CB00 }, &multiplayer_levels_try_and_get_by_map_id_hook, "multiplayer_levels_try_and_get_by_map_id");
		HookManager.Submit({ 0x14BCA0 }, &levels_get_default_map_id_hook, "levels_get_default_map_id");

		HookManager.Submit({ 0x166E70 }, &GameOptions__LoadIntoGlobalGameOptions_hook, "GameOptions::LoadIntoGlobalGameOptions");
	}
}

inline void SubmitLevelPatches(const char *name)
{
	if (ConfigManager.GetBool("Patches", name))
	{

	}
}