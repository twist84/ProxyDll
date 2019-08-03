#pragma once

#include "classes/classes.hpp"

#include "memory/tag_groups.hpp"
#include "memory/local_types.hpp"

float hotkey_sleep_delta = 1.f;

void PreInit()
{
	ConfigManager.Init(".\\bin\\ms23.ini");
	PreferenceManager.Init(".\\bin\\preferences.ini");
	PreferenceManagerAppname = "Preference";

	g_saves_path = ConfigManager.GetWString("Saves", "Path");
	UseStandardRendering(ConfigManager.GetBool("Rendering", "UseStandardRendering"));
	g_maps_path = ConfigManager.GetString("Maps", "Path")[0] != '\0' ? ConfigManager.GetString("Maps", "Path") : g_default_maps_path;
	g_use_default_system_ui_language = ConfigManager.GetBool("Language", "UseSystemDefault");
	g_new_system_ui_language = ConfigManager.GetLanguage("Language", "Selected");
	hotkey_sleep_delta = ConfigManager.GetFloat("Timing", "HotkeySleepDelta");
	update_debug_loading_type();

	Blam::StringIDCache::Instance.Load(g_maps_path);

	SubmitHooks();
	SubmitPatches();
}
void Init()
{



}
void PostInit()
{
	HookManager.Apply();
	PatchManager.Apply();

	PrintGPU();
	
	//PrintTagGroupEnum();
	//PrintGameSystems(/*e_game_system::_levels*/);
	g_vftables.AddEndAddress(0x069B1FFF);//->Print();
	//Blam::StringIDCache::Instance.PrintStrings();
}

void ExitGame()
{
	SetMemory<0x22B473C>(true); //g_game_is_exiting
}
void LaunchMainmenu()
{
	LaunchScenario("levels\\ui\\mainmenu\\mainmenu", e_scenario_type::_mainmenu);
}
void ForceLoad()
{
	auto scenario_path = ConfigManager.GetString("ForceLoad", "ScenarioPath");
	auto scenario_type = ConfigManager.GetInt("ForceLoad", "ScenarioType");
	auto game_type = ConfigManager.GetInt("ForceLoad", "GameType");
	auto team_game = ConfigManager.GetBool("ForceLoad", "TeamGame");
	auto time_limit = ConfigManager.GetInt("ForceLoad", "TimeLimit");
	auto respawn_time = ConfigManager.GetInt("ForceLoad", "RespawnTime");

	LaunchScenario(scenario_path, scenario_type, game_type, team_game, time_limit, respawn_time);
}

void MainThread()
{
	PreInit();
	Init();
	PostInit();
}
void HotkeyThread()
{
	while (true)
	{
		AssignHotkey(VK_F1, &ExitGame);

		AssignHotkey(VK_F2, &SetAllQualitySettingsLow);
		AssignHotkey(VK_F3, &SetAllQualitySettingsMedium);
		AssignHotkey(VK_F4, &SetAllQualitySettingsHigh);

		AssignHotkey(VK_F5, &update_debug_loading_type);

		AssignHotkey(VK_F6, &LaunchMainmenu);
		AssignHotkey(VK_F7, &ForceLoad);

		Sleep((int)(hotkey_sleep_delta * 1000));
	}
}

std::vector<LPTHREAD_START_ROUTINE> gThreads = {
	(LPTHREAD_START_ROUTINE)&MainThread,
	(LPTHREAD_START_ROUTINE)&HotkeyThread
};