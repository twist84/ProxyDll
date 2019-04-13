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

int MainThread()
{
	ConfigManager = { ".\\bin\\ms29.ini" };

	printf_s("And...\nwe're in.\n");

	//ApplyHooks();
	//ApplyPatches();

	return 1;
}

BOOL InitInstance(HINSTANCE hModule)
{
	DisableThreadLibraryCalls(hModule);

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

