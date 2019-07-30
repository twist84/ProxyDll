#pragma once

#include <Utils.hpp>

#include "../memory/tag_groups.hpp"
#include "../memory/local_types.hpp"
#include "filo.hpp"
#include "level.hpp"

struct s_mainmenu_scnr_tag
{
	bool Compare(uint32_t group, uint32_t index)
	{
		return group == 'scnr' && index == 0x27C3;
	}

	void CallBack(uint8_t *definition)
	{
		if (ConfigManager.GetInt("Maimenu.Hangar", "Type") == 1)
			Copy<uint16_t>(TagBlock<0x34, 0x424>(definition, 72), TagBlock<0x34, 0x424>(definition, 73), { 0x24, 0x26 }); // hangar script

		// biped palette
		Copy<uint32_t>(TagBlock<0x30, 0x0EC>(definition, e_biped_palette::_mp_masterchief_ui), TagBlock<0x30, 0x0EC>(definition, e_biped_palette(ConfigManager.GetInt("Maimenu.Hangar", "Biped.Human")).value), { 0x00, 0x0C });
		Copy<uint32_t>(TagBlock<0x30, 0x0EC>(definition, e_biped_palette::_mp_elite_ui), TagBlock<0x30, 0x0EC>(definition, e_biped_palette(ConfigManager.GetInt("Maimenu.Hangar", "Biped.Covenant")).value), { 0x00, 0x0C });
	}
} g_mainmenu_scnr_tag;

uint8_t *__cdecl tag_get_definition_hook(uint32_t group, uint32_t index)
{
	auto result = s_tag(index, group)./*Print('matg')->*/GetDefinition<uint8_t>();

	// DO STUFF!
	//PrintTagGroup(group, index);

	if (g_mainmenu_scnr_tag.Compare(group, index))
		g_mainmenu_scnr_tag.CallBack(result);

	return result;
}

uint32_t __cdecl tag_get_group_tag_hook(uint32_t index)
{
	auto result = s_tag(index)./*Print('matg')->*/GetGroupTag();

	if (result == group_tags.globals.Group)
		g_tag_info.globals_tag = result;

	// DO STUFF!
	//PrintTagGroup(result, index);

	return result;
}

uint8_t *__cdecl tag_block_get_defintion_hook(tag_block *block, int index, int size)
{
	auto result = &block->address[size * index];

	// DO STUFF!
	//printf_s("count: %d | block[%d]->size == 0x%X\n", block->count, index, size);

	return result;
}

const char *maps_path_hook()
{
	return g_maps_path.c_str();
}

char __fastcall filo_create_and_open_tags_hook(void *thisptr)
{
	cache_path.Update(ConfigManager.GetBool("Maps", "UseNewCacheStyle"));
	auto result = ((char(__thiscall *)(void *))0x5028C0)(thisptr);
	cache_path.tags.Print();

	return result;
}

template<typename T>
char cache_read_hook(T *a1, int a2, LONG tag_offset, DWORD size, LPVOID buffer)
{
	printf_s("cache_read: [tag_offset, 0x%04X, size, 0x%04X]\n", tag_offset, size);

	//return ((char(*)(uint8_t *, int, LONG, DWORD, LPVOID))(0x5016D0))(a1, a2, tag_offset, size, buffer);
	int file_error;
	if (!file_open(global_tag_cache_filo, 1, &file_error))
		return 0;
	if (!file_set_position_hook(global_tag_cache_filo, tag_offset, 0))
		return 0;
	return file_read_hook(global_tag_cache_filo, size, 0, buffer);
}

template<typename T>
char filo_read_tag_hook(T *a1, LONG tag_offset, DWORD size, LPVOID buffer)
{
	printf_s("filo_read_tag: [tag_offset, 0x%04X, size, 0x%04X]\n", tag_offset, size);
	if (!(g_cache_file->ExternalDependencies & 2))
		return cache_read_hook(a1, 2, tag_offset, size, buffer);

	int file_error;
	if (!file_open(global_tag_cache_filo, 1, &file_error))
		return 0;
	if (!file_set_position_hook(global_tag_cache_filo, tag_offset, 0))
		return 0;
	return file_read_hook(global_tag_cache_filo, size, 0, buffer);
}

