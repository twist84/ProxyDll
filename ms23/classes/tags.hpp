#pragma once

#include <Utils.hpp>

#include "../memory/tag_groups.hpp"
#include "../memory/local_types.hpp"
#include "filo.hpp"
#include "level.hpp"

uint32_t tag_get_group_tag(uint16_t index)
{
	if ((tag_header_get(index) == nullptr) || ((uint32_t)tag_header_get(index) < 0x400000))
		return -1;

	auto result = *(uint32_t *)(tag_header_get(index) + 0x14);
	if (result == group_tags.globals.Group)
		globals_tag = result;

	return result;
}

uint8_t *__cdecl tag_get_definition_hook(uint32_t group, uint16_t index)
{
	auto result = tag_get_definition<uint8_t>(group, index);

	// DO STUFF!
	//PrintTagGroup(group, index);

	return result;
}

uint32_t __cdecl tag_get_group_tag_hook(uint16_t index)
{
	auto result = tag_get_group_tag(index);

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
	g_tags.Print();

	return result;
}

inline void AddTagsHooks(const char *name)
{
	if (ConfigManager.GetBool("Hooks", name))
	{
		HookManager.AddHook({ 0x103370 }, &tag_get_definition_hook, "tag_get_definition");
		HookManager.AddHook({ 0x1033A0 }, &tag_get_group_tag_hook, "tag_get_group_tag");
		HookManager.AddHook({ 0x15AA00 }, &tag_block_get_defintion_hook, "tag_block_get_defintion");

		HookManager.AddHook({ 0x101FC0 }, &maps_path_hook, "maps_path");
		HookManager.AddHook({ 0x102E87 }, &filo_create_and_open_tags_hook, "filo_create_and_open_tags", HookFlags::IsCall);
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

inline void AddTagsPatches(const char *name)
{
	if (ConfigManager.GetBool("Patches", name))
	{
		PatchManager.AddPatch(&cache_read_patch, "cache_read_patch");
	}
}