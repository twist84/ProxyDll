#pragma once
#include <iostream>

#include "../utils/Utils.hpp"

#include "../memory/local_types.hpp"

#include "print.hpp"

double get_time_from_frame_count_hook(signed int frame_count)
{
	auto gameGlobalsPtr = game_globals_get();
	return (frame_count / (!gameGlobalsPtr ? 60.0 : gameGlobalsPtr->game_options.FrameLimit));
}

bool game_is_campaign_hook()
{
	return game_options_get()->ScenarioType.value == e_scenario_type::_campaign;
}

bool game_in_progress_hook()
{
	auto game_globals = game_globals_get();
	if (!game_globals || !game_globals->unknown24BDC || game_globals->unknown0)
		return false;
	if (game_globals->unknown1)
		return true;
	return false;
}

bool game_is_multiplayer_hook()
{
	return game_options_get()->ScenarioType.value == e_scenario_type::_multiplayer;
}

bool game_is_survival_hook()
{
	auto game_globals = game_globals_get();
	if (game_globals && (game_globals->unknown0 || game_globals->unknown1))
	{
		auto game_options = &game_globals->game_options;
		if (game_options && (game_options->ScenarioType.value == e_scenario_type::_campaign && game_options->SurvivalModeEnabled))
			return true;
	}
	return false;
}

bool game_is_theater_hook()
{
	auto game_globals = game_globals_get();
	return game_globals && (game_globals->unknown0 || game_globals->unknown1) && game_globals->game_options.GamePlayback.value;
}

bool game_is_playtest_hook()
{
	return game_options_get()->IsPlaytest;
}

bool game_is_mainmenu_hook()
{
	return game_options_get()->ScenarioType.value == e_scenario_type::_mainmenu;
}


bool game_is_map_loading_hook()
{
	return !IsMapLoaded();
}

bool sub_42E130_hook()
{
	return false;
}

bool game_is_multithreaded_hook()
{
	return false;
}

char prepare_game_level_hook(uint32_t a1)
{
	auto game_globals = game_globals_get();
	if (!sub_42E130_hook())
	{
		if (game_globals && (game_globals->unknown24BDC && !game_globals->unknown0 && game_globals->unknown1 && game_globals->game_options.ScenarioType.value == e_scenario_type::_campaign && game_globals->unknown24B58 != a1))
		{
			game_globals->unknown24B58 = a1;
			game_globals->unknown24BDF = false;
		}
	}
	return game_globals->unknown0;
}

char game_level_prepare_hook(uint32_t a1)
{
	auto game_globals = game_globals_get();
	if (!sub_42E130_hook())
	{
		if (game_globals && (game_globals->unknown24BDC && !game_globals->unknown0 && game_globals->unknown1 && game_globals->game_options.ScenarioType.value == e_scenario_type::_campaign))
		{
			game_globals->unknown24B58 = a1;
			game_globals->unknown24BDF = true;
		}
	}
	return game_globals->unknown0;
}

std::vector<e_primary_skull> primary_skulls = {
	{ e_primary_skull::_iron, false },
	{ e_primary_skull::_black_eye, false },
	{ e_primary_skull::_tough_luck, false },
	{ e_primary_skull::_catch, false },
	{ e_primary_skull::_fog, false },
	{ e_primary_skull::_famine, false },
	{ e_primary_skull::_thunderstorm, false },
	{ e_primary_skull::_tilt, false },
	{ e_primary_skull::_mythic, false }
};

std::vector<e_secondary_skull> secondary_skulls = {
	{ e_secondary_skull::_assassin, false },
	{ e_secondary_skull::_blind, false },
	{ e_secondary_skull::_superman, false },
	{ e_secondary_skull::_birthday_party, false },
	{ e_secondary_skull::_daddy, false },
	{ e_secondary_skull::_third_person, false },
	{ e_secondary_skull::_directors_cut, false }
};

void primary_skull_toggle_hook(__int16 skull, char enable)
{
	if (skull < e_primary_skull::k_number_of_primary_skulls)
		primary_skulls[skull].enabled = enable ? true : false;
}

void secondary_skull_toggle_hook(__int16 skull, char enable)
{
	if (skull < e_secondary_skull::k_number_of_secondary_skulls)
		secondary_skulls[skull].enabled = enable ? true : false;
}

bool __cdecl primary_skull_is_active_hook(__int16 skull)
{
	if (skull < e_primary_skull::k_number_of_primary_skulls)
		return primary_skulls[skull].enabled;
	return false;
}

bool __cdecl secondary_skull_is_active_hook(__int16 skull)
{
	if (skull < e_secondary_skull::k_number_of_secondary_skulls)
		return secondary_skulls[skull].enabled;
	return false;
}

bool game_is_widescreen_hook()
{
	return GetStructure<s_screen_resolution>(0x19106C0)->IsWidescreen();
}

double aspect_ratio_get_hook()
{
	return GetStructure<s_screen_resolution>(0x19106C0)->GetAspectRation();
}