s_cache_file_header *cache_file_header_get_hook()
{
	auto result = g_cache_file;

	printf_s("cache_file_get: [cache_file->ScenarioPath, %s]\n", result->ScenarioPath);
	printf_s("cache_file_get: [cache_file->ExternalDependencies, %d]\n", result->ExternalDependencies);

	return result;
}

template<typename Ta, typename Tb>
char sub_5AA7C0_hook(Ta *a1, Tb *a2, char *scenario_path, uint8_t *cache_file)
{
	auto result = ((char(*)(Ta *, Tb *, char *, uint8_t *))0x5AA7C0)(a1, a2, scenario_path, cache_file);

	printf_s("sub_5AA7C0: [cache_file->ScenarioPath, %s]\n", g_cache_file->ScenarioPath);

	return result;
}

template<typename Ta, typename Tb>
char map_load_tags_hook(Ta *a1, Tb *a2, char *scenario_path)
{
	auto result = ((char(*)(Ta *, Tb *, char *))0x502DC0)(a1, a2, scenario_path);

	printf_s("map_load_tags: [scenario_path, %s]\n", scenario_path);

	return result;
}

template<typename T>
char sub_502780_hook(T *a1, uint32_t tag_index)
{
	auto result = ((char(*)(T *, uint32_t tag_index))0x502780)(a1, tag_index); // crashes here on second run

	printf_s("sub_502780: [tag_index, 0x%04X]\n", tag_index);

	return result;
}

inline void SubmitTagsHooks(const char *name)
{
	if (ConfigManager.GetBool("Hooks", name))
	{
		HookManager.Submit({ 0x103370 }, &tag_get_definition_hook, "tag_get_definition");
		HookManager.Submit({ 0x1033A0 }, &tag_get_group_tag_hook, "tag_get_group_tag");
		HookManager.Submit({ 0x15AA00 }, &tag_block_get_defintion_hook, "tag_block_get_defintion");

		HookManager.Submit({ 0x101FC0 }, &maps_path_hook, "maps_path");
		HookManager.Submit({ 0x102E87 }, &filo_create_and_open_tags_hook, "filo_create_and_open_tags", HookFlags::IsCall);

		//HookManager.Submit({ 0x102C90 }, &filo_read_tag_hook<uint8_t>, "filo_read_tag");
		//HookManager.Submit({ 0x101F90 }, &cache_file_header_get_hook, "cache_file_header_get");
		//HookManager.Submit({ 0x1016D0 }, &cache_read_hook<uint8_t>, "cache_read");

		//HookManager.Submit({ 0x102E1E }, &sub_5AA7C0_hook<uint8_t, uint8_t>, "sub_5AA7C0", HookFlags::IsCall);
		//HookManager.Submit({ 0x0EA5EE }, &map_load_tags_hook<uint8_t, uint8_t>, "map_load_tags", HookFlags::IsCall);

		//HookManager.Submit({ 0x102F03, 0x102F16 }, &sub_502780_hook<uint8_t>, "sub_502780", HookFlags::IsCall);
	}
}

void cache_read_patch()
{
	if (ConfigManager.GetBool("Maps", "UseNewCacheStyle"))
	{
		Patch(0x1027C7, { 0xEB }).Apply();
		Patch(0x102C9A, { 0xEB }).Apply();
		//Patch::NopFill(0x102B54, 6);
		//Patch::NopFill(0x102907, 2);
		//Patch::NopFill(0x102F27, 2);
	}
}

inline void SubmitTagsPatches(const char *name)
{
	if (ConfigManager.GetBool("Patches", name))
	{
		PatchManager.Submit(&cache_read_patch, "cache_read_patch");
	}
}