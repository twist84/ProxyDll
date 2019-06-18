#pragma once
#include <Utils.hpp>

#include "../memory/local_types.hpp"

char __cdecl sub_614CB0_hook(uint8_t *a1)
{
	bool result; // validate after updating weapon fov the definition is still valid
	auto camDef = s_camera_definition(a1).ConvertForWeapon((float *)0x1913434, Utils::Math::Map<float>)->Validate(&result)/*->Print(true, true, true, true)*/;
	return result;
}

inline void AddCameraHooks(const char *name)
{
	if (ConfigManager.GetBool("Hooks", name))
	{
		HookManager.AddHook({ 0x214D68 }, &sub_614CB0_hook, "camera_definition_validate", HookFlags::IsCall);
	}
}

inline void AddCameraPatches(const char *name)
{
	if (ConfigManager.GetBool("Patches", name))
	{

	}
}