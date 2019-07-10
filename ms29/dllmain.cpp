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
	MapInfo.Reset();

	printf_s("reloading %s...\n", MapInfo.GameOptionsPtr->ScenarioPath);
}
void ForceLoad()
{
	MapInfo.ChangeMap(ConfigManager.GetString("ForceLoad", "ScenarioPath"));
	MapInfo.ChangeMapType(ConfigManager.GetInt("ForceLoad", "ScenarioType"));
	MapInfo.ChangeGameType(ConfigManager.GetInt("ForceLoad", "GameType"));
	MapInfo.ChangeTeamGame(ConfigManager.GetBool("ForceLoad", "TeamGame"));
	MapInfo.ChangeTimeLimit(ConfigManager.GetInt("ForceLoad", "TimeLimit"));
	MapInfo.ChangeRespawnTime(ConfigManager.GetInt("ForceLoad", "RespawnTime"));

	MapInfo.Reset();

	printf_s("loading %s...\n", MapInfo.GameOptionsPtr->ScenarioPath);
}

bool Loaded = false;
int ForceLoadThread()
{
	while (!ConfigManager.IsInitialized())
		Sleep(250);
	if (ConfigManager.GetBool("ForceLoad", "LoadOnStart"))
		ConfigManager.SetBool("ForceLoad", "LoadNew", true);

	while (true)
	{
		if (!Loaded || MapInfo.IsLoading())
			goto End;

		AssignHotkey(VK_F6, &ReloadMap);
		if (ConfigManager.CheckBoolAndRun("ForceLoad", "ReloadMap", &ReloadMap))
			goto End;
		AssignHotkey(VK_F7, &ForceLoad);
		if (ConfigManager.CheckBoolAndRun("ForceLoad", "LoadNew", &ForceLoad))
			goto End;

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
	ConfigManager.Init(".\\bin\\ms29.ini");

	UnprotectModuleMemory();

	g_use_default_system_ui_language = ConfigManager.GetBool("Language", "UseSystemDefault");
	g_new_system_ui_language = ConfigManager.GetLanguage("Language", "Selected");

	SubmitCameraHooks("Camera");
	SubmitCameraPatches("Camera");
	SubmitTagsHooks("Tags");
	SubmitTagsPatches("Tags");
	SubmitUiHooks("Ui");
	SubmitUiPatches("Ui");

	if (CanHook(ConfigManager.GetBool("Delays", "PrintHookDelay"), ConfigManager.GetFloat("Delays", "HookDelay"), ConfigManager.GetInt("Delays", "HookDelayIncrement")))
	{
		HookManager.Apply();
		PatchManager.Apply();

		Loaded = true;
	}

	return AssignHotkeys(1.5);
}

BOOL InitInstance(HINSTANCE hModule)
{
	SetProcessDPIAware();
	DisableThreadLibraryCalls(hModule);

	Console::Resize(995, 520, -250, 250);

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

