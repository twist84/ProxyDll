#pragma once
#include <Utils.hpp>

#include "../memory/local_types.hpp"

char __cdecl sub_614CB0_hook(uint8_t *a1)
{
	auto result = ((char(__cdecl *)(uint8_t *))0x614CB0)(a1);
	((s_camera_definition*)a1)/*->Print(true, true, true, true)*/->FieldOfView.ConvertForWeapon((float*)0x1913434, Utils::Math::Map<float>);
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