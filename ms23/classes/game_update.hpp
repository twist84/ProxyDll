#pragma once
#include <iostream>

#include <Utils.hpp>

#include "../memory/local_types.hpp"

#include "print.hpp"

bool __cdecl campaign_metagame_update_hook()
{
	bool enabled = false;
	return (enabled ? ((bool(__cdecl *)())0x60A4F0)() : false);
}

void __fastcall sub_6E59A0_hook(char *scoreboard, void *thisptr, uint32_t *handle, uint32_t event_type, short a4, uint32_t player_stat_type, char a6)
{
	return;
	((void(__thiscall *)(char *, void *, uint32_t *, uint32_t, short, uint32_t, char ))0x6E59A0)(scoreboard, thisptr, handle, event_type, a4, player_stat_type, a6);
}

inline void AddGameUpdateHooks(const char *name)
{
	//HookManager.Submit({ 0x1332E9, 0x1338E7 }, &campaign_metagame_update_hook, "campaign_metagame_update", HookFlags::IsCall);
	//HookManager.Submit({ 0x2E59A0 }, &sub_6E59A0_hook, "campaign_scoring_fix");
}

void AddGameUpdatePatches(const char *name)
{
	//PatchManager.Submit(&match_beginning_countdown, "match_beginning_countdown");
}