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

size_t g_director_vftable = -1;
size_t g_camera_vftable = -1;

uint8_t *__cdecl director_get_player_hook(int index)
{
	auto result = (uint8_t *)thread_local_storage(thread_local_storage::_director_globals).GetDefinition<uint8_t[0x5C0]>(0x160 + (4 * index));

	auto p_director_vftable = (size_t *)result;
	auto p_camera_vftable = (size_t *)(result + 4);

	if (g_director_vftable != *p_director_vftable)
	{
		g_director_vftable = *p_director_vftable;
		g_vftables.at(g_director_vftable).PrintMembers();
	}
	if (g_camera_vftable != *p_camera_vftable)
	{
		g_camera_vftable = *p_camera_vftable;
		g_vftables.at(g_camera_vftable).PrintMembers();
	}

	return result;
}

//.text:00A28DA0; int __thiscall c_first_person_view::update_weapon(c_first_person_view *this, char a2)
int __fastcall c_first_person_view_update_weapon_hook(uint8_t *thisptr, char a2)
{
	//*(float *)0x01913434 = 0.55f;
	auto result = ((int (__thiscall *)(uint8_t *, char))(0x00A28DA0))(thisptr, a2);

	auto &vtable = *(uint32_t *)(thisptr);
	auto &weapon_fov = *(float *)(thisptr + 0x2C);
	auto unknown34 = *(uint16_t *)(thisptr + 0x34);

	float(__cdecl * map)(double, double, double, double, double) = Utils::Math::Map<float>;

	//weapon_fov = 0.88f * (weapon_fov / *(float *)0x01913434);

	//weapon_fov *= 0.88;
	float fov = map(weapon_fov, 0.672053f, 1.927432f, 55, 150);
	//if (fov > 120)
	//	weapon_fov = map(fov, 90, 150, 0.88f, 0.55f);

	//printf_s("[vtable: 0x%08X]\n", vtable);
	if (vtable == 0x0165E11C)
	{
		printf_s("[weapon fov: %f, fov: %.2f]\n", weapon_fov / *(float *)0x01913434, fov);
		//weapon_fov = 1.88f;
	}

	return result;
}

inline void SubmitCameraHooks(const char *name)
{
	if (ConfigManager.GetBool("Hooks", name))
	{
		//HookManager.Submit({ 0x00614D68 }, &sub_614CB0_hook, "camera_definition_validate", HookFlags::IsCall);

		HookManager.Submit({ 0x0059228B, 0x00592399 }, &director_globals_set_director_mode_hook, "director_globals_set_director_mode", HookFlags::IsCall);
		HookManager.Submit({ 0x00591990 }, &director_get_player_hook, "director_get_player");

		HookManager.Submit({ 0x00A29028, 0x00A291B8, /*0x00A3A4CA, 0x00A3A67A*/ }, &c_first_person_view_update_weapon_hook, "c_first_person_view::update_weapon", HookFlags::IsCall);
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