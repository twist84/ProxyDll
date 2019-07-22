#pragma once

#include <Utils.hpp>

#include "../memory/tag_groups.hpp"
#include "../memory/local_types.hpp"
#include "filo.hpp"
#include "level.hpp"

// scenario biped palette
// _mp_masterchief, 0
// _mp_elite, 1
// _odst, 2
// _marine, 3
// _mp_masterchief_ui, 4
// _mp_elite_ui, 5
// _mp_masterchief_mannequin, 6
// _mp_elite_mannequin, 7

uint8_t *__cdecl tag_get_definition_hook(uint32_t group, uint32_t index)
{
	auto result = s_tag(index, group)./*Print('matg')->*/GetDefinition<uint8_t>();

	// DO STUFF!
	//PrintTagGroup(group, index);

	if (group == 'scnr' && index == 0x27C3)
	{
		if (ConfigManager.GetBool("Misc", "CovenantMaimenu"))
		{
			Copy<uint16_t>(TagBlock<0x34, 0x424>(result, 72), TagBlock<0x34, 0x424>(result, 73), { 0x24, 0x26 }); // hangar script			
			Copy<uint32_t>(TagBlock<0x30, 0x0EC>(result, 05), TagBlock<0x30, 0x0EC>(result, 03), { 0x00, 0x0C }); // biped palette
		}
	}

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

inline void SubmitTagsHooks(const char *name)
{
	if (ConfigManager.GetBool("Hooks", name))
	{
		HookManager.Submit({ 0x103370 }, &tag_get_definition_hook, "tag_get_definition");
		HookManager.Submit({ 0x1033A0 }, &tag_get_group_tag_hook, "tag_get_group_tag");
		HookManager.Submit({ 0x15AA00 }, &tag_block_get_defintion_hook, "tag_block_get_defintion");

		HookManager.Submit({ 0x101FC0 }, &maps_path_hook, "maps_path");
		HookManager.Submit({ 0x102E87 }, &filo_create_and_open_tags_hook, "filo_create_and_open_tags", HookFlags::IsCall);
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