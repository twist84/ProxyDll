#pragma once

#include <Utils.hpp>

#include "../memory/local_types.hpp"


void __fastcall edge_drop_hook(void *thisptr, void *unused, int a2, int a3, int a4, float *a5)
{
	Pointer(a3)(0xAC).WriteFast<float>(game_globals_get()->GetPhysicsRateFromFrameLimit());
	((void(__thiscall*)(void *thisptr, int a2, int a3, int a4, float *a5))0x724BB0)(thisptr, a2, a3, a4, a5);
}

inline void AddPhysicsHooks(const char *name)
{
	if (ConfigManager.GetBool("Hooks", name))
	{
		HookManager.AddHook({ 0x324701 }, &edge_drop_hook, "edge_drop_fix", HookFlags::IsCall);
	}
}

inline void AddPhysicsPatches(const char *name)
{
	if (ConfigManager.GetBool("Patches", name))
	{

	}
}