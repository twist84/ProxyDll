#pragma once
#include <iostream>

#include <Utils.hpp>

#include "../memory/local_types.hpp"

bool main_game_change_immediate_hook(s_game_options *data)
{
	if (!((bool(*)(s_game_options *))0x566EF0)(data))
		return false;

	return true;
}

void maps_store_map_info_hook(uint8_t *mapinfo, char a2, char *mapsPath, char a4)
{
	*reinterpret_cast<uint32_t*>(mapinfo + 0x111C) = 0x08081002;
	*reinterpret_cast<uint32_t*>(mapinfo + 0x1120) = 0x08080808;
	*reinterpret_cast<uint32_t*>(mapinfo + 0x1124) = 0x08080808;
	((int(__cdecl *)(uint8_t*, char, char *, char))0x0054A6C0)(mapinfo, a2, mapsPath, a4);
}

void game__game_engine__start_game_hook()
{
	((void(*)())0x551590)();

	auto engineGlobalsPtr = GetMainTls(0x48);
	if (!engineGlobalsPtr)
		return;

	auto engineGobals = engineGlobalsPtr[0];
	engineGobals(0x8).WriteFast(engineGobals(0x4).Read<uint32_t>());
}

void c_stop_watch__start_hook()
{
	// add tick functions here
	((void(*)())0x5547F0)();
}
bool __cdecl map_file_validation_hook(s_map_data *map_data)
{
	return true;
}
int __cdecl sub_52CCC0_hook(int a1, int a2, int a3)
{
	return *(uint32_t *)0x22AB010 + *(uint32_t *)0x22AB00C;
}
char __cdecl sub_508F80_hook(int a1, int a2)
{
	return true;
}
char __cdecl compute_blf_hash_hook(uint8_t *content_header, int size, char a3, int a4)
{
	return false;
}

char *__cdecl map_name_from_path(char *a1)
{
	char *v1; // eax
	char *result; // eax

	v1 = strrchr(a1, '\\');
	if (v1)
		result = v1 + 1;
	else
		result = a1;
	return result;
}

bool __cdecl sub_AC3900_hook(int content_type, e_map_id map_id, char *DstBuf)
{
	if (map_id.value == -1)
		return 0;

	s_levels level;
	char scenario_image_path[256] = {};
	if (campaign_levels_try_and_get_by_map_id_hook(map_id.value, &level) || multiplayer_levels_try_and_get_by_map_id_hook(map_id.value, &level))
		strcpy(scenario_image_path, level.ScenarioImagePath);
	if (!strlen(scenario_image_path))
		return 0;

	const char *image_name = map_id.GetImageName();
	
	switch (content_type)
	{
	case 0:
		format<256>(DstBuf, "%s%s.blf", scenario_image_path, image_name);
		break;
	case 1:
		format<256>(DstBuf, "%s%s_sm.blf", scenario_image_path, image_name);
		break;
	case 2:
		format<256>(DstBuf, "%s%s_variant.blf", scenario_image_path, image_name);
		break;
	case 3:
		format<256>(DstBuf, "%s%s_film.blf", scenario_image_path, image_name);
		break;
	case 4:
		format<256>(DstBuf, "%s%s_clip.blf", scenario_image_path, image_name);
		break;
	default:
		return strlen(DstBuf) > 0;
	}

	//printf_s("%s\n", DstBuf);
	return strlen(DstBuf) > 0;
}

inline void SubmitMapHooks(const char *name)
{
	if (ConfigManager.GetBool("Hooks", name))
	{
		//HookManager.Submit({ 0x10FC2C, 0x1671BE, 0x167B4F }, &main_game_change_immediate_hook, "main_game_change_immediate", HookFlags::IsCall);
		//HookManager.Submit({ 0x14C7FF }, &maps_store_map_info_hook, "maps_store_map_info", HookFlags::IsCall);
		//HookManager.Submit({ 0x14EB54, 0x14EB62, 0x152C15 }, &game__game_engine__start_game_hook, "game::game_engine::start_game", HookFlags::IsCall);
		//HookManager.Submit({ 0x105ABA, 0x105AD7, 0x1063E6 }, &c_stop_watch__start_hook, "c_stop_watch::start", HookFlags::IsCall);

		//HookManager.Submit({ 0x101A51 }, &map_file_validation_hook, "map_file_validation", HookFlags::IsCall);
		//HookManager.Submit({ 0x10286A }, &sub_52CCC0_hook, "sub_52CCC0", HookFlags::IsCall);
		//HookManager.Submit({ 0x10309E }, &sub_508F80_hook, "sub_508F80", HookFlags::IsCall);
		//HookManager.Submit({ 0x10C965 }, &compute_blf_hash_hook, "compute_blf_hash", HookFlags::IsCall);

		HookManager.Submit({ 0x6C3900 }, &sub_AC3900_hook, "sub_AC3900");
	}
}

inline void SubmitMapPatches(const char *name)
{
	if (ConfigManager.GetBool("Patches", name))
	{

	}
}