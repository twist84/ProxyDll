#pragma once
#include <Utils.hpp>

#include "../memory/local_types.hpp"

char __cdecl sub_614CB0_hook(uint8_t *a1)
{
	bool result; // validate after updating weapon fov the definition is still valid
	auto camDef = s_camera_definition(a1).ConvertForWeapon((float *)0x1913434, Utils::Math::Map<float>)->Validate(&result)/*->Print(true, true, true, true)*/;
	return result;
}

void observer_camera_mode_update(uint8_t camera_mode)
{
	// default is 3:first_person
	*(uint8_t *)0x726449 = camera_mode;
}

uint8_t *__cdecl director_globals_set_director_mode_hook(int local_player_index, int director_mode)
{
	auto dir_mode = ConfigManager.GetInt("Camera", "DirectorMode");
	if (dir_mode != -1)
		director_mode = dir_mode;

	auto cam_mode = ConfigManager.GetInt("Camera", "CameraMode");
	if (dir_mode == 3 && cam_mode != -1) observer_camera_mode_update(cam_mode);

	auto result = ((uint8_t * (__cdecl *)(int, int))(0x592480))(local_player_index, director_mode);

	printf_s("player_index:%d, director_mode:%d\n", local_player_index, director_mode);
	return result;
}

inline void SubmitCameraHooks(const char *name)
{
	if (ConfigManager.GetBool("Hooks", name))
	{
		HookManager.Submit({ 0x214D68 }, &sub_614CB0_hook, "camera_definition_validate", HookFlags::IsCall);

		HookManager.Submit({ 0x19228B, 0x192399 }, &director_globals_set_director_mode_hook, "director_globals_set_director_mode", HookFlags::IsCall);
	}
}

void observer_camera_mode_patch()
{
	observer_camera_mode_update(3);
}

inline void SubmitCameraPatches(const char *name)
{
	if (ConfigManager.GetBool("Patches", name))
	{
		PatchManager.Submit(&observer_camera_mode_patch, "observer_camera_mode");
	}
}