#pragma once
#include "../utils/Utils.hpp"

#include "../memory/local_types.hpp"

char __cdecl sub_553660_hook(uint8_t *a1)
{
	auto result = ((char(__cdecl *)(uint8_t *))0x553660)(a1);
	auto &definition = *(s_camera_definition *)a1;

	auto position = definition.position;
	auto position_shift = definition.position_shift;
	auto look = definition.look;
	auto look_shift = definition.look_shift;
	auto depth = definition.depth;
	auto field_of_view = definition.field_of_view;
	auto forward = definition.forward;
	auto up = definition.up;
	auto direction = definition.direction;
	auto center = definition.center;
	auto zoom_transition_time = definition.zoom_transition_time;

	if (direction.i != 0.0f || direction.j != 0.0f || direction.k != 0.0f)
	{
		printf_s("pos: %f %f %f, pos_shift: %f %f %f\n", position.i, position.j, position.k, position_shift.i, position_shift.j, position_shift.k);
		printf_s("look: %f, look_shift: %f, depth: %f, fov: %f\n", look, look_shift, depth, field_of_view.Get());
		printf_s("forward: %f %f %f, up: %f %f %f, direction: %f %f %f\n", forward.i, forward.j, forward.k, up.i, up.j, up.k, direction.i, direction.j, direction.k);
		printf_s("center: %f %f %f, zoom_transition_time: %f\n", center.i, center.j, center.k, zoom_transition_time);
	}

	auto fov = field_of_view.Get();
	auto new_val = fov < 90 ? Utils::Math::Map<float>(fov, 55, 70, 1.15, 1.0) : Utils::Math::Map<float>(fov, 55, 120, 1.15, 0.7);
	*(float *)0x1913434 = new_val + fov < 90 ? new_val + 0.0f : fov < 110 ? new_val + 0.05f : fov < 110 ? new_val + 0.15f : new_val + 0.20f;

	return result;
}

inline void AddCameraHooks(const char *name)
{
	if (ConfigManager.GetBool("Hooks", name))
	{
		AddHook({ 0x14690A }, &sub_553660_hook, "camera_definition_validate", HookFlags::IsCall);
	}
}

inline void AddCameraPatches(const char *name)
{
	if (ConfigManager.GetBool("Patches", name))
	{

	}
}