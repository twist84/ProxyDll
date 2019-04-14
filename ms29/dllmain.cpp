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

	if (CanHook(ConfigManager.GetFloat("Delays", "PrintHookDelay"), ConfigManager.GetFloat("Delays", "HookDelay"), ConfigManager.GetInt("Delays", "HookDelayIncrement")))
	{
		ApplyHooks();
		ApplyPatches();
	}

	return AssignHotkeys(1.5);
}

//This is taken from http://www.cplusplus.com/forum/beginner/127593/
//Finding the user's screen resolution
int Width = GetSystemMetrics(SM_CXSCREEN);
int Height = GetSystemMetrics(SM_CYSCREEN);

//Assigning variables for MoveWindows parameters
int WindowWidth = 995;		//--- Used as a parameter to specify the width of the console window (MoveWindows int nWidth)
int WindowHeight = 520;		//--- Used as a parameter to specify the height of the console window (MoveWindows int nHeight)
int NewWidth = ((Width - WindowWidth)) / 2 - 250;		//--- Used as a parameter to center the console window horizontally (MoveWindows int x)
int NewHeight = ((Height - WindowHeight) / 2) + 250;		//--- Used as a parameter to center the console window vertically (MoveWindows int y)

//Getting the console window handle
HWND hWnd = GetConsoleWindow();

//Declaring the function
BOOL WINAPI MoveWindow(_In_ HWND hWnd, _In_ int NewWidth, _In_ int NewHeight, _In_ int WindowWidth, _In_ int WindowHeight, _In_ BOOL bRepaint);

BOOL InitInstance(HINSTANCE hModule)
{
	SetProcessDPIAware();
	DisableThreadLibraryCalls(hModule);

	MoveWindow(hWnd, NewWidth, NewHeight, WindowWidth, WindowHeight, TRUE);
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

