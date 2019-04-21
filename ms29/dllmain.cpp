#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NON_CONFORMING_SWPRINTFS
#include <iostream>
#include <fstream>
#include <thread>
#include <string>
#include <codecvt>

#include "utils/Console.hpp"
#include "utils/Utils.hpp"
#include "Patch.hpp"

#include "classes/camera.hpp"
#include "classes/tags.hpp"
#include "classes/ui.hpp"

#include "memory/local_types.hpp"

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
		ApplyHooks();
		ApplyPatches();
	}

	return AssignHotkeys(1.5);
}

BOOL InitInstance(HINSTANCE hModule)
{
	SetProcessDPIAware();
	DisableThreadLibraryCalls(hModule);

	Console::Resize(995, 520, 250, 250);

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)&MainThread, NULL, 0, NULL);

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

