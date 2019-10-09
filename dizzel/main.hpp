#pragma once

#include <Utils.hpp>

#include "classes/classes.hpp"

float hotkey_sleep_delta = 1.f;

void PreInit()
{
	ConfigManager.Init(".\\bin\\dizzel.ini");

	//SubmitHooks();
	//SubmitPatches();
}
void Init()
{
	//Pointer::Base(0x369624).WriteFast(static_cast<float>(1 / 60));
	//Pointer::Base(0x38BAEC).WriteFast(3.5f);
}
void PostInit()
{
	HookManager.Apply();
	PatchManager.Apply();
}

void SomeFunc()
{
	printf_s("SomeFunc\n");
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
		AssignHotkey(VK_F1, &SomeFunc);
		
		Sleep((int)(hotkey_sleep_delta * 1000));

		SomeFunc();

		//ProtocolManager.Print();

		//printf_s("Resolution(%d, %d);\n", ProtocolManager.GetParam("width").Value.Int(), ProtocolManager.GetParam("height").Value.Int());
	}
}

std::vector<LPTHREAD_START_ROUTINE> gThreads = {
	(LPTHREAD_START_ROUTINE)&MainThread,
	(LPTHREAD_START_ROUTINE)&HotkeyThread
};