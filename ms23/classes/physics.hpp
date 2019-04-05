#pragma once

#include "../utils/Utils.hpp"

#include "../memory/local_types.hpp"


float GetNewPhysicsRate()
{
	auto gameGlobalsPtr = game_globals_get();
	if (!gameGlobalsPtr || gameGlobalsPtr->game_options.FrameLimit == 60)
		return 0.5f;
	return 30.0f / gameGlobalsPtr->game_options.FrameLimit;
}

void __fastcall edge_drop_hook(void* thisptr, void* unused, int a2, int a3, int a4, float* a5)
{
	Pointer(a3)(0xAC).WriteFast<float>(GetNewPhysicsRate());

	static auto sub_724BB0 = (void(__thiscall*)(void* thisptr, int a2, int a3, int a4, float* a5))(0x724BB0);
	sub_724BB0(thisptr, a2, a3, a4, a5);
}

inline void AddPhysicsHooks(const char *name)
{
	if (ConfigManager.GetBool("Hooks", name))
	{
		AddHook({ 0x324701 }, &edge_drop_hook, "edge_drop", HookFlags::IsCall);
	}
}

inline void AddPhysicsPatches(const char *name)
{
	if (ConfigManager.GetBool("Patches", name))
	{

	}
}