bool sub_42E350_hook()
{
	return true;
}

void GameClientShutdownHook()
{
}
void sub_600A20_hook()
{
}

unsigned long __cdecl podium_duration_call_hook(float a1)
{
	auto podium_duration = 7;
	return (unsigned long)((1.0 * 0.5) + 60 * podium_duration);
}

int game_set_initial_network_values_hook()
{
	auto result = ((int(*)())0x43D2B0)();

	initial_network_values->offline_max_player_count = 4; // works

	initial_network_values->lobby_coop_max_player_count = 8; // unsure
	initial_network_values->lobby_mapeditor_max_player_count = 16; // unsure
	initial_network_values->lobby_film_max_player_count = 8; // unsure

	return result;
}

const char *peer_property_get_string_hook(e_peer_property peer_property)
{
	if (peer_property.value >= e_peer_property::k_number_of_peer_properties)
		return "unknown";

	auto g_peer_property = *(e_peer_property *)0x19A03BC;

	//printf_s("peer_property: %s\n", peer_property.GetName());
	return peer_property.GetName();
}

string_id lobby_status_get_hook(bool player_is_squad_leader)
{
	auto result = ((string_id(*)(bool))0xB214E0)(false);

	switch (result.value)
	{
	case 0x50011: // error_network_configuration_unavailable
	case 0x50013: // error_banhammer_unavailable
	case 0x50017: // match_error_master_hopper_file_unavailable
	case 0x50019: // match_error_hopper_specific_file_unavailable
	case 0x5000F: // error_account_not_online_enabled
	case 0x5002F: // match_error_must_have_online_enabled_profiles_for_match
	case 0x50030: // match_error_must_connect_to_live_for_match
	case 0x5001A: // match_error_invalid_hopper
	case 0x50020: // match_error_unpaid_in_paid_hopper
	case 0x50021: // match_error_paid_in_unpaid_hopper
	case 0x50032: // must_be_connected_to_live_in_live_lobby
		result.value = 0x5003B; // status_ready_leader
		break;
	}

	//printf_s("lobby_status: %s\n", result.GetName());
	return result;
}

e_network_game_start_mode gamestart_status_get_hook(uint32_t *a1, uint32_t *a2)
{
	a1 = 0, a2 = 0;
	auto result = ((e_network_game_start_mode(__cdecl *)(uint32_t *, uint32_t *))0xA809F0)(a1, a2);

	switch (result.value)
	{
	case e_network_game_start_mode::_error:
		result.value = e_network_game_start_mode::_ready_leader;
		//printf_s("gamestart_status_error: unknown\n");
		break;
	}

	//printf_s("gamestart_status: %s\n", result.GetName());
	return result;
}

uint32_t __fastcall dereference_pointer_hook(void *thisptr)
{
	printf_s("0x%X\n", *(uint32_t *)thisptr);
	return *(uint32_t *)thisptr;
}

bool __fastcall c_life_cycle_state_handler_matchmaking_start__squad_allowed_to_start_matchmaking_hook(uint32_t *thisptr, bool a2)
{
	auto result = ((bool(__thiscall *)(uint32_t *, bool))0x4940F0)(thisptr, a2);

	printf_s("squad_allowed_to_start_matchmaking: %s", (result ? "true" : "false"));
	return result;
}

signed int __stdcall vector_ctor_iterator_hook(char *data_ptr, unsigned int size, int count, void(__thiscall *ctor)(void *), void(__thiscall *dtor)(void *))
{
	int v5 = 0;
	char *v6 = data_ptr;
	while (v5 < count)
	{
		ctor(v6);
		v6 += size;
		++v5;
	}

	printf_s("ptr: 0x%X | size: 0x%X | count: %d | ctor: 0x%X | dtor: 0x%X\n", *(unsigned int *)data_ptr, size, count, *(unsigned int *)ctor, *(unsigned int *)dtor);
	return 1;
}

signed int __stdcall vector_dtor_iterator_hook(char *data_ptr, unsigned int size, int count, void(__thiscall *dtor)(void *))
{
	int v4 = count;
	for (char *i = &data_ptr[count * size]; --v4 >= 0; dtor(i))
		i -= size;

	printf_s("ptr: 0x%X | size: 0x%X | count: %d | dtor: 0x%X\n", *(unsigned int *)data_ptr, size, count, *(unsigned int *)dtor);
	return 1;
}

