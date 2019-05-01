#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NON_CONFORMING_SWPRINTFS
#include <iostream>
#include <fstream>
#include <thread>
#include <string>
#include <codecvt>

#include <Console.hpp>
#include <Utils.hpp>

#include "classes/camera.hpp"
#include "classes/tags.hpp"
#include "classes/ui.hpp"

#include "memory/local_types.hpp"

void ReloadMap()
{
	if (!MapLoad.IsLoading())
		MapLoad.Reset();
}
void ForceLoad()
{
	g_game_options_base->SetScenarioPath(ConfigManager.GetString("ForceLoad", "ScenarioPath"));
	g_game_options_base->SetScenarioType(ConfigManager.GetInt("ForceLoad", "ScenarioType"));
	g_game_options_base->GameVariant_SetGameType(ConfigManager.GetInt("ForceLoad", "GameType"));
	g_game_options_base->GameVariant_SetTeamGame(ConfigManager.GetBool("ForceLoad", "TeamGame"));
	g_game_options_base->GameVariant_SetTimeLimit(ConfigManager.GetInt("ForceLoad", "TimeLimit"));
	g_game_options_base->GameVariant_SetRespawnTime(ConfigManager.GetInt("ForceLoad", "RespawnTime"));

	ReloadMap();
}

auto CanLoad = false;

int ForceLoadThread()
{
	while (!CanLoad)
	{
		Sleep(500);
	}

	while (true)
	{
		if (MapLoad.IsLoading())
			goto End;

		AssignHotkey(VK_F6, &ReloadMap);
		ConfigManager.CheckBoolAndRun("ForceLoad", "ReloadMap", &ReloadMap);
		AssignHotkey(VK_F7, &ForceLoad);
		ConfigManager.CheckBoolAndRun("ForceLoad", "LoadNew", &ForceLoad);

		End:
		Sleep(500);
	}
	return 0;
}

int AssignHotkeys(float sleep_time = 0.5)
{
	while (true)
	{
		//AssignHotkey(VK_F2, &SetAllQualitySettingsLow);

		Sleep((int)(sleep_time * 1000));
	}
	return 0;
}

bool CanHook(bool shouldPrint, double secondsToWait = 0.5, size_t incrementalStep = 50)
{
	int currentStep = 0;
	while (currentStep < secondsToWait * 1000)
	{
		currentStep += incrementalStep;
		Sleep(incrementalStep);
		if (shouldPrint)
			printf_s("can hook: %s\n", currentStep < (int)(secondsToWait * 1000) ? "false" : "true");
	}
	return true;
}

int MainThread()
{
	ConfigManager = { ".\\bin\\ms29.ini" };

	UnprotectModuleMemory();

	g_use_default_system_ui_language = ConfigManager.GetBool("Language", "UseSystemDefault");
	g_new_system_ui_language = ConfigManager.GetLanguage("Language", "Selected");

	AddCameraHooks("Camera");
	AddCameraPatches("Camera");
	AddTagsHooks("Tags");
	AddTagsPatches("Tags");
	AddUiHooks("Ui");
	AddUiPatches("Ui");

	if (CanHook(ConfigManager.GetBool("Delays", "PrintHookDelay"), ConfigManager.GetFloat("Delays", "HookDelay"), ConfigManager.GetInt("Delays", "HookDelayIncrement")))
	{
		HookManager.ApplyHooks();
		PatchManager.ApplyPatches();

		CanLoad = true;
	}

	return AssignHotkeys(1.5);
}

BOOL InitInstance(HINSTANCE hModule)
{
	SetProcessDPIAware();
	DisableThreadLibraryCalls(hModule);

	Console::Resize(995, 520, 250, 250);

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)&MainThread, NULL, 0, NULL);
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)&ForceLoadThread, NULL, 0, NULL);

	return true;
}

BOOL ExitInstance(HINSTANCE hModule)
{
	FreeLibrary(hModule);
	return true;
}

extern "C" BOOL WINAPI DllMain(HINSTANCE hModule, DWORD Reason, LPVOID Misc)
{
	switch (Reason)
	{
	case DLL_PROCESS_ATTACH: return InitInstance(hModule);
	case DLL_PROCESS_DETACH: return ExitInstance(hModule);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		return true;
	}
}

