#pragma once
#include <iostream>

#include <Utils.hpp>
#include "../memory/local_types.hpp"

inline char __cdecl unit_action_submit_hook(void *object_handle, e_unit_action unit_action_index)
{
	static const auto unit_action_submit_internal = (char(__cdecl *)(void *, s_unit_action *))0xB69C50;

	s_unit_action unit_action;
	memset(&unit_action, 0, sizeof(s_unit_action));
	unit_action.Index = unit_action_index;
	bool result = unit_action_submit_internal(object_handle, &unit_action);

	if (result)
	{
		//if (scenario_type_get() != e_scenario_type::_mainmenu)
		//	printf_s("%s\n", GetStructure<UnitActionInfo>(0x1947A58, unit_action.Index)->Name);
	}

	return result;
}

inline void AddUnitHooks(const char *name)
{
	if (ConfigManager.GetBool("Hooks", name))
	{
		HookManager.AddHook({ 0x769CF0 }, &unit_action_submit_hook, "unit_action_submit");
	}
}


inline void AddUnitPatches(const char *name)
{
	if (ConfigManager.GetBool("Patches", name))
	{

	}
}