inline void AddMiscHooks(const char *name)
{
	if (ConfigManager.GetBool("Hooks", name))
	{
		AddHook({ 0x2796C0 }, &get_time_from_frame_count_hook, "get_time_from_frame_count");
		AddHook({ 0x1314B0 }, &game_in_progress_hook, "game_in_progress");
		AddHook({ 0x131A60 }, &game_is_campaign_hook, "game_is_campaign");
		AddHook({ 0x131C00 }, &game_is_multiplayer_hook, "game_is_multiplayer");
		AddHook({ 0x131D10 }, &game_is_theater_hook, "game_is_theater");
		AddHook({ 0x131D50 }, &game_is_playtest_hook, "game_is_playtest");
		AddHook({ 0x131E20 }, &game_is_survival_hook, "game_is_survival");
		AddHook({ 0x131E90 }, &game_is_mainmenu_hook, "game_is_mainmenu");

		AddHook({ 0x1670E0 }, &game_is_map_loading_hook, "game_is_map_loading");

		AddHook({ 0x131FF0 }, &prepare_game_level_hook, "prepare_game_level");
		AddHook({ 0x132050 }, &game_level_prepare_hook, "game_level_prepare");

		AddHook({ 0x132B50 }, &primary_skull_toggle_hook, "primary_skull_toggle");
		AddHook({ 0x132EE0 }, &secondary_skull_toggle_hook, "secondary_skull_toggle");

		AddHook({ 0x20AE20 }, &primary_skull_is_active_hook, "primary_skull_is_active");
		AddHook({ 0x20AE50 }, &secondary_skull_is_active_hook, "secondary_skull_is_active");


		AddHook({ 0x2E130 }, &sub_42E130_hook, "sub_42E130");

		//AddHook({ 0x2E2C0 }, &game_is_multithreaded_hook, "game_is_multithreaded");

		AddHook({ 0x61FA30 }, &aspect_ratio_get_hook, "aspect_ratio_get");
		AddHook({ 0x61FC90 }, &game_is_widescreen_hook, "game_is_widescreen");

		//AddHook({ 0x622169, 0x10BF07 }, &sub_42E350_hook, "sub_42E350", HookFlags::IsCall);

		//AddHook({ 0x1056D0 }, &GameClientShutdownHook, "GameClientShutdown");
		//AddHook({ 0x200A20 }, &sub_600A20_hook, "sub_600A20");

		AddHook({ 0x130FAE }, &podium_duration_call_hook, "podium_duration", HookFlags::IsCall);

		AddHook({ 0x3C966 }, &game_set_initial_network_values_hook, "game_set_initial_network_values", HookFlags::IsCall);

		AddHook({ 0x149B70 }, &peer_property_get_string_hook, "peer_property_get_string");

		AddHook({ 0x7232DB }, &lobby_status_get_hook, "lobby_status_get", HookFlags::IsCall);

		AddHook({ 0x7232C4 }, &gamestart_status_get_hook, "gamestart_status_get", HookFlags::IsCall);

		AddHook({ 0x942D3, 0x9432F }, &c_life_cycle_state_handler_matchmaking_start__squad_allowed_to_start_matchmaking_hook, "c_life_cycle_state_handler_matchmaking_start::squad_allowed_to_start_matchmaking", HookFlags::IsCall);

		//AddHook({ 0x12BC80 }, &dereference_pointer_hook, "dereference_pointer");

		//AddHook({ 0x7F0454 }, &vector_ctor_iterator_hook, "vector_constructor_iterator'");
		//AddHook({ 0x7F04BC }, &vector_dtor_iterator_hook, "vector_destructor_iterator'");
	}
}


bool lod_increase_patch()
{
	memset(Pointer(0xA65EBB), 0x50, 1);
	memset(Pointer(0xA1962C), 0x90, 2);

	return true;
}

bool unknown_float30_to_float60_patch()
{
	SetMemoryAtOffset<float>(0x1615F34, 60);

	return true;
}

bool match_beginning_countdown_patch()
{
	unsigned long seconds = 0;

	Pointer::Base(0x153708).Write<uint8_t>((uint8_t)seconds + 0); // player control
	Pointer::Base(0x153738).Write<uint8_t>((uint8_t)seconds + 4); // camera position
	Pointer::Base(0x1521D1).Write<uint8_t>((uint8_t)seconds + 4); // ui timer

	// Fix team notification
	if (seconds == 4)
		Pointer::Base(0x1536F0).Write<uint8_t>(2);
	else
		Pointer::Base(0x1536F0).Write<uint8_t>(3);

	return true;
}

bool gamestart_status_error_check_patch()
{
	// gamestart_status == e_gamestart_status::_error checks
	memset(Pointer(0xA80A5D), 0x90, 2);
	memset(Pointer(0xB23319), 0x90, 2);

	return true;
}

bool gameshield_initialize_patch()
{
	Patch::NopFill(0x2BCDB6, 5);

	return true;
}

void AddMiscPatches(const char *name)
{
	if (ConfigManager.GetBool("Patches", name))
	{
		AddPatch(&lod_increase_patch, "lod_increase");
		AddPatch(&match_beginning_countdown_patch, "match_beginning_countdown");
		//AddPatch(&unknown_float30_to_float60_patch, "unknown_float30_to_float60"); // this float is what's actually used in get_time_from_frame_count, but we hook it just incase

		AddPatch(&gamestart_status_error_check_patch, "gamestart_status_error_check");
	}
}