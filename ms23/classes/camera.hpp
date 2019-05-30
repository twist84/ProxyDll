#pragma once
#include <Utils.hpp>

#include "../memory/local_types.hpp"

char __cdecl sub_614CB0_hook(uint8_t *a1)
{
	auto result = ((char(__cdecl *)(uint8_t *))0x614CB0)(a1);
	auto fov = ((s_camera_definition*)a1)->Print(true, true, true, true)->FieldOfView.Get();
	auto new_val = fov < 90 ? Utils::Math::Map<float>(fov, 55, 70, 1.15, 1.0) : Utils::Math::Map<float>(fov, 55, 120, 1.15, 0.7);
	*(float *)0x1913434 = new_val + fov < 90 ? new_val + 0.0f : fov < 110 ? new_val + 0.05f : fov < 110 ? new_val + 0.15f : new_val + 0.20f;

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