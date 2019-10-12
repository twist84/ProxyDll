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

static float s_weapon_fov_scale = 0.88f;

//.text:00A28DA0; int __thiscall c_first_person_view::update_weapon(class c_first_person_view *this, char a2)
template<int call_index>
int __fastcall c_first_person_view_update_weapon_hook(uint8_t *first_person_view, char a2)
{
	auto &weapon_fov_scale = *(float *)(0x01913434);
	auto &vtable = *(uint32_t *)(first_person_view);
	auto &weapon_fov = *(float *)(first_person_view + 0x2C);

	s_weapon_fov_scale = call_index == 1 ? 0.5f : 1.5f;

	auto result = ((int (__thiscall *)(uint8_t *, char))(0x00A28DA0))(first_person_view, a2);

	if (vtable == 0x0165E11C /* address of c_first_person_view::`vftable' */)
	{
		printf_s("[weapon fov: %f, fov: %.2f]\n", weapon_fov/* / s_weapon_fov_scale*/, Utils::Math::Map<float>(weapon_fov, 0.514266f, 1.696140f, 55, 150));
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

		HookManager.Submit({ 0x00A29028 }, &c_first_person_view_update_weapon_hook<0>, "c_first_person_view::update_weapon<shields?>", HookFlags::IsCall);
		HookManager.Submit({ 0x00A291B8 }, &c_first_person_view_update_weapon_hook<1>, "c_first_person_view::update_weapon<details?>", HookFlags::IsCall);
	}
}

void observer_camera_mode_patch()
{
	observer_camera_mode_update(3);
}

void c_first_person_view_update_weapon_fov_scale_patch()
{
	SetMemory<0x00A28E19>(&s_weapon_fov_scale, 4); // Pointer(0x00A28E1D).Write(&s_weapon_fov);
}

inline void SubmitCameraPatches(const char *name)
{
	if (ConfigManager.GetBool("Patches", name))
	{
		PatchManager.Submit(&observer_camera_mode_patch, "observer_camera_mode");
		PatchManager.Submit(&c_first_person_view_update_weapon_fov_scale_patch, "c_first_person_view::update_weapon() ::fov_scale_patch");
	}
}