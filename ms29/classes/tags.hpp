#pragma once

#include <Utils.hpp>

#include "../memory/local_types.hpp"

inline void AddTagsHooks(const char *name)
{
	if (ConfigManager.GetBool("Hooks", name))
	{

	}
}

void enable_tag_edits_patch()
{
	// enable tag edits (untested)
	Patch(0x82DB4, { 0xEB }).Apply();
	Patch::NopFill(Pointer::Base(0x83120), 2);
	Patch::NopFill(Pointer::Base(0x83AFC), 2);
}

inline void AddTagsPatches(const char *name)
{
	if (ConfigManager.GetBool("Patches", name))
	{
		PatchManager.AddPatch(&enable_tag_edits_patch, "enable_tag_edits");
	}
}