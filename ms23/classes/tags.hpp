#pragma once

#include <Utils.hpp>

#include "../memory/tag_groups.hpp"
#include "../memory/local_types.hpp"

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

const char *maps_path_hook()
{
	return g_maps_path.c_str();
}

uint8_t *__cdecl tag_block_get_defintion_hook(tag_block *block, int index, int size)
{
	auto result = &block->address[size * index];

	// DO STUFF!
	//printf_s("count: %d | block[%d]->size == 0x%X\n", block->count, index, size);

	return result;
}

inline void SubmitTagsHooks(const char *name)
{
	if (ConfigManager.GetBool("Hooks", name))
	{
		HookManager.Submit({ 0x103370 }, &tag_get_definition_hook, "tag_get_definition");
		HookManager.Submit({ 0x1033A0 }, &tag_get_group_tag_hook, "tag_get_group_tag");
		
		HookManager.Submit({ 0x101FC0 }, &maps_path_hook, "maps_path");
		HookManager.Submit({ 0x15AA00 }, &tag_block_get_defintion_hook, "tag_block_get_defintion");
	}
}

inline void SubmitTagsPatches(const char *name)
{
	if (ConfigManager.GetBool("Patches", name))
	{
		//PatchManager.Submit(&, "");
	}
}