#pragma once
#include <iostream>

#include "../utils/Utils.hpp"
#include "../memory/local_types.hpp"

std::vector<size_t> c_simulation_event_handler_send_event_offsets = { 0xE5723, 0xE5A15, 0xE5B1B };
char c_simulation_event_handler_send_event_hook(uint32_t *this_ptr, e_simulation_event simulation_event, int a3, int a4, int a5, size_t num, void *source, int a8)
{
	if (scenario_type_get() != e_scenario_type::_mainmenu || simulation_event.value < e_simulation_event::k_number_of_simulation_events)
		printf_s(simulation_event.GetName());

	static auto c_simulation_event_handler_send_event = (char(__thiscall*)(uint32_t *this_ptr, e_simulation_event simulation_event, int a3, int a4, int a5, size_t num, void *source, int a8))(0x4A7500);
	return c_simulation_event_handler_send_event(this_ptr, simulation_event, a3, a4, a5, num, source, a8);
}

std::vector<size_t> simulation_event_generate_internal_offsets = { 0xB2409, 0xB387D, 0xB38E3, 0xB39D5, 0xB3A44, 0xB3B4B, 0xB3BB3, 0xB3D11, 0xB4142, 0xB4EF7, 0xB4F59, 0xB4FDA, 0xB5008, 0xB506D, 0xB5885, 0xE5803 };
char __cdecl simulation_event_generate_internal_hook(e_simulation_event simulation_event, int a2, int a3, int player_handle, size_t a5, void *a6)
{
	if (scenario_type_get() != e_scenario_type::_mainmenu || simulation_event.value < e_simulation_event::k_number_of_simulation_events)
		printf_s(simulation_event.GetName());

	static auto simulation_event_generate_internal = (char(__cdecl *)(e_simulation_event simulation_event, int a2, int a3, int player_handle, size_t a5, void *a6))(0x4E5A40);
	return simulation_event_generate_internal(simulation_event, a2, a3, player_handle, a5, a6);
}

inline void AddSimulationHooks(const char *name)
{
	if (ConfigManager.GetBool("Hooks", name))
	{
		// these crash the game if hooked, unsure currently as to why that is
		//AddHook(c_simulation_event_handler_send_event_offsets, &c_simulation_event_handler_send_event_hook, "c_simulation_event_handler_send_event");
		//AddHook(simulation_event_generate_internal_offsets, &simulation_event_generate_internal_hook, "simulation_event_generate_internal");
	}
}

inline void AddSimulationPatches(const char *name)
{
	if (ConfigManager.GetBool("Patches", name))
	{

	}
}