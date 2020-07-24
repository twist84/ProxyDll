#pragma once
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <Pointer.hpp>

void* _mainTLS;
Pointer GetMainTls(size_t tlsOffset)
{
	// cache the result allowing future cross-thread calls to succeed
	if (_mainTLS == nullptr)
	{
		_asm
		{
			mov     eax, dword ptr fs : [2Ch]
			mov     eax, dword ptr ds : [eax]
			mov		_mainTLS, eax
		}
	}

	return Pointer(_mainTLS)(tlsOffset);
}

static void HandleFinder()
{
};
std::string GetDirectory()
{
	char Path[MAX_PATH];
	HMODULE hMod;
	if (!GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCSTR)&HandleFinder, &hMod))
	{
		int Error = GetLastError();
		OutputDebugString((LPCWSTR)std::string("Unable to resolve current directory, error code: ").append(std::to_string(Error)).c_str());
	}
	GetModuleFileNameA(hMod, Path, sizeof(Path));
	std::string Dir(Path);
	Dir = Dir.substr(0, std::string(Dir).find_last_of('\\') + 1);
	return Dir;
}
std::string GetModule()
{
	char Path[MAX_PATH];
	HMODULE hMod;
	if (!GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCSTR)&HandleFinder, &hMod))
	{
		int Error = GetLastError();
		OutputDebugString((LPCWSTR)std::string("Unable to resolve current directory, error code: ").append(std::to_string(Error)).c_str());
	}
	GetModuleFileNameA(hMod, Path, sizeof(Path));
	std::string Module(Path);
	Module = Module.substr(std::string(Module).find_last_of('\\') + 1);
	return Module;
}

std::string GetExecutable()
{
	char* cmd = GetCommandLineA();
	int offset = 0;
	if (cmd[offset] == '"')
		while (cmd[++offset] != '"');
	while (cmd[++offset] != ' ');
	return static_cast<std::string>(GetCommandLineA()).c_str();
}

#pragma warning( push )
#pragma warning( disable : 4244)
template <size_t offset, typename T>
T SetMemory(T value, size_t off = 0)
{
	if (*(T*)(offset + off) != value)
		*(T*)(offset + off) = value;
	return value;
}
#pragma warning( pop )

template<typename T>
T* pointer_get(size_t ptr, int itr = 0, int off = 0)
{
	return (T*)((ptr + off) + (itr * sizeof(T)));
}
template<typename T>
T* pointer_get(uint8_t* data, int itr = 0, int off = 0)
{
	return (T*)((data + off) + (itr * sizeof(T)));
}
template<typename T>
T& reference_get(size_t ptr, int itr = 0, int off = 0)
{
	return *(T*)((ptr + off) + (itr * sizeof(T)));
}
template<typename T>
T& reference_get(uint8_t* data, int itr = 0, int off = 0)
{
	return *(T*)((data + off) + (itr * sizeof(T)));
}

uintptr_t virtual_address_get(uintptr_t addr, bool base = false)
{
	return base ? addr - 0x400000 : addr;
}

template<typename T>
void Copy(uint8_t* data1, uint8_t* data2, std::vector<size_t> offsets)
{
	for (auto offset : offsets)
		*(T*)(data1 + offset) = *(T*)(data2 + offset);
}

inline void* qmemcpy(void* dst, const void* src, size_t cnt)
{
	char* out = (char*)dst;
	const char* in = (const char*)src;
	while (cnt > 0)
	{
		*out++ = *in++;
		--cnt;
	}
	return dst;
}

template<typename T>
inline void* zeromem(T memory)
{
	return memset(memory, 0, sizeof(T));
}

template<size_t size>
struct s_base_definition { uint8_t data[size]; };

ConMan PreferenceManager;
const char* PreferenceManagerAppname;

struct e_lobby_type
{
	enum : int
	{
		_campaign = 0,
		_matchmaking,
		_multiplayer,
		_mapeditor,
		_theater,
		_survival,
		k_number_of_lobby_types
	} value;

	const char* GetName()
	{
		const char* names[]{
			"campaign",
			"matchmaking",
			"multiplayer",
			"mapeditor",
			"theater",
			"survival"
		};
		return names[value];
	}
};

struct e_player_marker_option
{
	enum : int
	{
		_default_colors = 0,
		_team_colors,
		_armor_colors,
		k_number_of_player_marker_options
	} value;

	const char* GetName()
	{
		const char* names[]{
			"default",
			"ally blue",
			"armor colors"
		};
		return names[value];
	}
};

struct e_control_method_option
{
	enum : int
	{
		_keyboard_and_mouse = 0,
		_controller,
		k_number_of_control_methods
	} value;

	const char* GetName()
	{
		const char* names[]{
			"keyboard and mouse",
			"controller"
		};
		return names[value];
	}
};

struct e_toggle_option
{
	enum : int
	{
		_off = 0,
		_on,
		k_number_of_toggle_options
	} value;

	const char* GetName()
	{
		const char* names[]{
			"off",
			"on"
		};
		return names[value];
	}
};

struct e_quality_option
{
	enum : int
	{
		_low = 0,
		_medium,
		_high,
		k_number_of_quality_options
	} value;

	const char* GetName()
	{
		const char* names[]{
			"low",
			"medium",
			"high"
		};
		return names[value];
	}
};

struct e_display_option
{
	enum : int
	{
		_windowed = 0,
		_borderless_windowed,
		_fullscreen,
		k_number_of_display_options
	} value;

	const char* GetName()
	{
		const char* names[]{
			"windowed",
			"borderless (windowed)",
			"fullscreen"
		};
		return names[value];
	}
};

struct e_game_language
{
	enum : int
	{
		_english,
		_japanese,
		_german,
		_french,
		_spanish,
		_mexican,
		_italian,
		_korean,
		_chinese_traditional,
		_chinese_simplified,
		_portuguese,
		_russian,
		k_number_of_game_languages
	} value;

	const char* GetName()
	{
		const char* names[]{
			"english",
			"japanese",
			"german",
			"french",
			"spanish",
			"mexican",
			"italian",
			"korean",
			"chinese-traditional",
			"chinese-simplified",
			"portuguese",
			"russian"
		};
		return names[value];
	}
	const char* GetRegion()
	{
		const char* names[]{
			"en",
			"jpn",
			"de",
			"fr",
			"sp",
			"mx",
			"it",
			"kor",
			"cht",
			"chs",
			"pt",
			"ru"
		};
		return names[value];
	}

	const wchar_t* GetLoadingText()
	{
		const wchar_t* names[]{
			L"LOADING",
			L"読み込んでいます",
			L"LADEN",
			L"CHARGEMENT EN COURS",
			L"CARGANDO",
			L"CARGANDO",
			L"CARICAMENTO",
			L"불러오는 중",
			L"載入中",
			L"載入中",
			L"CARREGANDO",
			L"ЗАГРУЗКА"
		};
		return names[value];
	}

	e_game_language* Print()
	{
		wprintf_s(GetLoadingText());

		return this;
	}
};

bool g_use_default_system_ui_language = true;
auto g_new_system_ui_language = -1;

struct e_scenario_type
{
	enum e : int
	{
		_none = 0,

		_campaign,
		_multiplayer,
		_mainmenu,
		_shared, // not sure

		k_number_of_scenario_types
	} value;

	e_scenario_type(int val)
	{
		if (val >= _none && val < k_number_of_scenario_types)
			value = (e)val;
	}

	const char* GetName()
	{
		const char* names[]{
			"none",
			"campaign",
			"multiplayer",
			"mainmenu",
			"shared"
		};
		return names[value];
	}
};

struct e_game_simulation
{
	enum : char
	{
		_none = 0,
		_local,
		_sync_client,
		_sync_server,
		_dist_client,
		_dist_server,

		k_number_of_game_simulations
	} value;

	const char* GetName()
	{
		const char* names[]{
			"none",
			"local",
			"sync-client",
			"sync-server",
			"dist-client",
			"dist-server"
		};
		return names[value];
	}
};

struct e_game_playback
{
	enum : short
	{
		_none = 0,
		_local,
		_network_server,
		_network_client,

		k_number_of_game_playbacks
	} value;

	const char* GetName()
	{
		const char* names[]{
			"none",
			"local",
			"network-server",
			"network-client"
		};
		return names[value];
	}
};

struct e_difficulty_level
{
	enum : short
	{
		_easy = 0,
		_normal,
		_heroic,
		_legendary,

		k_number_of_difficulty_levels
	} value;

	const char* GetName()
	{
		const char* names[]{
			"easy",
			"normal",
			"heroic",
			"legendary"
		};
		return names[value];
	}
};

struct e_insertion_point
{
	enum : short
	{
		_mission_start = 0,
		_rally_point_alpha,
		_rally_point_bravo,
		_rally_point_charlie,
		_rally_point_delta,
		_rally_point_echo,
		_rally_point_foxtrot,
		_rally_point_golf,
		_rally_point_hotel,

		k_number_of_insertion_points
	} value;

	const char* GetName()
	{
		const char* names[]{
			"Mission Start",
			"Rally Point Alpha",
			"Rally Point Bravo",
			"Rally Point Charlie",
			"Rally Point Delta",
			"Rally Point Echo",
			"Rally Point Foxtrot",
			"Rally Point Golf",
			"Rally Point Hotel"
		};
		return names[value];
	}
};

struct e_metagame_scoring_option
{
	enum : short
	{
		_off = 0,
		_team,
		_free_for_all,

		k_number_of_metagame_scoring_options
	} value;

	const char* GetName()
	{
		const char* names[]{
			"off",
			"team",
			"free for all"
		};
		return names[value];
	}
};

struct s_unit_action_info
{
	const char* Name;
	unsigned short Unknown4;
	unsigned short Unknown6;
};
struct e_unit_action
{
	enum : int
	{
		_death_ping = 0,
		_custom_animation,
		_stop_custom_animation,
		_sync_container,
		_assassinate,
		_get_infected,
		_hostile_morph,
		_resurrect,
		_hard_ping,
		_ping,
		_morph,
		_morph_arrival,
		_infect,
		_posture,
		_posture_exit,
		_vehicle_exit,
		_vehicle_exit_and_detach,
		_vehicle_ejection,
		_vehicle_board,
		_vehicle_enter,
		_open,
		_close,
		_vehicle_exit_immediate,
		_vehicle_flip,
		_climb_attach,
		_climb_detach,
		_wall_lean,
		_wall_leanopen,
		_token,
		_take_off,
		_perch,
		_perch_jump,
		_land,
		_jump,
		_leap_anticipation,
		_leap,
		_leap_recovery,
		_emit_ai,
		_berserk,
		_flurry,
		_deploy_turret,
		_smash,
		_vault,
		_hoist,
		_ai_impulse,
		_melee_ai,
		_weapon_pickup,
		_weapon_trade,
		_primary_weapon_drop,
		_secondary_weapon_drop,
		_surge,
		_phase,
		_stow,
		_draw,
		_infection_spew,
		_kamikaze,
		_primary_weapon_switch,
		_secondary_weapon_switch,
		_grenade,
		_equipment,
		_equipment_animation,
		_equipment_pickup,
		_equipment_drop,
		_melee_player,
		_primary_weapon_primary_reload,
		_primary_weapon_secondary_reload,
		_secondary_weapon_primary_reload,
		_secondary_weapon_secondary_reload,
		_soft_ping,
		_primary_weapon_primary_recoil,
		_primary_weapon_secondary_recoil,
		_primary_weapon_primary_chamber,
		_primary_weapon_secondary_chamber,
		_primary_weapon_primary_charged,
		_primary_weapon_secondary_charged,
		_secondary_weapon_primary_recoil,
		_secondary_weapon_secondary_recoil,
		_secondary_weapon_primary_chamber,
		_secondary_weapon_secondary_chamber,
		_secondary_weapon_primary_charged,
		_secondary_weapon_secondary_charged,
		_primary_weapon_overheat_enter,
		_primary_weapon_overheat_loop,
		_primary_weapon_overheat_exit,
		_secondary_weapon_overheat_enter,
		_secondary_weapon_overheat_loop,
		_secondary_weapon_overheat_exit,

		k_number_of_unit_actions
	} value;

	const char* GetName()
	{
		return reference_get<s_unit_action_info>(0x1947A58, value).Name;
	}
};

struct e_simulation_event
{
	enum : int
	{
		_simulation_event_damage_aftermath = 0,
		_simulation_event_damage_section_response,
		_simulation_event_breakable_surface_damage,
		_simulation_event_projectile_attached,
		_simulation_event_projectile_detonate,
		_simulation_event_projectile_impact_effect,
		_simulation_event_projectile_object_impact_effect,
		_simulation_event_effect_on_pos,
		_simulation_event_game_engine,
		_simulation_event_unit_board_vehicle,
		_simulation_event_unit_pickup,
		_simulation_event_weapon_effect,
		_simulation_event_weapon_empty_click,
		_simulation_event_hit_marker,
		_simulation_event_unit_exit_vehicle,
		_simulation_event_unit_assassinate,
		_simulation_event_player_taunt_request,
		_simulation_event_weapon_fire,
		_simulation_event_unit_equipment_use,
		_simulation_event_weapon_reload,
		_simulation_event_unit_throw_initiate,
		_simulation_event_unit_melee_initiate,
		_simulation_event_weapon_pickup,
		_simulation_event_weapon_put_away,
		_simulation_event_weapon_drop,
		_simulation_event_vehicle_flip,
		_simulation_event_vehicle_trick,
		_simulation_event_device_touch,
		_simulation_event_unit_throw_release,
		_simulation_event_unit_melee_damage,
		_simulation_event_unit_melee_clang,
		_simulation_event_unit_enter_vehicle,
		_simulation_event_game_engine_request_boot_player,
		_simulation_event_player_respawn_request,
		_simulation_event_player_force_base_respawn,
		_simulation_event_unit_equipment_pickup,
		_simulation_event_projectile_supercombine_request,
		_simulation_event_object_refresh,
		_simulation_event_player_editor_request,

		k_number_of_simulation_events
	} value;

	const char* GetName()
	{
		const char* names[]{
			"_simulation_damage_aftermath_event",
			"_simulation_damage_section_response_event",
			"_simulation_breakable_surface_damage_event",
			"_simulation_projectile_attached_event",
			"_simulation_projectile_detonate_event",
			"_simulation_projectile_impact_effect_event",
			"_simulation_projectile_object_impact_effect_event",
			"_simulation_effect_on_pos_event",
			"_simulation_game_engine_event",
			"_simulation_unit_board_vehicle_event",
			"_simulation_unit_pickup_event",
			"_simulation_weapon_effect_event",
			"_simulation_weapon_empty_click_event",
			"_simulation_hit_marker_event",
			"_simulation_unit_exit_vehicle_event",
			"_simulation_unit_assassinate_event",
			"_simulation_player_taunt_request_event",
			"_simulation_weapon_fire_event",
			"_simulation_unit_equipment_use_event",
			"_simulation_weapon_reload_event",
			"_simulation_unit_throw_initiate_event",
			"_simulation_unit_melee_initiate_event",
			"_simulation_weapon_pickup_event",
			"_simulation_weapon_put_away_event",
			"_simulation_weapon_drop_event",
			"_simulation_vehicle_flip_event",
			"_simulation_vehicle_trick_event",
			"_simulation_device_touch_event",
			"_simulation_unit_throw_release_event",
			"_simulation_unit_melee_damage_event",
			"_simulation_unit_melee_clang_event",
			"_simulation_unit_enter_vehicle_event",
			"_simulation_game_engine_request_boot_player_event",
			"_simulation_player_respawn_request_event",
			"_simulation_player_force_base_respawn_event",
			"_simulation_unit_equipment_pickup_event",
			"_simulation_projectile_supercombine_request_event",
			"_simulation_object_refresh_event",
			"_simulation_player_editor_request_event"
		};
		return names[value];
	}
};

struct e_session_overlapped_task_type
{
	enum : short
	{
		_create = 0,
		_delete,
		_modify,
		_add_players,
		_remove_players,
		_start,
		_end,

		k_number_of_session_overlapped_task_types
	} value;

	const char* GetName()
	{
		const char* names[]{
			"create",
			"delete",
			"modify",
			"add players",
			"remove players",
			"start",
			"end"
		};
		return names[value];
	}
};

struct e_privacy_mode
{
	enum : int
	{
		_open_to_public = 0,
		_open_to_friends,
		_invite_only,
		_system_link,
		_offline,

		k_number_of_network_modes
	} value;

	const char* GetName()
	{
		const char* names[]{
			"_open_to_public",
			"_open_to_friends",
			"_invite_only",
			"_system_link",
			"_offline"
		};
		return names[value];
	}
};

struct s_game_system_definition
{
	void(*initialize)();
	void(*dispose)();
	void(*initialize_for_new_map)();
	void(*dispose_from_old_map)();
	void(*prepare_for_new_zone_set)(long, long);
	void(*initialize_for_new_structure_bsp)(long);
	void(*dispose_from_old_structure_bsp)(long);
	void(*change_pvs)(unsigned char*, unsigned char*, bool);
	void(*activation)(unsigned char*, unsigned char*);
	void(*prepare_for_non_bsp_zone_set_switch)(unsigned char*, unsigned char*, unsigned char*);
	void(*initialize_for_new_non_bsp_zone_set)(unsigned char*);
	void(*dispose_from_old_non_bsp_zone_set)(unsigned char*);

	size_t Size()
	{
		return sizeof(*this);
	}
};

struct e_game_system_member
{
	enum e : int
	{
		_initialize = 0,
		_dispose,
		_initialize_for_new_map,
		_dispose_from_old_map,
		_prepare_for_new_zone_set,
		_initialize_for_new_structure_bsp,
		_dispose_from_old_structure_bsp,
		_change_pvs,
		_activation,
		_prepare_for_non_bsp_zone_set_switch,
		_initialize_for_new_non_bsp_zone_set,
		_dispose_from_old_non_bsp_zone_set,

		k_number_of_game_system_members
	} value;

	e_game_system_member(int val)
	{
		if (val >= _initialize && val < k_number_of_game_system_members)
			value = (e)val;
	}

	const char* GetName()
	{
		const char* names[]{
			"initialize",
			"dispose",
			"initialize_for_new_map",
			"dispose_from_old_map",
			"prepare_for_new_zone_set",
			"initialize_for_new_structure_bsp",
			"dispose_from_old_structure_bsp",
			"change_pvs",
			"activation",
			"prepare_for_non_bsp_zone_set_switch",
			"initialize_for_new_non_bsp_zone_set",
			"dispose_from_old_non_bsp_zone_set"
		};
		return names[value];
	}
};

struct e_game_system
{
	enum e : int
	{
		_determinism_debug_manager = 0,
		_optional_cache,
		_screenshots_loader_optional_cache,
		_transport,
		_runtime,
		_structure_renderer,
		_datamine,
		_overlapped,
		_random_math,
		_network,
		_network_webstats,
		_xbox_connection,
		_remote_command,
		_telnet_console,
		_console,
		_input_abstraction,
		_collision_log,
		_levels,
		_visibility_collection,
		_game_grief,
		_achievements,
		_game_state,
		_game_time,
		_profiler,
		_game_allegiance,
		_players,
		_player_control,
		_player_training,
		_game_engine,
		_simulation,
		_scenario,
		_physics_constants,
		_collision_debug,
		_objects,
		_object_early_movers,
		_object_scripting,
		_object_scheduler,
		_object_activation_regions,
		_scenario_kill_trigger_volumes,
		_scenario_sky_objects,
		_soft_ceilings,
		_campaign_metagame_globals,
		_autosave_queue,
		_saved_game_files,
		_fire_teams,
		_rasterizer,
		_render,
		_unknown,
		_breakable_surfaces,
		_director,
		_observer,
		_depth_of_field,
		_water_renderer,
		_render_texture_camera,
		_render_hud_camera,
		_scripted_exposure,
		_render_game_state,
		_decals,
		_effects,
		_point_physics,
		_atmosphere_fog,
		_screen_effects,
		_sound_classes,
		_sound,
		_game_sound_deterministic,
		_game_sound,
		_game_sound_player_effects,
		_rumble,
		_player_effects,
		_simulated_input,
		_interface,
		_chud_cortana_effect,
		_overhead_map,
		_cheats,
		_cinematic,
		_closed_captions,
		_screenshots,
		_player_rewards,
		_hs,
		_recorded_animations,
		_debug_menu,
		_error_report_rendering,
		_object_placement,
		_havok,
		_havok_contact_points,
		_havok_proxies,
		_player_positions,
		_ai,
		_portal_activation,
		_scenario_interpolators,
		_game_save,
		_watch_window,
		_bink_playback,
		_editor,
		_render_state,

		k_number_of_game_systems
	} value;

	e_game_system(int val)
	{
		if (val >= _determinism_debug_manager && val < k_number_of_game_systems)
			value = (e)val;
	}

	uint32_t GetMember(int member, bool base = false)
	{
		return (!base ? 0x1655950 : 0x1655950 - 0x400000) + (sizeof(s_game_system_definition) * value) + (sizeof(uint32_t) * member);
	}
	uint32_t MemberGetRef(int member, bool base = false)
	{
		return *(uint32_t*)GetMember(member);
	}
	bool MemberHasRef(int member, bool base = false)
	{
		return MemberGetRef(member);
	}
	bool MemberRefIsGood(int member, bool base = false)
	{
		return MemberHasRef(member) && *(uint8_t*)MemberGetRef(member) != 0xC3;
	}
	bool MemberRefIsHook(int member, bool base = false)
	{
		return MemberHasRef(member) && MemberGetRef(member) > 0x069B1FFF; // eldorado end address
	}
	bool AnyMemberHasRef()
	{
		bool result = false;
		for (size_t i = 0; i < e_game_system_member::k_number_of_game_system_members; i++)
			if (MemberHasRef(i))
				result = true;
		return result;
	}
	bool AnyMemberRefIsGood()
	{
		bool result = false;
		for (size_t i = 0; i < e_game_system_member::k_number_of_game_system_members; i++)
			if (MemberHasRef(i) && MemberRefIsGood(i))
				result = true;
		return result;
	}
	bool AnyMemberRefIsHook()
	{
		bool result = false;
		for (size_t i = 0; i < e_game_system_member::k_number_of_game_system_members; i++)
			if (MemberHasRef(i) && MemberRefIsGood(i) && MemberRefIsHook(i))
				result = true;
		return result;
	}

	void ReplaceMember(int member, void* func)
	{
		Pointer(GetMember(member)).Write(uint32_t(func));
	}

	const char* GetName()
	{
		const char* names[]{
			"determinism_debug_manager",
			"optional_cache",
			"screenshots_loader_optional_cache",
			"transport",
			"runtime",
			"structure_renderer",
			"datamine",
			"overlapped",
			"random_math",
			"network",
			"network_webstats",
			"xbox_connection",
			"remote_command",
			"telnet_console",
			"console",
			"input_abstraction",
			"collision_log",
			"levels",
			"visibility_collection",
			"game_grief",
			"achievements",
			"game_state",
			"game_time",
			"profiler",
			"game_allegiance",
			"players",
			"player_control",
			"player_training",
			"game_engine",
			"simulation",
			"scenario",
			"physics_constants",
			"collision_debug",
			"objects",
			"object_early_movers",
			"object_scripting",
			"object_scheduler",
			"object_activation_regions",
			"scenario_kill_trigger_volumes",
			"scenario_sky_objects",
			"soft_ceilings",
			"campaign_metagame_globals",
			"autosave_queue",
			"saved_game_files",
			"fire_teams",
			"rasterizer",
			"render",
			"unknown47",
			"breakable_surfaces",
			"director",
			"observer",
			"depth_of_field",
			"water_renderer",
			"render_texture_camera",
			"render_hud_camera",
			"scripted_exposure",
			"render_game_state",
			"decals",
			"effects",
			"point_physics",
			"atmosphere_fog",
			"screen_effects",
			"sound_classes",
			"sound",
			"game_sound_deterministic",
			"game_sound",
			"game_sound_player_effects",
			"rumble",
			"player_effects",
			"simulated_input",
			"interface",
			"chud_cortana_effect",
			"overhead_map",
			"cheats",
			"cinematic",
			"closed_captions",
			"screenshots",
			"player_rewards",
			"hs",
			"recorded_animations",
			"debug_menu",
			"error_report_rendering",
			"object_placement",
			"havok",
			"havok_contact_points",
			"havok_proxies",
			"player_positions",
			"ai",
			"portal_activation",
			"scenario_interpolators",
			"game_save",
			"watch_window",
			"bink_playback",
			"editor",
			"render_state"
		};
		return names[value];
	}
};

struct e_primary_skull
{
	enum : __int32
	{
		_iron = 0,
		_black_eye,
		_tough_luck,
		_catch,
		_fog,
		_famine,
		_thunderstorm,
		_tilt,
		_mythic,

		k_number_of_primary_skulls
	} value;

	bool enabled = false;

	const char* GetName()
	{
		const char* names[]{
			"iron",
			"black eye",
			"tough luck",
			"catch",
			"fog",
			"famine",
			"thunderstorm",
			"tilt",
			"mythic"
		};
		return names[value];
	}
};

struct e_secondary_skull
{
	enum : __int32
	{
		_assassin = 0,
		_blind,
		_superman,
		_birthday_party,
		_daddy,
		_third_person,
		_directors_cut,

		k_number_of_secondary_skulls
	} value;

	bool enabled = false;

	const char* GetName()
	{
		const char* names[]{
			"assassin",
			"blind",
			"superman",
			"birthday party",
			"daddy",
			"third person",
			"directors cut"
		};
		return names[value];
	}
};

struct e_peer_property
{
	enum : int
	{
		_none = 0,
		_network_configuration_unavailable,
		_banhammer_unavailable,
		_player_stats_unavailable,
		_master_hopper_file_unavailable,
		_hopper_specific_file_unavailable,
		_network_configuration_pending,
		_banhammer_pending,
		_player_stats_pending,
		_master_hopper_file_pending,
		_hopper_specific_file_pending,
		_no_map_selected,
		_map_load_failure,
		_map_load_precaching,
		_invalid_film_selected,
		_no_film_selected,
		_too_many_teams,
		_all_observers,
		_too_many_for_local_coop,
		_too_many_for_net_coop,
		_incompatible_for_net_coop,
		_account_not_online_enabled,
		_all_profiles_must_by_live_gold,
		_must_be_connect_to_live,
		_must_be_in_a_live_lobby,
		_invalid_hopper,
		_squad_too_large,
		_squad_too_small,
		_games_played_too_low,
		_games_played_too_high,
		_experience_too_low,
		_experience_too_high,
		_access_bit_not_set,
		_unpaid_in_paid_hopper,
		_paid_in_unpaid_hopper,
		_player_not_in_region,
		_player_not_in_country_code,
		_player_not_in_language,
		_player_not_in_gamerzone,
		_guest_not_allowed,
		_not_beta_player_in_beta_hopper,
		_player_missing_content,
		_player_missing_files,
		_player_missing_required_maps,
		_player_banned_from_matchmaking,
		_not_yet_start_time,
		_end_time_has_passed,
		_custom_games_are_disabled,
		_multiplayer_split_screen,
		_no_live_in_live_lobby,
		_must_have_live_for_alpha,
		_only_one_player_in_theater_alpha,
		_theater_too_many_players,
		_theater_must_have_hard_drive,
		_theater_leader_must_be_host,
		_theater_all_not_compatible,
		_too_many_players_in_forge,
		_user_content_not_permitted,
		_coop_player_missind_hdd,
		_coop_player_hdd_mismatch,
		_coop_player_language_mismatch,
		_invalid_film_language,
		_controller_not_attached,

		k_number_of_peer_properties
	} value;

	const char* GetName()
	{
		const char* names[]{
			"none",
			"network configuration unavailable",
			"banhammer unavailable",
			"player stats unavailable",
			"master hopper file unavailable",
			"hopper specific file unavailable",
			"network configuration pending",
			"banhammer pending",
			"player stats pending",
			"master hopper file pending",
			"hopper specific file pending",
			"no map selected",
			"map load failure",
			"map load precaching",
			"invalid film selected",
			"no film selected",
			"too many teams",
			"all observers",
			"too many for local coop",
			"too many for net coop",
			"incompatible for net coop",
			"account not online enabled",
			"all profiles must by live-gold",
			"must be connect to live",
			"must be in a live lobby",
			"invalid hopper",
			"squad too large",
			"squad too small",
			"games played too low",
			"games played too high",
			"experience too low",
			"experience too high",
			"access bit not set",
			"unpaid in paid hopper",
			"paid in unpaid hopper",
			"player not in region",
			"player not in country code",
			"player not in language",
			"player not in gamerzone",
			"guest not allowed",
			"not beta player in beta hopper",
			"player missing content",
			"player missing files",
			"player missing required maps",
			"player banned from matchmaking",
			"not yet start time",
			"end time has passed",
			"custom games are disabled",
			"multiplayer split screen",
			"no live in live lobby",
			"must have live for alpha",
			"only one player in theater alpha",
			"theater too many players",
			"theater must have hard drive",
			"theater leader must be host",
			"theater all not compatible",
			"too many players in forge",
			"user content not permitted",
			"coop player missind hdd",
			"coop player hdd mismatch",
			"coop player language mismatch",
			"invalid film language",
			"controller not attached"
		};
		return names[value];
	}
};

struct e_network_game_start_mode
{
	enum : signed int
	{
		_none = 0,
		_not_pregame,
		_changing_settings_member,
		_join_in_progress,
		_loading,
		_ready_leader,
		_countdown = 7,
		_error,

		k_number_of_network_game_start_modes
	} value;

	const char* GetName()
	{
		const char* names[]{
			"none",
			"not pregame",
			"changing settings member",
			"join in progress",
			"loading",
			"ready leader",
			"",
			"countdown",
			"error",
		};
		return names[value];
	}
};

struct
{
	std::vector<s_vftable> Array
	{
		{ 0x0160CFDC, 6, "c_http_stream" },
		{ 0x0160CFF8, 6, "c_http_get_stream: c_http_stream" },
		{ 0x0160D014, 6, "c_http_post_stream: c_http_stream" },
		{ 0x01612370, 1, "c_http_stored_buffer_downloader<8033>: c_http_buffer_downloader" },
		{ 0x01612D60, 8, "c_network_channel_client" },
		{ 0x01612D84, 8, "c_network_connection: c_network_channel_client" },
		{ 0x01612DA8, 8, "c_network_message_queue: c_network_channel_client" },
		{ 0x01612DCC, 8, "c_network_channel_simulation_gatekeeper: c_network_channel_client" },
		{ 0x01617240, 16, "c_network_session_parameter_base" },
		{ 0x016182D4, 6, "c_life_cycle_state_handler" },
		{ 0x016182F0, 6, "c_life_cycle_state_handler_none: c_life_cycle_state_handler" },
		{ 0x0161830C, 6, "c_life_cycle_state_handler_pre_game: c_life_cycle_state_handler" },
		{ 0x01618328, 6, "c_life_cycle_state_handler_matchmaking_select_host: c_life_cycle_state_handler" },
		{ 0x01618344, 6, "c_life_cycle_state_handler_start_game: c_life_cycle_state_handler" },
		{ 0x01618360, 6, "c_life_cycle_state_handler_in_match: c_life_cycle_state_handler" },
		{ 0x0161837C, 6, "c_life_cycle_state_handler_in_game: c_life_cycle_state_handler" },
		{ 0x01618398, 6, "c_life_cycle_state_handler_end_game_write_stats: c_life_cycle_state_handler" },
		{ 0x016183B4, 6, "c_life_cycle_state_handler_leaving: c_life_cycle_state_handler" },
		{ 0x016183D0, 6, "c_life_cycle_state_handler_joining: c_life_cycle_state_handler" },
		{ 0x016183EC, 6, "c_life_cycle_state_handler_matchmaking_start: c_life_cycle_state_handler" },
		{ 0x01618408, 6, "c_life_cycle_state_handler_matchmaking_arbitration: c_life_cycle_state_handler" },
		{ 0x01618424, 6, "c_life_cycle_state_handler_matchmaking_find_match_client: c_life_cycle_state_handler" },
		{ 0x01618440, 6, "c_life_cycle_state_handler_matchmaking_find_match: c_life_cycle_state_handler" },
		{ 0x0161845C, 6, "c_life_cycle_state_handler_matchmaking_find_and_assemble_match: c_life_cycle_state_handler" },
		{ 0x01618478, 6, "c_life_cycle_state_handler_matchmaking_assemble_match: c_life_cycle_state_handler" },
		{ 0x01618494, 6, "c_life_cycle_state_handler_matchmaking_prepare_map: c_life_cycle_state_handler" },
		{ 0x016184B0, 6, "c_life_cycle_state_handler_end_match_write_stats: c_life_cycle_state_handler" },
		{ 0x016184CC, 6, "c_life_cycle_state_handler_post_match: c_life_cycle_state_handler" },
		{ 0x0161E914, 1, "c_network_out_of_band_consumer" },
		{ 0x0161E934, 5, "c_network_session: c_network_channel_owner" },
		{ 0x0161E94C, 1, "c_network_message_gateway: c_network_out_of_band_consumer" },
		{ 0x0161E954, 9, "c_replication_scheduler_client" },
		{ 0x0161E97C, 8, "c_replication_scheduler: c_network_channel_client" },
		{ 0x0161E9A0, 9, "c_replication_event_manager_view: c_replication_scheduler_client" },
		{ 0x0161E9C8, 9, "c_replication_entity_manager_view: c_replication_scheduler_client" },
		{ 0x0161E9F0, 9, "c_replication_control_view: c_replication_scheduler_client" },
		{ 0x0161EA18, 5, "c_simulation_watcher: c_network_channel_owner" },
		{ 0x0161F2FC, 1, "c_http_buffer_downloader" },
		{ 0x01620124, 2, "c_allocation_base" },
		{ 0x01650850, 3, "c_optional_cache_user_callback" },
		{ 0x01650860, 4, "c_restricted_memory_callbacks" },
		{ 0x01650874, 6, "c_game_state_compressor_callback: c_optional_cache_user_callback" },
		{ 0x01650884, 5, "c_gamestate_deterministic_allocation_callbacks: c_restricted_memory_callbacks" },
		{ 0x0165089C, 4, "c_gamestate_nondeterministic_allocation_callbacks: c_restricted_memory_callbacks" },
		{ 0x0165A64C, 9, "c_director" },
		{ 0x0165A6E4, 14, "c_null_camera: c_camera" },
		{ 0x0165A9A4, 80, "c_game_engine" },
		{ 0x0165AAEC, 80, "c_sandbox_engine: c_game_engine" },
		{ 0x0165B220, 9, "c_overlapped_task" },
		{ 0x0165D6F4, 3, "c_io_result" },
		{ 0x0165D708, 3, "c_simple_io_result: c_io_result" },
		{ 0x0165DB98, 4, "c_view" },
		{ 0x0165DBAC, 4, "c_ui_view: c_view" },
		{ 0x0165DBBC, 4, "c_fullscreen_view: c_view" },
		{ 0x0165DDA0, 6, "c_tag_resource_collector" },
		{ 0x0165DDBC, 4, "c_tag_resource_demand_callback" },
		{ 0x0165DDD0, 1, "c_user_interface_bitmap_collector" },
		{ 0x0165DDD8, 4, "c_main_render_demand_callback: c_tag_resource_demand_callback" },
		{ 0x0165DDEC, 4, "c_potential_resource_collector: c_tag_resource_collector" },
		{ 0x0165DE08, 6, "c_simple_tag_resource_predictor: c_tag_resource_collector" },
		{ 0x0165DE24, 1, "c_main_render_user_interface_collector: c_user_interface_bitmap_collector" },
		{ 0x0165E0C4, 4, "c_lights_view: c_world_view, c_view" },
		{ 0x0165E0D8, 4, "c_lightmap_shadows_view: c_world_view, c_view" },
		{ 0x0165E0EC, 6, "c_occlusion_view: c_lightmap_shadows_view, c_world_view, c_view" },
		{ 0x0165E108, 4, "c_reflection_view: c_view" },
		{ 0x0165E11C, 4, "c_first_person_view: c_view" },
		{ 0x0165E130, 4, "c_player_view: c_world_view, c_view" },
		{ 0x0165E144, 4, "c_hud_camera_view: c_player_view, c_world_view, c_view" },
		{ 0x0165E3B0, 3, "c_bink_optional_cache_callback: c_optional_cache_user_callback" },
		{ 0x0165E3CC, 2, "c_bink_allocation: c_allocation_base" },
		{ 0x0165FC44, 7, "c_draw_string" },
		{ 0x0165FCB0, 6, "c_font_cache_base" },
		{ 0x0165FCCC, 6, "c_font_cache_mt_safe: c_font_cache_base" },
		{ 0x0165FCE8, 6, "c_null_font_cache: c_font_cache_base" },
		{ 0x0166ACB0, 14, "c_first_person_camera: c_camera" },
		{ 0x0166DB68, 10, "c_gui_selected_item" },
		{ 0x0166DB94, 11, "c_gui_saved_screenshot_selected_item: c_gui_selected_item" },
		{ 0x0166DBC4, 3, "c_screenshots_loader_optional_cache_callback: c_optional_cache_user_callback" },
		{ 0x0167068C, 90, "c_ctf_engine: c_game_engine" },
		{ 0x016707FC, 90, "c_assault_engine: c_game_engine" },
		{ 0x01671F58, 9, "c_game_director: c_director" },
		{ 0x01672130, 14, "c_camera" },
		{ 0x016721D4, 9, "c_debug_director: c_director" },
		{ 0x016722E8, 10, "c_observer_director: c_director" },
		{ 0x01672358, 10, "c_saved_film_director: c_director" },
		{ 0x016723D0, 9, "c_editor_director: c_director" },
		{ 0x016724D4, 14, "c_following_camera: c_camera" },
		{ 0x016725DC, 14, "c_dead_camera: c_camera" },
		{ 0x0167265C, 14, "c_orbiting_camera: c_camera" },
		{ 0x016726D0, 14, "c_flying_camera: c_camera" },
		{ 0x0167280C, 14, "c_scripted_camera: c_camera" },
		{ 0x016728A8, 14, "c_static_camera: c_camera" },
		{ 0x01672920, 14, "c_authored_camera: c_camera" },
		{ 0x0168F3FC, 80, "c_slayer_engine: c_game_engine" },
		{ 0x0168F584, 80, "c_oddball_engine: c_game_engine" },
		{ 0x0168F70C, 80, "c_king_engine: c_game_engine" },
		{ 0x0168F884, 80, "c_juggernaut_engine: c_game_engine" },
		{ 0x0168FA0C, 80, "c_territories_engine: c_game_engine" },
		{ 0x0168FBAC, 80, "c_infection_engine: c_game_engine" },
		{ 0x0168FD2C, 80, "c_vip_engine: c_game_engine" },
		{ 0x01692AD0, 7, "c_hardware_draw_string: c_draw_string" },
		{ 0x01692AF0, 7, "c_rasterizer_draw_string: c_hardware_draw_string, c_draw_string" },
		{ 0x01697104, 7, "c_simple_font_draw_string: c_draw_string" },
		{ 0x01699240, 6, "c_simple_font_cache: c_font_cache_base" },
		{ 0x01699FD4, 3, "c_message" },
		{ 0x01699FE4, 3, "c_controller_input_message: c_message" },
		{ 0x01699FF4, 3, "c_xenon_message: c_message" },
		{ 0x0169A004, 4, "c_load_screen_message: c_message" },
		{ 0x0169A018, 3, "c_screen_custom_message: c_message" },
		{ 0x0169A028, 4, "c_load_alert_screen_message: c_load_screen_message, c_message" },
		{ 0x0169A03C, 4, "c_load_dialog_screen_message: c_load_screen_message, c_message" },
		{ 0x0169A050, 4, "c_load_in_progress_screen_message: c_load_screen_message, c_message" },
		{ 0x0169A064, 4, "c_load_in_progress_mini_screen_message: c_load_in_progress_screen_message, c_load_screen_message, c_message" },
		{ 0x0169A078, 3, "c_dialog_result_message: c_message" },
		{ 0x0169A088, 4, "c_load_spartan_milestone_screen_message: c_load_screen_message, c_message" },
		{ 0x0169A09C, 4, "c_load_spartan_rank_screen_message: c_load_screen_message, c_message" },
		{ 0x0169A144, 7, "c_chud_draw_string: c_hardware_draw_string, c_draw_string" },
		{ 0x0169A8C4, 3, "c_game_tag_parser: c_xml_tag_parser<wchar_t>" },
		{ 0x0169A8D4, 3, "c_simple_game_tag_parser: c_game_tag_parser, c_xml_tag_parser<wchar_t>" },
		{ 0x0169A8E4, 3, "c_magic_string_game_tag_parser: c_game_tag_parser, c_xml_tag_parser<wchar_t>" },
		{ 0x0169A9AC, 55, "c_gui_screen_terminal: c_gui_screen_widget, c_gui_widget" },
		{ 0x0169AD9C, 55, "c_gui_screen_widget: c_gui_widget" },
		{ 0x0169AE7C, 55, "c_gui_screen_codeless_widget: c_gui_screen_widget, c_gui_widget" },
		{ 0x0169AF9C, 55, "c_gui_screen_scoreboard: c_gui_screen_widget, c_gui_widget" },
		{ 0x0169B07C, 4, "c_scoreboard_load_screen_message: c_load_screen_message, c_message" },
		{ 0x0169B094, 28, "c_gui_scoreboard_data: c_gui_ordered_data, c_gui_data" },
		{ 0x0169B148, 2, "c_user_interface_allocation: c_allocation_base" },
		{ 0x0169B1E4, 4, "c_load_boot_betrayer_screen_message: c_load_screen_message, c_message" },
		{ 0x0169B1FC, 55, "c_gui_screen_boot_betrayer: c_gui_screen_widget, c_gui_widget" },
		{ 0x0169B344, 37, "c_gui_widget" },
		{ 0x0169B3DC, 4, "c_sized_user_interface_text<1024>: c_user_interface_text" },
		{ 0x0169B3F4, 43, "c_gui_sized_text_widget<1024>: c_gui_text_widget, c_gui_widget" },
		{ 0x0169B4A4, 4, "c_sized_user_interface_text<256>: c_user_interface_text" },
		{ 0x0169B4BC, 43, "c_gui_sized_text_widget<256>: c_gui_text_widget, c_gui_widget" },
		{ 0x0169B56C, 4, "c_sized_user_interface_text<48>: c_user_interface_text" },
		{ 0x0169B584, 43, "c_gui_sized_text_widget<48>: c_gui_text_widget, c_gui_widget" },
		{ 0x0169B6A0, 4, "c_load_game_camera_list_screen_message: c_load_screen_message, c_message" },
		{ 0x0169B6B4, 55, "c_observer_camera_list_screen: c_gui_screen_widget, c_gui_widget" },
		{ 0x0169B794, 29, "c_camera_list_datasource: c_gui_ordered_data, c_gui_data" },
		{ 0x0169CAC8, 4, "c_user_interface_text" },
		{ 0x0169CCAC, 55, "c_gui_carnage_report_loading_screen: c_gui_screen_in_progress, c_gui_screen_widget, c_gui_widget" },
		{ 0x0169CD8C, 4, "c_load_carnage_report_loading_screen_message: c_load_in_progress_screen_message, c_load_screen_message, c_message" },
		{ 0x0169CDA4, 55, "c_gui_screen_carnage_report: c_gui_screen_widget, c_gui_widget" },
		{ 0x0169CE84, 28, "c_metagame_tally_datasource: c_gui_ordered_data, c_gui_data" },
		{ 0x0169D2C8, 4, "c_load_pregame_selection_screen_message: c_load_screen_message, c_message" },
		{ 0x0169D2DC, 4, "c_load_pregame_players_selection_screen_message: c_load_screen_message, c_message" },
		{ 0x0169D334, 43, "c_gui_custom_bitmap_widget: c_gui_bitmap_widget, c_gui_widget" },
		{ 0x0169D65C, 1, "c_http_stored_buffer_downloader<4096>: c_http_buffer_downloader" },
		{ 0x0169DA04, 27, "c_gui_data" },
		{ 0x0169DA74, 27, "c_gui_data_array: c_gui_data" },
		{ 0x0169DAE4, 27, "c_gui_data_array_test: c_gui_data_array, c_gui_data" },
		{ 0x0169DB54, 28, "c_gui_ordered_data: c_gui_data" },
		{ 0x0169DBCC, 28, "c_gui_tag_datasource: c_gui_ordered_data, c_gui_data" },
		{ 0x0169DDD4, 55, "c_gui_alert_screen_widget: c_gui_screen_widget, c_gui_widget" },
		{ 0x0169DEF4, 55, "c_gui_dialog_screen_widget: c_gui_screen_widget, c_gui_widget" },
		{ 0x0169DFD4, 28, "c_dialog_screen_widget_dialog_items_datasource: c_gui_ordered_data, c_gui_data" },
		{ 0x0169E23C, 11, "c_gui_map_selected_item: c_gui_selected_item" },
		{ 0x0169E26C, 28, "c_gui_map_category_datasource: c_gui_ordered_data, c_gui_data" },
		{ 0x0169E2E4, 29, "c_gui_map_subitem_selectable_item_datasource: c_gui_ordered_data, c_gui_data" },
		{ 0x0169E3F4, 10, "c_gui_difficulty_selected_item: c_gui_selected_item" },
		{ 0x0169E424, 28, "c_gui_difficulty_category_datasource: c_gui_ordered_data, c_gui_data" },
		{ 0x0169E4DC, 11, "c_gui_game_variant_selected_item: c_gui_selected_item" },
		{ 0x0169E50C, 28, "c_gui_game_variant_category_datasource: c_gui_ordered_data, c_gui_data" },
		{ 0x0169E584, 29, "c_gui_game_variant_subitem_selectable_item_datasource: c_gui_ordered_data, c_gui_data" },
		{ 0x0169E6A4, 11, "c_gui_saved_film_selected_item: c_gui_selected_item" },
		{ 0x0169E6D4, 28, "c_gui_saved_film_category_datasource: c_gui_ordered_data, c_gui_data" },
		{ 0x0169E74C, 28, "c_gui_saved_film_subitem_datasource: c_gui_ordered_data, c_gui_data" },
		{ 0x0169E8AC, 29, "c_game_info_datasource: c_gui_ordered_data, c_gui_data" },
		{ 0x0169E924, 4, "c_load_game_browser_screen_message: c_load_screen_message, c_message" },
		{ 0x0169E93C, 55, "c_gui_game_info_screen: c_gui_screen_widget, c_gui_widget" },
		{ 0x0169EA1C, 55, "c_gui_game_browser: c_gui_game_info_screen, c_gui_screen_widget, c_gui_widget" },
		{ 0x0169EB0C, 29, "c_available_games_info_datasource: c_game_info_datasource, c_gui_ordered_data, c_gui_data" },
		{ 0x0169EC2C, 4, "c_load_start_menu_pane_screen_message: c_load_screen_message, c_message" },
		{ 0x0169EC44, 55, "c_start_menu_screen_widget: c_gui_screen_widget, c_gui_widget" },
		{ 0x0169ED24, 4, "c_load_start_menu_screen_message: c_load_screen_message, c_message" },
		{ 0x0169ED3C, 28, "c_start_menu_screen_widget_sidebar_items_datasource: c_gui_ordered_data, c_gui_data" },
		{ 0x0169EDF4, 28, "c_gui_data_proxy: c_gui_data" },
		{ 0x0169EE6C, 55, "c_sandbox_budget_summary_screen_widget: c_gui_screen_widget, c_gui_widget" },
		{ 0x0169EF4C, 55, "c_sandbox_object_menu_screen_widget: c_gui_screen_widget, c_gui_widget" },
		{ 0x0169F02C, 28, "c_gui_placeable_object_datasource: c_gui_ordered_data, c_gui_data" },
		{ 0x0169F0A4, 29, "c_gui_budget_range_datasource: c_gui_ordered_data, c_gui_data" },
		{ 0x0169F11C, 4, "c_load_object_creation_screen_message: c_load_screen_message, c_message" },
		{ 0x0169F130, 4, "c_load_object_property_panel_screen_message: c_load_screen_message, c_message" },
		{ 0x0169F144, 4, "c_load_budget_screen_message: c_load_screen_message, c_message" },
		{ 0x0169F15C, 28, "c_sandbox_budget_items_datasource: c_gui_data_proxy, c_gui_data" },
		{ 0x0169F214, 55, "c_sandbox_object_properties_screen_widget: c_gui_screen_widget, c_gui_widget" },
		{ 0x0169F2F4, 28, "c_gui_property_value_datasource: c_gui_ordered_data, c_gui_data" },
		{ 0x0169F36C, 28, "c_sandbox_object_properties_items_datasource: c_gui_data_proxy, c_gui_data" },
		{ 0x0169F424, 55, "c_saved_film_control_pad: c_gui_screen_widget, c_gui_widget" },
		{ 0x0169F59C, 55, "c_saved_film_take_screenshot: c_gui_screen_widget, c_gui_widget" },
		{ 0x0169F7A4, 55, "c_saved_film_snippet_screen: c_gui_screen_widget, c_gui_widget" },
		{ 0x0169F8C4, 55, "c_error_dialog_screen_widget: c_gui_screen_widget, c_gui_widget" },
		{ 0x0169F9A4, 55, "c_error_dialog_ok_screen_widget: c_error_dialog_screen_widget, c_gui_screen_widget, c_gui_widget" },
		{ 0x0169FACC, 55, "c_gui_screen_alpha_motd: c_gui_screen_widget, c_gui_widget" },
		{ 0x0169FBAC, 4, "c_load_alpha_motd_screen_message: c_load_screen_message, c_message" },
		{ 0x0169FC10, 1, "c_http_stored_buffer_downloader<4665>: c_http_buffer_downloader" },
		{ 0x0169FC1C, 55, "c_main_menu_screen_widget: c_gui_screen_widget, c_gui_widget" },
		{ 0x0169FCFC, 4, "c_load_campaign_select_difficulty_screen_message: c_load_screen_message, c_message" },
		{ 0x0169FD7C, 56, "c_start_menu_game_campaign: c_start_menu_pane_screen_widget, c_gui_screen_widget, c_gui_widget" },
		{ 0x0169FF1C, 56, "c_start_menu_game_multiplayer: c_start_menu_pane_screen_widget, c_gui_screen_widget, c_gui_widget" },
		{ 0x016A008C, 56, "c_start_menu_game_editor: c_start_menu_pane_screen_widget, c_gui_screen_widget, c_gui_widget" },
		{ 0x016A0174, 28, "c_gui_gametype_category_datasource: c_gui_ordered_data, c_gui_data" },
		{ 0x016A01E8, 4, "c_load_legal_screen_message: c_load_screen_message, c_message" },
		{ 0x016A02C4, 56, "c_start_menu_game_saved_film: c_start_menu_pane_screen_widget, c_gui_screen_widget, c_gui_widget" },
		{ 0x016A03E8, 1, "c_http_stored_buffer_downloader<2721>: c_http_buffer_downloader" },
		{ 0x016A03F0, 1, "c_http_stored_buffer_downloader<61440>: c_http_buffer_downloader" },
		{ 0x016A03FC, 56, "c_start_menu_headquartersc_start_menu_headquarters: c_start_menu_pane_screen_widget, c_gui_screen_widget, c_gui_widget" },
		{ 0x016A056C, 56, "c_gui_start_menu_hq_service_record_pane: c_start_menu_pane_screen_widget, c_gui_screen_widget, c_gui_widget" },
		{ 0x016A0654, 56, "c_gui_start_menu_hq_service_record: c_gui_start_menu_hq_service_record_pane, c_start_menu_pane_screen_widget, c_gui_screen_widget, c_gui_widget" },
		{ 0x016A073C, 28, "c_gui_start_menu_hq_service_record_insignia_datasource: c_gui_ordered_data, c_gui_data" },
		{ 0x016A0844, 56, "c_gui_start_menu_hq_service_record_file_share: c_gui_start_menu_hq_service_record_pane, c_start_menu_pane_screen_widget, c_gui_screen_widget, c_gui_widget" },
		{ 0x016A0928, 4, "c_load_file_share_choose_category_screen_message: c_load_screen_message, c_message" },
		{ 0x016A093C, 4, "c_load_file_share_choose_item_screen_message: c_load_screen_message, c_message" },
		{ 0x016A0950, 4, "c_load_file_share_item_selected_screen_message: c_load_screen_message, c_message" },
		{ 0x016A0964, 4, "c_load_transfers_item_selected_screen_message: c_load_screen_message, c_message" },
		{ 0x016A097C, 28, "c_gui_file_share_slots_datasource: c_gui_ordered_data, c_gui_data" },
		{ 0x016A0ACC, 55, "c_gui_start_menu_hq_service_record_file_share_choose_category: c_gui_screen_widget, c_gui_widget" },
		{ 0x016A0BEC, 55, "c_gui_start_menu_hq_service_record_file_share_choose_item: c_gui_screen_widget, c_gui_widget" },
		{ 0x016A0CCC, 28, "c_gui_content_item_datasource: c_gui_ordered_data, c_gui_data" },
		{ 0x016A0E3C, 55, "c_gui_start_menu_hq_service_record_file_share_item_selected: c_gui_screen_widget, c_gui_widget" },
		{ 0x016A0F1C, 4, "c_load_screenshots_file_share_previewer_screen_message: c_load_screen_message, c_message" },
		{ 0x016A0F34, 28, "c_gui_file_share_selected_item_datasource: c_gui_ordered_data, c_gui_data" },
		{ 0x016A10B4, 56, "c_gui_start_menu_hq_screenshots: c_start_menu_pane_screen_widget, c_gui_screen_widget, c_gui_widget" },
		{ 0x016A1198, 4, "c_load_screenshots_viewer_screen_message: c_load_screen_message, c_message" },
		{ 0x016A11AC, 4, "c_load_hq_screenshots_options_screen_message: c_load_screen_message, c_message" },
		{ 0x016A11C4, 28, "c_player_screenshots_datasource: c_gui_ordered_data, c_gui_data" },
		{ 0x016A133C, 55, "c_gui_start_menu_hq_screenshots_options: c_gui_screen_widget, c_gui_widget" },
		{ 0x016A14F4, 57, "c_screenshots_screen_widget_base: c_gui_screen_widget, c_gui_widget" },
		{ 0x016A15DC, 57, "c_screenshots_viewer_screen_widget: c_screenshots_screen_widget_base, c_gui_screen_widget, c_gui_widget" },
		{ 0x016A16C4, 1, "c_http_stored_buffer_downloader<317440>: c_http_buffer_downloader" },
		{ 0x016A16CC, 57, "c_screenshots_file_share_previewer_screen_widget: c_screenshots_screen_widget_base, c_gui_screen_widget, c_gui_widget" },
		{ 0x016A1824, 56, "c_gui_start_menu_hq_transfers: c_start_menu_pane_screen_widget, c_gui_screen_widget, c_gui_widget" },
		{ 0x016A190C, 28, "c_active_transfers_datasource: c_gui_ordered_data, c_gui_data" },
		{ 0x016A19C4, 55, "c_gui_start_menu_hq_transfers_item_selected: c_gui_screen_widget, c_gui_widget" },
		{ 0x016A1AA4, 28, "c_gui_transfers_selected_item_datasource: c_gui_ordered_data, c_gui_data" },
		{ 0x016A1B5C, 56, "c_start_menu_settings: c_start_menu_pane_screen_widget, c_gui_screen_widget, c_gui_widget" },
		{ 0x016A1C84, 56, "c_start_menu_settings_controls: c_start_menu_pane_screen_widget, c_gui_screen_widget, c_gui_widget" },
		{ 0x016A1D6C, 28, "c_settings_controls_sidebar_items_datasource: c_gui_data_proxy, c_gui_data" },
		{ 0x016A1E94, 56, "c_start_menu_settings_controls_button: c_start_menu_pane_screen_widget, c_gui_screen_widget, c_gui_widget" },
		{ 0x016A1FBC, 56, "c_start_menu_settings_controls_thumbstick: c_start_menu_pane_screen_widget, c_gui_screen_widget, c_gui_widget" },
		{ 0x016A20E4, 56, "c_start_menu_settings_appearance: c_start_menu_pane_screen_widget, c_gui_screen_widget, c_gui_widget" },
		{ 0x016A22CC, 56, "c_start_menu_settings_appearance_model: c_start_menu_pane_screen_widget, c_gui_screen_widget, c_gui_widget" },
		{ 0x016A23B4, 28, "c_model_customization_selections_datasource: c_gui_ordered_data, c_gui_data" },
		{ 0x016A242C, 28, "c_settings_appearance_model_sidebar_items_datasource: c_gui_data_proxy, c_gui_data" },
		{ 0x016A2554, 56, "c_start_menu_settings_appearance_colors: c_start_menu_pane_screen_widget, c_gui_screen_widget, c_gui_widget" },
		{ 0x016A263C, 39, "c_color_swatch_focus_list_item_widget: c_gui_list_item_widget, c_gui_widget" },
		{ 0x016A27B4, 56, "c_start_menu_settings_camera: c_start_menu_pane_screen_widget, c_gui_screen_widget, c_gui_widget" },
		{ 0x016A289C, 28, "c_settings_camera_sidebar_items_datasource: c_gui_data_proxy, c_gui_data" },
		{ 0x016A298C, 56, "c_start_menu_settings_display: c_start_menu_pane_screen_widget, c_gui_screen_widget, c_gui_widget" },
		{ 0x016A2A74, 28, "c_settings_display_sidebar_items_datasource: c_gui_data_proxy, c_gui_data" },
		{ 0x016A2B64, 56, "c_start_menu_settings_film_autosave: c_start_menu_pane_screen_widget, c_gui_screen_widget, c_gui_widget" },
		{ 0x016A2C4C, 28, "c_settings_film_autosave_sidebar_items_datasource: c_gui_data_proxy, c_gui_data" },
		{ 0x016A2D4C, 55, "c_gui_screen_in_progress: c_gui_screen_widget, c_gui_widget" },
		{ 0x016A2E6C, 55, "c_gui_spartan_milestone: c_gui_screen_widget, c_gui_widget" },
		{ 0x016A2F8C, 55, "c_gui_spartan_rank: c_gui_screen_widget, c_gui_widget" },
		{ 0x016A30B4, 55, "c_gui_screen_campaign_select_difficulty: c_gui_screen_widget, c_gui_widget" },
		{ 0x016A31DC, 55, "c_gui_screen_campaign_select_level: c_gui_screen_widget, c_gui_widget" },
		{ 0x016A32BC, 10, "c_gui_level_selected_item: c_gui_selected_item" },
		{ 0x016A32EC, 29, "c_gui_survival_level_datasource: c_gui_ordered_data, c_gui_data" },
		{ 0x016A3434, 55, "c_gui_screen_campaign_select_scoring: c_gui_screen_campaign_settings, c_gui_screen_widget, c_gui_widget" },
		{ 0x016A35DC, 55, "c_gui_screen_campaign_select_skulls: c_gui_screen_campaign_settings, c_gui_screen_widget, c_gui_widget" },
		{ 0x016A36BC, 28, "c_gui_primary_skulls_data: c_gui_ordered_data, c_gui_data" },
		{ 0x016A3734, 28, "c_gui_secondary_skulls_data: c_gui_ordered_data, c_gui_data" },
		{ 0x016A37F0, 1, "c_gui_screen_pregame_lobby_campaign: c_gui_screen_pregame_lobby, c_gui_screen_widget, c_gui_widget" },
		{ 0x016A38F4, 4, "c_load_campaign_select_level_screen_message: c_load_screen_message, c_message" },
		{ 0x016A39DC, 63, "c_gui_screen_pregame_lobby_survival: c_gui_screen_pregame_lobby, c_gui_screen_widget, c_gui_widget" },
		{ 0x016A3B24, 63, "c_gui_screen_pregame_lobby_multiplayer: c_gui_screen_pregame_lobby, c_gui_screen_widget, c_gui_widget" },
		{ 0x016A3CCC, 1, "c_http_stored_buffer_downloader<2465>: c_http_buffer_downloader" },
		{ 0x016A3CD4, 1, "c_http_stored_buffer_downloader<102400>: c_http_buffer_downloader" },
		{ 0x016A3CDC, 63, "c_gui_screen_pregame_lobby_matchmaking: c_gui_screen_pregame_lobby, c_gui_screen_widget, c_gui_widget" },
		{ 0x016A3EF4, 63, "c_gui_screen_pregame_lobby_mapeditor: c_gui_screen_pregame_lobby, c_gui_screen_widget, c_gui_widget" },
		{ 0x016A4064, 63, "c_gui_screen_pregame_lobby_theater: c_gui_screen_pregame_lobby, c_gui_screen_widget, c_gui_widget" },
		{ 0x016A4234, 55, "c_gui_screen_pregame_switch_lobby: c_gui_screen_widget, c_gui_widget" },
		{ 0x016A435C, 55, "c_gui_screen_pregame_selection: c_gui_screen_widget, c_gui_widget" },
		{ 0x016A453C, 55, "c_gui_screen_matchmaking_advanced_options: c_gui_screen_widget, c_gui_widget" },
		{ 0x016A470C, 55, "c_gui_screen_postgame_lobby: c_gui_screen_widget, c_gui_widget" },
		{ 0x016A4870, 4, "c_load_player_select_screen_message: c_load_screen_message, c_message" },
		{ 0x016A4884, 55, "c_gui_player_select_screen_widget: c_gui_screen_widget, c_gui_widget" },
		{ 0x016A4964, 28, "c_player_select_actions_datasource: c_gui_ordered_data, c_gui_data" },
		{ 0x016A49DC, 28, "c_player_select_medals_datasource: c_gui_ordered_data, c_gui_data" },
		{ 0x016A4D2C, 55, "c_gui_screen_maximum_party_size: c_gui_screen_widget, c_gui_widget" },
		{ 0x016A4E4C, 4, "c_load_game_details_screen_message: c_load_screen_message, c_message" },
		{ 0x016A4E64, 55, "c_gui_game_details: c_gui_game_info_screen, c_gui_screen_widget, c_gui_widget" },
		{ 0x016A4F44, 29, "c_specific_game_info_datasource: c_game_info_datasource, c_gui_ordered_data, c_gui_data" },
		{ 0x016A5004, 4, "c_load_game_options_screen_message: c_load_screen_message, c_message" },
		{ 0x016A501C, 55, "c_gui_screen_game_options: c_gui_screen_widget, c_gui_widget" },
		{ 0x016A50FC, 28, "c_game_options_parameter_datasource: c_gui_ordered_data, c_gui_data" },
		{ 0x016A5174, 28, "c_game_options_category_datasource: c_gui_ordered_data, c_gui_data" },
		{ 0x016A52EC, 55, "c_gui_screen_alpha_legal: c_gui_screen_widget, c_gui_widget" },
		{ 0x016A540C, 55, "c_gui_screen_alpha_locked_down: c_gui_screen_widget, c_gui_widget" },
		{ 0x016A5534, 55, "c_gui_screen_forge_legal: c_gui_screen_widget, c_gui_widget" },
		{ 0x016A5654, 55, "c_gui_screen_matchmaking_searching: c_gui_screen_widget, c_gui_widget" },
		{ 0x016A591C, 55, "c_gui_screen_matchmaking_match_found: c_gui_screen_widget, c_gui_widget" },
		{ 0x016A5E34, 55, "c_motd_popup_screen_widget: c_gui_screen_widget, c_gui_widget" },
		{ 0x016A5F14, 4, "c_motd_popup_screen_message: c_load_screen_message, c_message" },
		{ 0x016A5F6C, 38, "c_gui_group_widget: c_gui_widget" },
		{ 0x016A600C, 39, "c_gui_button_key_widget: c_gui_group_widget, c_gui_widget" },
		{ 0x016A60EC, 38, "c_gui_list_widget: c_gui_widget" },
		{ 0x016A61CC, 41, "c_gui_bitmap_widget: c_gui_widget" },
		{ 0x016A62F4, 39, "c_gui_list_item_widget: c_gui_widget" },
		{ 0x016A63D4, 43, "c_gui_text_widget: c_gui_widget" },
		{ 0x016A6564, 38, "c_gui_model_widget: c_gui_widget" },
		{ 0x016A6684, 29, "c_gui_game_results_data: c_gui_ordered_data, c_gui_data" },
		{ 0x016A66FC, 28, "c_gui_game_results_team_data: c_gui_ordered_data, c_gui_data" },
		{ 0x016A6774, 28, "c_gui_top_medals_data: c_gui_ordered_data, c_gui_data" },
		{ 0x016A685C, 28, "c_gui_campaign_results_data: c_gui_ordered_data, c_gui_data" },
		{ 0x016A6910, 3, "c_html_comment_game_tag_parser: c_simple_game_tag_parser, c_game_tag_parser, c_xml_tag_parser<wchar_t>" },
		{ 0x016A6920, 3, "c_html_line_break_game_tag_parser: c_simple_game_tag_parser, c_game_tag_parser, c_xml_tag_parser<wchar_t>" },
		{ 0x016A6930, 3, "c_html_paragraph_game_tag_parser: c_simple_game_tag_parser, c_game_tag_parser, c_xml_tag_parser<wchar_t>" },
		{ 0x016A6940, 3, "c_html_paragraph_close_game_tag_parser: c_simple_game_tag_parser, c_game_tag_parser, c_xml_tag_parser<wchar_t>" },
		{ 0x016A6950, 3, "c_html_div_game_tag_parser: c_simple_game_tag_parser, c_game_tag_parser, c_xml_tag_parser<wchar_t>" },
		{ 0x016A6960, 3, "c_html_div_close_game_tag_parser: c_simple_game_tag_parser, c_game_tag_parser, c_xml_tag_parser<wchar_t>" },
		{ 0x016A6970, 3, "c_html_font_game_tag_parser: c_simple_game_tag_parser, c_game_tag_parser, c_xml_tag_parser<wchar_t>" },
		{ 0x016A6980, 3, "c_html_font_close_game_tag_parser: c_simple_game_tag_parser, c_game_tag_parser, c_xml_tag_parser<wchar_t>" },
		{ 0x016A6990, 3, "c_color_game_tag_parser: c_simple_game_tag_parser, c_game_tag_parser, c_xml_tag_parser<wchar_t>" },
		{ 0x016A69A0, 3, "c_color_close_game_tag_parser: c_simple_game_tag_parser, c_game_tag_parser, c_xml_tag_parser<wchar_t>" },
		{ 0x016A6BE0, 3, "c_start_menu_custom_message: c_screen_custom_message, c_message" },
		{ 0x016A6BF4, 56, "c_start_menu_pane_screen_widget: c_gui_screen_widget, c_gui_widget" },
		{ 0x016A6D9C, 28, "c_gui_level_category_datasource: c_gui_ordered_data, c_gui_data" },
		{ 0x016A6E14, 29, "c_gui_level_subitem_selectable_item_datasource: c_gui_ordered_data, c_gui_data" },
		{ 0x016A6ECC, 55, "c_gui_screen_campaign_settings: c_gui_screen_widget, c_gui_widget" },
		{ 0x016A6FF4, 63, "c_gui_screen_pregame_lobby: c_gui_screen_widget, c_gui_widget" },
		{ 0x016A7384, 10, "c_gui_network_mode_selected_item: c_gui_selected_item" },
		{ 0x016A73B4, 28, "c_gui_network_mode_category_datasource: c_gui_ordered_data, c_gui_data" },
		{ 0x016A742C, 29, "c_gui_network_mode_subitem_selectable_item_datasource: c_gui_ordered_data, c_gui_data" },
		{ 0x016A74E4, 10, "c_gui_hopper_selected_item: c_gui_selected_item" },
		{ 0x016A7514, 28, "c_gui_hopper_category_datasource: c_gui_ordered_data, c_gui_data" },
		{ 0x016A758C, 29, "c_gui_hopper_subitem_selectable_item_datasource: c_gui_ordered_data, c_gui_data" },
		{ 0x016A7644, 30, "c_gui_roster_data: c_gui_ordered_data, c_gui_data" },
		{ 0x016A76C4, 30, "c_gui_active_roster_data: c_gui_roster_data, c_gui_ordered_data, c_gui_data" },
		{ 0x016A7744, 30, "c_gui_static_roster_data: c_gui_roster_data, c_gui_ordered_data, c_gui_data" },
		{ 0x016A7814, 38, "c_gui_roster_list_widget: c_gui_list_widget, c_gui_widget" },
		{ 0x016AA5D0, 4, "c_load_terminal_screen_message: c_load_screen_message, c_message" },
		{ 0x017695E4, 9, "c_achievements_enumerate_overlapped_task: c_overlapped_task" },
		{ 0x01769634, 9, "c_achievement_write_overlapped_task: c_overlapped_task" },
		{ 0x0176976C, 9, "c_online_marketplace_enumerate_offers_task: c_overlapped_task" },
		{ 0x01769794, 9, "c_online_marketplace_enumerate_assets_task: c_overlapped_task" },
		{ 0x017697BC, 9, "c_online_marketplace_consume_asset_task: c_overlapped_task" },
		{ 0x017697E4, 9, "c_online_marketplace_purchase_task: c_overlapped_task" },
		{ 0x01769AB0, 9, "c_online_find_friend_task: c_overlapped_task" },
		{ 0x0176A1CC, 2, "c_xml_tag_parser<wchar_t>" },
		{ 0x0176A1D8, 2, "c_wchar_retrad_parser: c_xml_tag_parser<wchar_t>" },
		{ 0x0176A1F4, 2, "c_xml_parser<wchar_t>" },

		/*
				{ 0x016D6860, 6, "net::REMOTE_BINLOGGER"}
		*/
	};

	auto* AddEndAddress(int end_address)
	{
		for (auto vftable : Array)
			vftable.UpdateEndAddress(end_address);

		return this;
	}
	s_vftable at(int address)
	{
		for (auto vftable : Array)
			if (address == vftable.Address)
				return vftable;

		return s_vftable(-1, -1, (static_cast<std::stringstream const&>(std::stringstream() << "0x" << std::hex << address)).str());
	}
	void Print()
	{
		for (auto vftable : Array)
			vftable.PrintMembers();
	}
} g_vftables;

struct e_session_composition
{
	enum : signed int
	{
		_none = 0,
		_session_state_not_ready,
		_no_hopper_configuration,
		_hopper_mismatch,
		_no_game_set,
		_session_not_ready_no_stats,
		_session_not_ready_banned,
		_session_not_ready_no_controller,
		_invalid_player_count,
		_invalid_party_composition,
		_guests_not_allowed,
		_cant_pick_teams,
		_cant_even_out_teams,
		_big_party_no_rabble_yet,
		_big_party_teams_exceed_imbalance,
		_big_party_count_exceeds_teams,
		_no_signed_in_local_players,
		_invalid_skill_range,
		_success,

		k_number_of_session_compositions
	} value;

	const char* GetName()
	{
		const char* names[]{
			"none",
			"session state not ready",
			"no hopper configuration",
			"hopper mismatch",
			"no game set",
			"session not ready no stats",
			"session not ready banned",
			"session not ready no controller",
			"invalid player count",
			"invalid party composition",
			"guests not allowed",
			"cant pick teams",
			"cant even out teams",
			"big party no rabble yet",
			"big party teams exceed imbalance",
			"big party count exceeds teams",
			"no signed in local players",
			"invalid skill range",
			"success"
		};
		return names[value];
	}
};

struct e_controller_achievement_state
{
	enum : signed int
	{
		_achievements_are_disabled = 0,
		_profile_is_not_in_use,
		_profile_is_temporary,
		_controller_is_guest,
		_controller_is_not_attached_to_an_active_player,
		_game_conditions_dont_allow_achievement,
		_controller_already_has_achievement,

		k_number_of_controller_achievement_states
	} value;

	const char* GetName()
	{
		const char* names[]{
			"achievements are disabled",
			"profile is not in use",
			"profile is temporary",
			"controller is guest",
			"controller is not attached to an active player",
			"game conditions don't allow achievement",
			"controller already has achievement"
		};
		return names[value];
	}
};

#pragma warning( push )
#pragma warning( disable : 4996 )
namespace Blam
{
	struct StringIDCacheHeader
	{
		int32_t StringCount;
		int32_t StringDataSize;
	};

	struct StringIDCache
	{
		StringIDCacheHeader Header;
		char* Data;
		char** Strings;

		StringIDCache();
		~StringIDCache();

		static StringIDCache Instance;

		bool Load(const std::string& path);
		char* GetString(const uint32_t stringID);
		void PrintStrings();
	};

	StringIDCache StringIDCache::Instance;

	StringIDCache::StringIDCache()
		: Header(), Data(nullptr), Strings(nullptr)
	{
	}

	StringIDCache::~StringIDCache()
	{
		if (Strings != nullptr)
			delete[] Strings;

		if (Data != nullptr)
			delete[] Data;
	}

	bool StringIDCache::Load(const std::string& path)
	{
		std::ifstream stream;
		stream.open(path + "string_ids.dat", std::ios::binary);

		if (!stream.good())
			return false;

		stream.read((char*)&Header, sizeof(StringIDCacheHeader));

		Data = new char[Header.StringDataSize + 1];
		Strings = new char* [Header.StringCount];

		auto* stringOffsets = new int32_t[Header.StringCount];
		stream.read((char*)stringOffsets, (Header.StringCount * sizeof(int32_t)));

		auto dataOffset = stream.tellg().seekpos();
		stream.read(Data, Header.StringDataSize);
		Data[Header.StringDataSize] = '\0';

		for (auto i = 0; i < Header.StringCount; i++)
		{
			if (stringOffsets[i] < 0 || stringOffsets[i] >= Header.StringDataSize)
			{
				Strings[i] = nullptr;
				continue;
			}

			Strings[i] = Data + stringOffsets[i];
		}

		stream.close();
		delete[] stringOffsets;

		return true;
	}

	char* StringIDCache::GetString(const uint32_t StringID)
	{
		int32_t setMin = 0x1;
		int32_t setMax = 0xF1E;
		int32_t setOffsets[] = { 0x90F, 0x1, 0x685, 0x720, 0x7C4, 0x778, 0x7D0, 0x8EA, 0x902 };

		int32_t set = (int32_t)((StringID >> 16) & 0xFF);
		int32_t index = (int32_t)(StringID & 0xFFFF);

		if (set == 0 && (index < setMin || index > setMax))
			return Strings[index];

		if (set < 0 || set >= 9)
			return nullptr;

		if (set == 0)
			index -= setMin;

		return Strings[index + setOffsets[set]];
	}

	void StringIDCache::PrintStrings()
	{
		for (size_t i = 0; i < 0xFFFF; i++)
			printf_s("[0x%04X, %s]\n", i, GetString(i));
	}
}
#pragma warning( pop )

struct string_id
{
	uint32_t value;

	const char* GetName()
	{
		return Blam::StringIDCache::Instance.GetString(value);
	}
};

#pragma pack(push, 1)
struct XnkAddr
{
	uint32_t unsigned0;
	uint16_t unsigned4;
	uint16_t unsigned6;
	uint8_t unsigned8[8];

	size_t Size()
	{
		return sizeof(*this);
	}

	char* String()
	{
		static char string[0x40u];
		sprintf_s(
			string,
			37u,
			"%08lX-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
			unsigned0,
			unsigned4,
			unsigned6,
			unsigned8[0],
			unsigned8[1],
			unsigned8[2],
			unsigned8[3],
			unsigned8[4],
			unsigned8[5],
			unsigned8[6],
			unsigned8[7]
		);
		return string;
	}
};
#pragma pack(pop)

struct s_game_options_base // this remains the same alpha->12.x
{
	e_scenario_type ScenarioType = e_scenario_type(-1);
	e_game_simulation GameSimulation;
	int16_t FrameLimit;
	int32_t GameInstance;
	int16_t wordC[2];
	int32_t RandomSeed;
	int32_t Language;
	int32_t DeterminismVersion;
	int32_t CampaignId;
	int32_t map_id;
	char scenario_path[260];
	int16_t ZonesetIndex;
	uint8_t byte12A;
	uint8_t byte12B;
	uint8_t byte12C;
	uint8_t byte12D;
	bool IsPlaytest;
	uint8_t byte12F;
	e_game_playback GamePlayback;
	uint8_t byte132;
	uint8_t byte133;
	uint32_t dword134;
	uint32_t dword138;
	e_difficulty_level DifficultyLevel;
	e_insertion_point InsertionPoint;
	e_metagame_scoring_option MetagameScoringOption;
	uint8_t MetagameEnabled;
	uint8_t SurvivalModeEnabled;
	uint8_t byte144;
	uint8_t byte145;
	uint8_t PlayerArmaments[0x78];
	int16_t byte10A;
	uint8_t GameProgression[0x80];
	uint32_t SkullsPrimary;
	uint32_t SkullsSecondary;
	uint8_t byte248[0x80];
	uint8_t byte2AC;
	uint8_t byte2AD[7];
	uint8_t byte2B4[0x5C];
	char GameVariant[0x264]; // Blam::GameVariant
	char MapVariant[0xE090]; // Blam::MapVariant

	size_t Size()
	{
		return sizeof(*this);
	}
};
static_assert(sizeof(s_game_options_base) == 0xE620u, "s_game_options_info wrong size");

struct s_game_options : s_game_options_base
{
	uint8_t MachineArray[0x128];
	struct
	{
		uint8_t IsValid;
		uint8_t byte1;
		uint16_t word2;
		uint32_t dword4;
		uint8_t __unknown8[0x18];
		char PlayerProperties[0x1620]; // Blam::Players::PlayerProperties
	} InitialParticipantsArray[16];

	size_t Size()
	{
		return sizeof(*this);
	}
	s_game_options* SetScenarioType(int val)
	{
		ScenarioType = e_scenario_type(val);

		return this;
	}
	// only needs the last part `scenario_path` I.E. s3d_tutorial
	// the game must iterate over scenarios until a match is found, if no match is found the game crashes
	s_game_options* SetScenarioPath(const char* val)
	{
		memset(scenario_path, 0, 260);
		strncpy(scenario_path, val, 260);

		return this;
	}
	s_game_options* GameVariant_SetGameType(int32_t val)
	{
		*(int32_t*)GameVariant = val;

		return this;
	}
	s_game_options* GameVariant_SetTeamGame(bool val)
	{
		GameVariant[0x124] = val;

		return this;
	}
	s_game_options* GameVariant_SetTimeLimit(uint8_t val)
	{
		GameVariant[0x125] = val;

		return this;
	}
	s_game_options* GameVariant_SetRespawnTime(uint8_t val)
	{
		GameVariant[0x12D] = val;

		return this;
	}
	int LoadIntoGlobalGameOptions(bool is_force_loaded = false)
	{
		if (is_force_loaded)
		{
			SetScenarioPath(ConfigManager.GetString("ForceLoad", "ScenarioPath"));
			SetScenarioType(ConfigManager.GetInt("ForceLoad", "ScenarioType"));
			GameVariant_SetGameType(ConfigManager.GetInt("ForceLoad", "GameType"));
			GameVariant_SetTeamGame(ConfigManager.GetBool("ForceLoad", "TeamGame"));
			GameVariant_SetTimeLimit(ConfigManager.GetInt("ForceLoad", "TimeLimit"));
			GameVariant_SetRespawnTime(ConfigManager.GetInt("ForceLoad", "RespawnTime"));
		}
		printf_s("Scenario(%s, %s).Launch()\n", ScenarioType.GetName(), scenario_path);

		auto v1 = this == 0;
		if (this)
		{
			memmove((void*)0x2391800, this, 0x24B48u);
			v1 = this == 0;
		}

		SetMemory<0x23917F1>(v1);
		SetMemory<0x23917F0>(true);

		// substitute timeGetTime() with GetTickCount64()
		auto result = (int)GetTickCount64();
		if (!this && !is_force_loaded)
		{
			if (((int16_t(__cdecl*)())0x454DB0)())
				result = ((int(__cdecl*)(bool))0x455260)(false);
			else
				result = ((int(__cdecl*)())0x454B40)();
		}
		return result;
	}
};
static_assert(sizeof(s_game_options) == 0x24B48u, "game_options wrong size");

auto& g_game_options = reference_get<s_game_options>(0x2391800);

// only needs the last part `scenario_path` I.E. s3d_tutorial
// the game must iterate over scenarios until a match is found, if no match is found the game crashes
void LaunchScenario(
	const char* scenario_path = "levels\\solo\\s3d_tutorial\\s3d_tutorial",
	int scenario_type = 1,
	int game_type = 0,
	bool team_game = false,
	uint8_t time_limit = 0,
	uint8_t respawn_time = 0
)
{
	// replace tutorial scenario_type and scenario_path with new ones
	SetMemory<0x7B5E8C>(scenario_path);
	SetMemory<0x7B5E97>(scenario_type);

	// execute ssl_hq_start_tutorial_level
	((void(__cdecl*)())0x7B5E40)();

	// if multiplayer set default gametype to slayer
	if (scenario_type == e_scenario_type::_multiplayer)
	{
		g_game_options.GameVariant_SetGameType(game_type);
		g_game_options.GameVariant_SetTeamGame(team_game);
		g_game_options.GameVariant_SetTimeLimit(time_limit);
		g_game_options.GameVariant_SetRespawnTime(respawn_time);
	}
}

struct s_progression
{
	unsigned char unknown[0x80];

	size_t Size()
	{
		return sizeof(*this);
	}
};

struct game_globals
{
	unsigned char __unknown0;
	unsigned char unknown1;
	unsigned char unknown2;
	unsigned char unknown3;
	unsigned long StructureBspIndex;
	unsigned long __unknown8;
	unsigned long unknownC;

	s_game_options GameOptions;

	unsigned long unknown24B58; // mapname string_id?

	s_progression Progression;
	unsigned char unknown24BDC;
	unsigned char unknown24BDD;
	unsigned char unknown24BDE;
	unsigned char unknown24BDF;
	unsigned char unknown24BE0;
	unsigned char unknown24BE1;
	unsigned char unknown24BE2;
	unsigned char unknown24BE3;
	bool unknown24BE4;
	unsigned char unknown24BD5[3];
	unsigned long EndMatchWaitTime;
	unsigned long PrimarySkullFlags;
	unsigned long SecondarySkullFlags;
	unsigned char unknown24BF4[4];
	struct {
		struct {
			unsigned char unknown[32];
		} unknown[16];
	} unknown24BF8[3];
	bool CinematicIsPlaying;
	unsigned char unknown251F9[15];

	size_t Size()
	{
		return sizeof(*this);
	}

	float GetPhysicsRateFromFrameLimit()
	{
		auto result = (!this ? 0.5f : (30.f / GameOptions.FrameLimit));

		//printf_s("FrameLimitScale: %f\n", result);

		return result;
	}
};
static_assert(sizeof(game_globals) == 0x25208u, "game_globals wrong size");
//static_assert(sizeof(game_globals) == 0x1A908, "game_globals wrong size");

struct s_saved_game_data
{
	struct s_campaign_data
	{
		uint8_t __unknown0;
		uint8_t unknown1;
		uint8_t unknown2;
		uint8_t unknown3;
		uint32_t CampaignId;
		uint32_t map_id;
		uint16_t CampaignInsertionPoint;
		uint16_t unknownE;
		uint32_t CampaignDifficultyLevel;
		uint32_t CampaignMetagameScoringOptions;
		uint32_t CampaignSkullsPrimary;
		uint32_t CampaignSkullsSecondary;
		char PlayersArmaments[0x78];
		s_progression Progression;
		char unknown118[0x80];
	};
	struct s_matchmaking_data
	{
		uint8_t __unknown0;
		uint8_t unknown1;
		uint16_t unknown2;
		uint8_t unknown4;
		uint8_t unknown5;
		uint16_t MatchmakingHopper;
	};
	struct s_multiplayer_data
	{
		uint8_t __unknown0;
		uint8_t unknown1;
		uint8_t unknown2;
		uint8_t unknown3;
		uint8_t GameVariant[0x264];
		uint8_t unknown4[0x210];
		uint8_t MapVariant[0xE090];
		uint8_t unknownE508[0x210];
	};
	struct s_mapeditor_data
	{
		uint8_t __unknown0;
		uint8_t unknown1;
		uint8_t unknown2;
		uint8_t unknown3;
		uint32_t unknown4;
		uint8_t MapVariant[0xE090];
		uint8_t unknownE098[0x210];
	};
	struct s_savedfilm_data
	{
		uint8_t __unknown0;
		uint8_t unknown1;
		uint8_t unknown2;
		uint8_t unknown3;
		uint8_t unknown4[0x10];
		struct s_saved_film_description
		{
			uint32_t CampaignId;
			uint32_t map_id;
			uint8_t __unknown8[8];
			uint32_t __unknown10;
			uint16_t unknown14;
			uint8_t unknown16[0x1FE];
			uint16_t unknown214;
			uint8_t unknown216[0x42];
			uint8_t __unknown258[0xBA];
			uint32_t unknown316;
			uint32_t unknown31A;
		} SavedFilmDescription;
		s_game_options GameOptions;
		uint8_t unknown24E78[8];
	};

	s_campaign_data Campaign;
	s_campaign_data Survival;
	s_matchmaking_data Matchmaking;
	s_multiplayer_data Multiplayer;
	s_mapeditor_data Mapeditor;
	s_savedfilm_data SavedFilm;
} SavedGame;

struct s_save_data_entry
{
	const wchar_t* Path;
	DWORD Size;
	LPVOID Buffer;
};


auto g_saves_path = std::wstring(L"bin\\saves\\");

std::vector<s_save_data_entry> save_data_data_array = {
	{ (g_saves_path + L"campaign_data.dat").c_str(), sizeof(s_saved_game_data::s_campaign_data), &SavedGame.Campaign } ,
	{ (g_saves_path + L"matchmaking_data.dat").c_str(), sizeof(s_saved_game_data::s_matchmaking_data), &SavedGame.Matchmaking } ,
	{ (g_saves_path + L"multiplayer_data.dat").c_str(), sizeof(s_saved_game_data::s_multiplayer_data), &SavedGame.Multiplayer } ,
	{ (g_saves_path + L"mapeditor_data.dat").c_str(), sizeof(s_saved_game_data::s_mapeditor_data), &SavedGame.Mapeditor } ,
	{ (g_saves_path + L"savedfilm_data.dat").c_str(), sizeof(s_saved_game_data::s_savedfilm_data), &SavedGame.SavedFilm } ,
	{ (g_saves_path + L"survival_data.dat").c_str(), sizeof(s_saved_game_data::s_campaign_data), &SavedGame.Survival } ,
	{ (g_saves_path + L"all_data.dat").c_str(), sizeof(s_saved_game_data), &SavedGame }
};

struct s_lobby_data
{
	e_lobby_type LobbyType;
	uint8_t* Data;
};

struct s_save_data
{
	const char* name;
	s_lobby_data* get(s_lobby_data* a1)
	{
		memmove(&a1->Data, save_data_data_array[a1->LobbyType.value].Buffer, save_data_data_array[a1->LobbyType.value].Size);
		return a1;
	}
	void set(s_lobby_data* a1)
	{
		printf_s("Saving %s: %s\n", name, a1->LobbyType.GetName());
		memmove(save_data_data_array[a1->LobbyType.value].Buffer, &a1->Data, save_data_data_array[a1->LobbyType.value].Size);
	}
};

struct s_save_data_all
{
	const char* name;
	s_saved_game_data* get()
	{
		memmove(&SavedGame, save_data_data_array[6].Buffer, save_data_data_array[6].Size);
		return &SavedGame;
	}
	void set(s_saved_game_data* a1)
	{
		printf_s("Saving %s\n", name);
		memmove(save_data_data_array[6].Buffer, &a1, save_data_data_array[6].Size);
	}
};

struct s_screen_resolution
{
	int width;
	int height;

	double GetAspectRation()
	{
		return (double)(width / height);
	}
	int GetPixelCount()
	{
		return width * height;
	}
	bool IsWidescreen()
	{
		return (width / height) / 1.5;
	}
	const char* ToString()
	{
		return (std::to_string(width) + "x" + std::to_string(height)).c_str();
	}
};

struct screen_resolution
{
	int width, height;
	const char* name;
	bool locked;
	void get(int* a1, int* a2)
	{
		*a1 = -1;
		*a2 = -1;
		*a1 = width;
		*a2 = height;
		printf_s("Get %s: %dx%d\n", name, *a1, *a2);
	}
	void set(int a1, int a2)
	{
		if (a1 == width && a2 == height)
			return;
		if (locked)
		{
			printf_s("Unable to set %s: locked\n", name);
			return;
		}
		s_screen_resolution value = { width, height };
		auto prev = value;
		value.width = a1;
		value.height = a2;
		printf_s("Set %s: %s->%s\n", name, prev.ToString(), value.ToString());
		PreferenceManager.SetString(PreferenceManagerAppname, name, value.ToString());
	}
	void set(s_screen_resolution* a1)
	{
		set(a1->width, a1->height);
	}
	void toggle_lock()
	{
		locked = !locked;
	}
};

struct game_language
{
	e_game_language value;
	const char* name;
	bool locked;

	e_game_language get()
	{
		return value;
	}
	void set(e_game_language a1)
	{
		if (a1.value == value.value)
			return;
		if (locked)
		{
			printf_s("Unable to set %s: locked\n", name);
			return;
		}

		auto prev = value;
		value = a1;
		printf_s("Set %s: %s->%s\n", name, prev.GetName(), value.GetName());
		PreferenceManager.SetString(PreferenceManagerAppname, name, value.GetName());
	}
	void toggle_lock()
	{
		locked = !locked;
	}
};

struct player_marker
{
	e_player_marker_option value;
	const char* name;
	bool locked;

	e_player_marker_option get()
	{
		return value;
	}
	void set(e_player_marker_option a1)
	{
		if (a1.value == value.value)
			return;
		if (locked)
		{
			printf_s("Unable to set %s: locked\n", name);
			return;
		}

		auto prev = value;
		value = a1;
		printf_s("Set %s: %s->%s\n", name, prev.GetName(), value.GetName());
		PreferenceManager.SetString(PreferenceManagerAppname, name, value.GetName());
	}
	void toggle_lock()
	{
		locked = !locked;
	}
};

struct control_method
{
	e_control_method_option value;
	const char* name;
	bool locked;

	e_control_method_option get()
	{
		return value;
	}
	void set(e_control_method_option a1)
	{
		if (a1.value == value.value)
			return;
		if (locked)
		{
			printf_s("Unable to set %s: locked\n", name);
			return;
		}

		auto prev = value;
		value = a1;
		printf_s("Set %s: %s->%s\n", name, prev.GetName(), value.GetName());
		PreferenceManager.SetString(PreferenceManagerAppname, name, value.GetName());
	}
	void toggle_lock()
	{
		locked = !locked;
	}
};

struct toggle
{
	e_toggle_option value;
	const char* name;
	bool locked;

	e_toggle_option get()
	{
		return value;
	}
	void set(e_toggle_option a1)
	{
		if (a1.value == value.value)
			return;
		if (locked)
		{
			printf_s("Unable to set %s: locked\n", name);
			return;
		}

		auto prev = value;
		value = a1;
		printf_s("Set %s: %s->%s\n", name, prev.GetName(), value.GetName());
		PreferenceManager.SetString(PreferenceManagerAppname, name, value.GetName());
	}
	void toggle_lock()
	{
		locked = !locked;
	}
};

struct quality
{
	e_quality_option quality;
	const char* name;
	bool locked;

	e_quality_option get()
	{
		return quality;
	}
	void set(e_quality_option a1)
	{
		if (a1.value == quality.value)
			return;
		if (locked)
		{
			printf_s("Unable to set %s: locked\n", name);
			return;
		}

		auto prev = quality;
		quality.value = a1.value;
		printf_s("Set %s: %s->%s\n", name, prev.GetName(), quality.GetName());
		PreferenceManager.SetString(PreferenceManagerAppname, name, quality.GetName());
	}
	void toggle_lock()
	{
		locked = !locked;
	}
};

struct stringid
{
	uint32_t value;
	const char* name;
	bool locked;

	uint32_t get()
	{
		return value;
	}
	void set(uint32_t a1)
	{
		if (a1 == value)
			return;
		if (locked)
		{
			printf_s("Unable to set %s: locked\n", name);
			return;
		}

		auto prev = value;
		value = a1;
		printf_s("Set %s: %s->%s\n", name, Blam::StringIDCache::Instance.GetString(prev), Blam::StringIDCache::Instance.GetString(a1));
		PreferenceManager.SetString(PreferenceManagerAppname, name, Blam::StringIDCache::Instance.GetString(a1));
	}
	void toggle_lock()
	{
		locked = !locked;
	}
};

struct uint32
{
	uint32_t value;
	const char* name;
	bool locked;

	uint32_t get()
	{
		return value;
	}
	void set(uint32_t a1)
	{
		if (a1 == value)
			return;
		if (locked)
		{
			printf_s("Unable to set %s: locked\n", name);
			return;
		}

		auto prev = value;
		value = a1;
		printf_s("Set %s: %d->%d\n", name, prev, value);
		PreferenceManager.SetInt(PreferenceManagerAppname, name, value);
	}
	void toggle_lock()
	{
		locked = !locked;
	}
};

struct uint16
{
	uint16_t value;
	const char* name;
	bool locked;

	uint16_t get()
	{
		return value;
	}
	void set(uint16_t a1)
	{
		if (a1 == value)
			return;
		if (locked)
		{
			printf_s("Unable to set %s: locked\n", name);
			return;
		}

		auto prev = value;
		value = a1;
		printf_s("Set %s: %d->%d\n", name, prev, value);
		PreferenceManager.SetInt(PreferenceManagerAppname, name, value);
	}
	void toggle_lock()
	{
		locked = !locked;
	}
};

struct uint8
{
	uint8_t value;
	const char* name;
	bool locked;

	uint8_t get()
	{
		return value;
	}
	void set(uint8_t a1)
	{
		if (a1 == value)
			return;
		if (locked)
		{
			printf_s("Unable to set %s: locked\n", name);
			return;
		}

		auto prev = value;
		value = a1;
		printf_s("Set %s: %d->%d\n", name, prev, value);
		PreferenceManager.SetInt(PreferenceManagerAppname, name, value);
	}
	void toggle_lock()
	{
		locked = !locked;
	}
};

bool IsConnectedToLive()
{
	return reinterpret_cast<uint8_t*>(0x2179468)[0] == 0;
}

bool IsMapLoaded()
{
	return reinterpret_cast<uint8_t*>(0x23917F0)[0] == 0;
}

uint8_t* Transport()
{
	return reinterpret_cast<uint8_t*>(0x199FA28);
}

auto game_globals_get = []() { return (game_globals*)GetMainTls(0x3C)[0]; };
auto game_options_get = []() { return &game_globals_get()->GameOptions; };
auto scenario_type_get = []() { return game_options_get()->ScenarioType.value; };
auto game_progression_get = []() { return game_globals_get()->Progression; };

struct s_levels
{
	uint8_t __unknown0[2];
	uint16_t CampaignId;
	uint32_t map_id;
	wchar_t MapName[32];
	wchar_t MapSescription[128];
	char scenario_path[256];
	char ScenarioImagePath[256];
	uint32_t unknown348;
	uint32_t unknown34C;
	uint16_t unknown34E;
	uint8_t GameType[14];

	size_t Size()
	{
		return sizeof(*this);
	}
};
static_assert(sizeof(s_levels) == 0x360, "s_levels wrong size");

struct s_campaigns_data
{
	uint8_t __unknown0[2];
	uint16_t Flags;
	uint32_t CampaignId;
	wchar_t __unknown8[64];
	wchar_t unknown88[128];
	uint32_t unknown188[64];

	size_t Size()
	{
		return sizeof(*this);
	}
};

struct s_levels_unknown
{
	int* campaigns_data;
	int* campaign_levels_data; // s_levels
	int* campaign_insertions_data;
	int* multiplayer_levels_data; // s_levels

	struct s_levels_unknown_offset_10_of_size_360
	{
		uint8_t __unknown0[2];
		uint16_t campaign_id;
		uint32_t map_id;
		uint8_t __unknown8[320];
		char scenario_path[256];
		uint8_t __unknown258[280];

		size_t Size()
		{
			return sizeof(*this);
		}
	} __unknown10;
	static_assert(sizeof(s_levels_unknown_offset_10_of_size_360) == 0x360, "s_levels_unknown_offset_10 wrong size");

	uint32_t __unknown370;
	uint8_t __unknown374[1698];
	uint8_t __unknownA16;
	uint8_t __unknownA17;
	uint8_t __unknownA18[4];

	size_t Size()
	{
		return sizeof(*this);
	}
};
static_assert(sizeof(s_levels_unknown) == 0xA1C, "s_levels_unknown wrong size");

struct s_game_state_header
{
	uint32_t* Sessions[3];
	uint8_t unknownC[252];
	char BuildVersion[32];
	uint32_t unknown108;
	uint8_t unknown10C[4];
	s_game_options GameOptions;
	uint8_t ScenarioGameState[24];
	uint8_t unknown24C90[64];

	size_t Size()
	{
		return sizeof(*this);
	}
};

struct s_runtime_state_allocation
{
	bool* IsInitialized;
	bool* ShouldReleaseMemory;
	void** Data;
	uint32_t* DatumSize;
	uint32_t* Size;
	bool* IsValid;

	size_t GetSize()
	{
		return sizeof(*this);
	}
};
auto& g_runtime_state_allocation = reference_get<s_runtime_state_allocation>(0x2497CD0);

struct s_file_reference
{
	uint32_t HeaderType;
	uint16_t Flags;
	int16_t unknown6;
	char Path[256];
	HANDLE FileHandle;
	uint32_t FilePointer;

	size_t Size()
	{
		return sizeof(*this);
	}

	s_file_reference* __cdecl initialize_header(uint16_t a2)
	{
		memset(this, 0, 0x110u);
		HeaderType = 'filo';
		unknown6 = a2;

		return this;
	}
	s_file_reference* __cdecl initialize(uint16_t a2)
	{
		initialize_header(a2);
		FileHandle = (HANDLE)-1;

		return this;
	}
	bool close()
	{
		bool result;
		if (CloseHandle(FileHandle))
		{
			FileHandle = (HANDLE)-1;
			FilePointer = 0;
			result = true;
		}
		else
		{
			SetLastError(0);
			result = false;
		}
		return result;
	}
	bool read(DWORD nNumberOfBytesToRead, char a3, LPVOID lpBuffer, void(__cdecl* sub_5294F0)(const char*, s_file_reference*, s_file_reference*, char))
	{
		DWORD v4 = nNumberOfBytesToRead;
		if (!nNumberOfBytesToRead)
			return true;
		DWORD v6 = nNumberOfBytesToRead;
		nNumberOfBytesToRead = 0;
		char result = false;
		if (ReadFile(FileHandle, lpBuffer, v6, &nNumberOfBytesToRead, 0))
		{
			if (nNumberOfBytesToRead == v4)
				result = true;
			else
				SetLastError(0x26u);
		}
		FilePointer += nNumberOfBytesToRead;
		if (!result)
			sub_5294F0("file_read", this, 0, a3);

		return result;
	}
	bool set_position(LONG lDistanceToMove, char a3, void(__cdecl* sub_5294F0)(const char*, s_file_reference*, s_file_reference*, char))
	{
		if (FilePointer == lDistanceToMove)
			return true;
		void* v4 = FileHandle;
		LONG DistanceToMoveHigh = 0;
		auto v5 = SetFilePointer(v4, lDistanceToMove, &DistanceToMoveHigh, 0);
		bool file_pointer_is_valid = v5 != -1;
		FilePointer = v5;
		if (v5 == -1)
			sub_5294F0("file_set_position", this, 0, a3);

		return file_pointer_is_valid;
	}
	bool write(DWORD nNumberOfBytesToWrite, LPCVOID lpBuffer, void(__cdecl* sub_5294F0)(const char*, s_file_reference*, s_file_reference*, char))
	{
		DWORD v3 = nNumberOfBytesToWrite;
		if (!nNumberOfBytesToWrite)
			return true;
		DWORD v5 = nNumberOfBytesToWrite;
		nNumberOfBytesToWrite = 0;
		char result = false;
		if (WriteFile(FileHandle, lpBuffer, v5, &nNumberOfBytesToWrite, 0))
		{
			result = 0;
			if (nNumberOfBytesToWrite == v3)
				result = true;
		}
		FilePointer += nNumberOfBytesToWrite;
		if (!result)
			sub_5294F0("file_write", this, 0, 0);
		return result;
	}
	int __cdecl get_eof(void(__cdecl* sub_5294F0)(const char*, s_file_reference*, s_file_reference*, char))
	{
		DWORD result = GetFileSize(FileHandle, 0);
		if (!result)
			sub_5294F0("file_get_eof", this, 0, 0);
		return result;
	}

	s_file_reference* Print(const char* calling_function)
	{
		return this;
		printf_s("type: %s, flags: %d, unk6: %d, handle: 0x%p, pointer: 0x%08X, path: %s, %s\n", (HeaderType == 'filo' ? "'filo'" : "'????'"), Flags, unknown6, FileHandle, FilePointer, Path, calling_function);
	}
};
auto& global_tag_cache_filo = reference_get<s_file_reference>(0x22AE3A8);

struct s_unit_action
{
	e_unit_action Index;
	unsigned char unknown4[0x44];

	size_t Size()
	{
		return sizeof(*this);
	}
};

struct s_content_catalogue
{
	uint32_t StorageDeviceId;
	int* Data;
	uint8_t __unknown8[8];
	struct s_size_240
	{
		uint8_t __unknown0[576];
	} __unknown10;
	uint8_t unknown250[6];
	uint16_t unknown256;
	uint8_t __unknown258[12];
	uint32_t unknown264;
	uint8_t unknown268[14];
	uint16_t unknown276;
	uint8_t unknown278[40];
	uint32_t unknown2A0;
	volatile LONG* unknown2A4;
	uint32_t Flags2A8;
	uint8_t unknown2AC[4];

	size_t Size()
	{
		return sizeof(*this);
	}
};

struct s_storage_device
{
	s_content_catalogue* ContentCataloguePtr;
	uint8_t unknown4[44];

	size_t Size()
	{
		return sizeof(*this);
	}
};

#pragma pack(push, 1)
struct s_player_profile_offset0_offset8
{
	uint8_t __unknown0[12];
	uint32_t UserIndex;
	uint8_t unknownC[492];
	uint32_t CameraInversion;
	uint32_t CameraPanning;
	uint32_t CameraLookSensitivity;
	uint32_t CameraSpeed;
	uint32_t CameraThrust;
	uint32_t CampaignDifficultyLevel;
	uint8_t unknown214[4];
	uint8_t unknown218[2][32];
	uint8_t __unknown258[16];
	uint32_t UserAquiredPrimarySkullsFlags;
	uint32_t UserAquiredSecondarySkullsFlags;
	uint8_t unknown270[560];
	uint8_t unknown4A0[1616];
	uint8_t unknownAF0[20];
	uint32_t unknownB04;
	uint32_t unknownB08;
	uint16_t unknownB0A;
	uint16_t unknownB0C;

	size_t Size()
	{
		return sizeof(*this);
	}
};

struct s_player_profile
{
	uint8_t Flags;
	uint8_t unknown1;
	uint16_t LocalPlayerIndex;
	uint8_t unknown4[4];
	s_player_profile_offset0_offset8* __unknown8;
	uint8_t unknownC[1286];

	size_t Size()
	{
		return sizeof(*this);
	}
};

struct c_controller_interface
{
	s_player_profile unkown0;
	uint8_t unkown512[3822];
	wchar_t Name[16];
	uint8_t unkown544[16];
	uint32_t Achievements[2];
	uint8_t unkown55C[16];

	size_t Size()
	{
		return sizeof(*this);
	}
};
#pragma pack(pop)

#pragma pack(push, 1)
struct s_overlapped_task_vftable
{
	int(__cdecl* vftable0)(void*, char);
	e_session_overlapped_task_type(__cdecl* type)(uint32_t*, char);
	void(__cdecl* vftable2)(uint32_t);
	void(__cdecl* vftable3)(uint32_t);
	void(__cdecl* vftable4)(uint32_t*, uint32_t);
	void(__cdecl* vftable5)(uint32_t*, uint32_t, uint32_t, uint32_t);
	void(__cdecl* vftable6)(uint32_t*);
	void(__cdecl* vftable7)(uint16_t*);
	void(__cdecl* vftable8)(uint32_t, uint32_t, uint32_t);

	size_t Size()
	{
		return sizeof(*this);
	}
};
struct XSession
{
	uint32_t Controller;
	uint16_t SlotsFlags;
	uint8_t Unknown8[2];
	uint32_t SlotsPublic;
	uint32_t SlotsPrivate;
	XnkAddr XnkAddr[3];
	uint8_t Unknown40[8];
	uint32_t* Handle;
	uint32_t Unknown4C;
	uint64_t XUid[32];

	size_t Size()
	{
		return sizeof(*this);
	}
};
class c_managed_session
{
public:
	uint32_t SignInState;
	uint32_t Unknown4;
	uint32_t LongFlags8;
	uint16_t ShortFlagsC;
	uint16_t ShortFlagsE;
	s_overlapped_task_vftable OverlappedTask;
	uint8_t Unknown32[220];
	uint32_t UnknownTimeValue;
	uint8_t CheckLive;
	uint8_t CheckIP;
	uint8_t CheckConflickingSession;
	uint8_t Unknown117;
	XSession OfflineSession;
	XSession LocalSession;
	XSession LiveSession;
	uint32_t XUid[16][2];
	uint8_t Unknown588[32];
	uint32_t XUids;
	uint8_t IsHost;
	uint8_t Unknown5AD;
	XnkAddr XnkAddr[3];
	uint8_t Unknown5D8[2];
	uint32_t Unknown5E0[8];
	uint32_t Unknown600;
	uint8_t Unknown604[4];

	size_t Size()
	{
		return sizeof(*this);
	}
};
#pragma pack(pop)

struct s_network_configuration
{
	int __unknown0;
	int unknown4;
	int __unknown8;
	float unknownC;
	int __unknown10;
	int unknown14;
	int unknown18;
	int unknown1C;
	float unknown20;
	int unknown24;
	int unknown28;
	int unknown2C;
	int unknown30;
	int unknown34;
	int unknown38;
	int unknown3C;
	int unknown40;
	int unknown44;
	int unknown48;
	int unknown4C;
	int unknown50;
	int unknown54;
	int unknown58;
	int unknown5C;
	int unknown60;
	int unknown64;
	int unknown68;
	int unknown6C;
	int unknown70;
	int unknown74;
	int unknown78;
	int unknown7C;
	int unknown80;
	int unknown84;
	int unknown88;
	int unknown8C;
	int unknown90;
	int unknown94;
	int unknown98;
	int unknown9C;
	int unknownA0;
	int unknownA4;
	int unknownA8;
	int unknownAC;
	int unknownB0;
	int unknownB4;
	int unknownB8;
	int unknownBC;
	int unknownC0;
	int unknownC4;
	int unknownC8;
	int unknownCC;
	int unknownD0;
	int unknownD4;
	int unknownD8;
	int unknownDC;
	int unknownE0;
	int unknownE4;
	int unknownE8;
	int unknownEC;
	int unknownF0;
	int unknownF4;
	int unknownF8;
	int unknownFC;
	int unknown100;
	int unknown104;
	int unknown108;
	int unknown10C;
	int unknown110;
	int unknown114;
	int unknown118;
	int unknown11C;
	int unknown120;
	int unknown124;
	int unknown128;
	int unknown12C;
	int unknown130;
	int unknown134;
	int unknown138;
	int unknown13C;
	int unknown140;
	int unknown144;
	int unknown148;
	int unknown14C;
	int unknown150;
	int unknown154;
	int unknown158;
	int unknown15C;
	int unknown160;
	int unknown164;
	int unknown168;
	int unknown16C;
	int unknown170;
	int unknown174;
	int unknown178;
	int unknown17C;
	int unknown180;
	int unknown184;
	int unknown188;
	int unknown18C;
	int unknown190;
	int unknown194;
	int unknown198;
	int unknown19C;
	int unknown1A0;
	int unknown1A4;
	int unknown1A8;
	int unknown1AC;
	int unknown1B0;
	int unknown1B4;
	int unknown1B8;
	int unknown1BC;
	int unknown1C0;
	int unknown1C4;
	int unknown1C8;
	int unknown1CC;
	int unknown1D0;
	int unknown1D4;
	int unknown1D8;
	int unknown1DC;
	int unknown1E0;
	int unknown1E4;
	int unknown1E8;
	int unknown1EC;
	int unknown1F0;
	int unknown1F4;
	int unknown1F8;
	int unknown1FC;
	int unknown200;
	int unknown204;
	int unknown208;
	int unknown20C;
	int unknown210;
	int unknown214;
	int unknown218;
	int unknown21C;
	int unknown220;
	int unknown224;
	int unknown228;
	int unknown22C;
	int unknown230;
	int unknown234;
	int unknown238;
	int unknown23C;
	int unknown240;
	int unknown244;
	int DisbandTimeout;
	int unknown24C;
	int unknown250;
	int unknown254;
	int __unknown258;
	int unknown25C;
	int unknown260;
	__int8 unknown264;
	float unknown268;
	int unknown26C;
	int unknown270;
	int unknown274;
	int unknown278;
	int unknown27C;
	int unknown280;
	int unknown284;
	__int8 unknown288;
	int unknown28C;
	int unknown290;
	int unknown294;
	int unknown298;
	int unknown29C;
	int GriefTimerTimeout;
	int unknown2A4;
	int unknown2A8;
	__int8 unknown2AC;
	int unknown2B0;
	int unknown2B4;
	int SimulationAbortAsHostTimeout;
	int SimulationAbortAsPeerTimeout;
	int unknown2C0;
	int unknown2C4;
	int unknown2C8;
	int unknown2CC;
	int unknown2D0;
	int unknown2D4;
	int unknown2D8;
	int unknown2DC;
	int unknown2E0;
	int unknown2E4;
	int unknown2E8;
	int unknown2EC;
	int unknown2F0;
	int unknown2F4;
	int unknown2F8;
	int unknown2FC;
	float unknown300;
	int unknown304;
	int unknown308;
	int unknown30C;
	int unknown310;
	int unknown314;
	int unknown318;
	int unknown31C;
	int unknown320;
	int unknown324;
	int unknown328;
	int unknown32C;
	int unknown330;
	int unknown334;
	int unknown338;
	int unknown33C;
	int unknown340;
	float unknown344;
	float unknown348;
	int unknown34C;
	int unknown350;
	int unknown354;
	int unknown358;
	int unknown35C;
	int unknown360;
	int unknown364;
	int unknown368;
	int unknown36C;
	int __unknown370;
	float __unknown374;
	int unknown378;
	int unknown37C;
	int unknown380;
	int unknown384;
	int unknown388;
	int unknown38C;
	int unknown390;
	int unknown394;
	int unknown398;
	int unknown39C;
	int unknown3A0;
	int unknown3A4;
	int unknown3A8;
	int unknown3AC;
	int unknown3B0;
	int unknown3B4;
	int unknown3B8;
	int unknown3BC;
	int unknown3C0;
	int LobbyCoopMaxPlayerCount;
	int LobbyMapeditorMaxPlayerCount;
	int unknown3CC;
	int MachineFileRefreshTimeout;
	int unknown3D4;
	int unknown3D8;
	int unknown3DC;
	int unknown3E0;
	float unknown3E4;
	float unknown3E8;
	float unknown3EC;
	float unknown3F0;
	float unknown3F4;
	float unknown3F8;
	float unknown3FC;
	int unknown400;
	int unknown404;
	float unknown408;
	float unknown40C;
	float unknown410;
	float unknown414;
	int unknown418;
	int unknown41C;
	int unknown420;
	int unknown424;
	int unknown428;
	int unknown42C;
	int unknown430;
	int unknown434;
	int unknown438;
	int unknown43C;
	int unknown440;
	float unknown444;
	float unknown448;
	float unknown44C;
	int unknown450;
	int unknown454;
	int unknown458;
	int unknown45C;
	int unknown460;
	float unknown464;
	float unknown468;
	int unknown46C;
	int unknown470;
	int unknown474;
	int unknown478;
	float unknown47C;
	float unknown480;
	int unknown484;
	int unknown488;
	float unknown48C;
	float unknown490;
	float unknown494;
	int unknown498;
	int unknown49C;
	float unknown4A0;
	float unknown4A4;
	float unknown4A8;
	int unknown4AC;
	int unknown4B0;
	float unknown4B4;
	float unknown4B8;
	float unknown4BC;
	int unknown4C0;
	int unknown4C4;
	float unknown4C8;
	float unknown4CC;
	float unknown4D0;
	int unknown4D4;
	int unknown4D8;
	float unknown4DC;
	float unknown4E0;
	float unknown4E4;
	int unknown4E8;
	int unknown4EC;
	float unknown4F0;
	float unknown4F4;
	float unknown4F8;
	int unknown4FC;
	int unknown500;
	float unknown504;
	float unknown508;
	float unknown50C;
	float unknown510;
	int unknown514;
	int unknown518;
	int unknown51C;
	int unknown520;
	int unknown524;
	int unknown528;
	float unknown52C;
	float unknown530;
	float unknown534;
	int unknown538;
	int unknown53C;
	float unknown540;
	float unknown544;
	float unknown548;
	int unknown54C;
	int unknown550;
	float unknown554;
	float unknown558;
	float unknown55C;
	int unknown560;
	int unknown564;
	float unknown568;
	float unknown56C;
	float unknown570;
	int unknown574;
	int unknown578;
	float unknown57C;
	float unknown580;
	float unknown584;
	int unknown588;
	int unknown58C;
	float unknown590;
	float unknown594;
	float unknown598;
	int unknown59C;
	int unknown5A0;
	float unknown5A4;
	float unknown5A8;
	float unknown5AC;
	int unknown5B0;
	int unknown5B4;
	float unknown5B8;
	float unknown5BC;
	float unknown5C0;
	float unknown5C4;
	int unknown5C8;
	int unknown5CC;
	int unknown5D0;
	int unknown5D4;
	int unknown5D8;
	int unknown5DC;
	float unknown5E0;
	float unknown5E4;
	float unknown5E8;
	float unknown5EC;
	int unknown5F0;
	int unknown5F4;
	int unknown5F8;
	int unknown5FC;
	int unknown600;
	int unknown604;
	float unknown608;
	float unknown60C;
	float unknown610;
	int unknown614;
	int unknown618;
	float unknown61C;
	float unknown620;
	float unknown624;
	int unknown628;
	int unknown62C;
	float unknown630;
	float unknown634;
	float unknown638;
	float unknown63C;
	int unknown640;
	int unknown644;
	int unknown648;
	int unknown64C;
	float unknown650;
	int unknown654;
	int unknown658;
	int unknown65C;
	int unknown660;
	float unknown664;
	int unknown668;
	int unknown66C;
	int unknown670;
	int unknown674;
	float unknown678;
	int unknown67C;
	int unknown680;
	int unknown684;
	int unknown688;
	float unknown68C;
	int unknown690;
	int unknown694;
	int unknown698;
	int unknown69C;
	float unknown6A0;
	int unknown6A4;
	int unknown6A8;
	int unknown6AC;
	int unknown6B0;
	float unknown6B4;
	int unknown6B8;
	int unknown6BC;
	int unknown6C0;
	int unknown6C4;
	float unknown6C8;
	int unknown6CC;
	int unknown6D0;
	int unknown6D4;
	int unknown6D8;
	float unknown6DC;
	int unknown6E0;
	int unknown6E4;
	int unknown6E8;
	int unknown6EC;
	float unknown6F0;
	int unknown6F4;
	int unknown6F8;
	int unknown6FC;
	int unknown700;
	float unknown704;
	int unknown708;
	int unknown70C;
	int unknown710;
	int unknown714;
	float unknown718;
	int unknown71C;
	int unknown720;
	int unknown724;
	int unknown728;
	float unknown72C;
	int unknown730;
	int unknown734;
	int unknown738;
	int unknown73C;
	float unknown740;
	int unknown744;
	int unknown748;
	int unknown74C;
	int unknown750;
	float unknown754;
	int unknown758;
	int unknown75C;
	int unknown760;
	int unknown764;
	float unknown768;
	int unknown76C;
	int unknown770;
	int unknown774;
	int unknown778;
	float unknown77C;
	int unknown780;
	int unknown784;
	int unknown788;
	int unknown78C;
	float unknown790;
	int unknown794;
	int unknown798;
	int unknown79C;
	int unknown7A0;
	float unknown7A4;
	float unknown7A8;
	float unknown7AC;
	int unknown7B0;
	int unknown7B4;
	float unknown7B8;
	float unknown7BC;
	int unknown7C0;
	float unknown7C4;
	float unknown7C8;
	float unknown7CC;
	int unknown7D0;
	int unknown7D4;
	int unknown7D8;
	float unknown7DC;
	int unknown7E0;
	int unknown7E4;
	int unknown7E8;
	int unknown7EC;
	float unknown7F0;
	float unknown7F4;
	float unknown7F8;
	int unknown7FC;
	int unknown800;
	float unknown804;
	float unknown808;
	int unknown80C;
	float unknown810;
	float unknown814;
	float unknown818;
	int unknown81C;
	int unknown820;
	int unknown824;
	float unknown828;
	int unknown82C;
	int unknown830;
	int unknown834;
	int unknown838;
	float unknown83C;
	float unknown840;
	float unknown844;
	int unknown848;
	int unknown84C;
	float unknown850;
	float unknown854;
	int unknown858;
	float unknown85C;
	float unknown860;
	float unknown864;
	int unknown868;
	int unknown86C;
	int unknown870;
	float unknown874;
	int unknown878;
	int unknown87C;
	int unknown880;
	int unknown884;
	float unknown888;
	float unknown88C;
	float unknown890;
	int unknown894;
	int unknown898;
	float unknown89C;
	float unknown8A0;
	int unknown8A4;
	float unknown8A8;
	float unknown8AC;
	float unknown8B0;
	int unknown8B4;
	int unknown8B8;
	int unknown8BC;
	float unknown8C0;
	int unknown8C4;
	int unknown8C8;
	int unknown8CC;
	int unknown8D0;
	float unknown8D4;
	float unknown8D8;
	float unknown8DC;
	int unknown8E0;
	int unknown8E4;
	float unknown8E8;
	float unknown8EC;
	int unknown8F0;
	float unknown8F4;
	float unknown8F8;
	float unknown8FC;
	int unknown900;
	int unknown904;
	int unknown908;
	float unknown90C;
	int unknown910;
	int unknown914;
	int unknown918;
	int unknown91C;
	float unknown920;
	float unknown924;
	float unknown928;
	int unknown92C;
	int unknown930;
	float unknown934;
	float unknown938;
	int unknown93C;
	float unknown940;
	float unknown944;
	float unknown948;
	int unknown94C;
	int unknown950;
	int unknown954;
	float unknown958;
	int unknown95C;
	int unknown960;
	int unknown964;
	int unknown968;
	float unknown96C;
	float unknown970;
	float unknown974;
	int unknown978;
	int unknown97C;
	float unknown980;
	float unknown984;
	int unknown988;
	float unknown98C;
	float unknown990;
	float unknown994;
	int unknown998;
	int unknown99C;
	int unknown9A0;
	float unknown9A4;
	int unknown9A8;
	int unknown9AC;
	int unknown9B0;
	int unknown9B4;
	float unknown9B8;
	float unknown9BC;
	float unknown9C0;
	int unknown9C4;
	int unknown9C8;
	float unknown9CC;
	float unknown9D0;
	int unknown9D4;
	float unknown9D8;
	float unknown9DC;
	float unknown9E0;
	int unknown9E4;
	int unknown9E8;
	int unknown9EC;
	float unknown9F0;
	int unknown9F4;
	int unknown9F8;
	int unknown9FC;
	int unknownA00;
	float unknownA04;
	float unknownA08;
	float unknownA0C;
	int unknownA10;
	int unknownA14;
	float __unknownA18;
	float unknownA1C;
	int unknownA20;
	float unknownA24;
	float unknownA28;
	float unknownA2C;
	int unknownA30;
	int unknownA34;
	int unknownA38;
	float unknownA3C;
	int unknownA40;
	int unknownA44;
	int unknownA48;
	int unknownA4C;
	float unknownA50;
	float unknownA54;
	float unknownA58;
	int unknownA5C;
	int unknownA60;
	float unknownA64;
	float unknownA68;
	int unknownA6C;
	float unknownA70;
	float unknownA74;
	float unknownA78;
	int unknownA7C;
	int unknownA80;
	int unknownA84;
	int unknownA88;
	float unknownA8C;
	float unknownA90;
	float unknownA94;
	int unknownA98;
	float unknownA9C;
	float unknownAA0;
	float unknownAA4;
	int unknownAA8;
	int unknownAAC;
	float unknownAB0;
	float unknownAB4;
	int unknownAB8;
	float unknownABC;
	float unknownAC0;
	float unknownAC4;
	int unknownAC8;
	int unknownACC;
	int unknownAD0;
	float unknownAD4;
	int unknownAD8;
	int unknownADC;
	int unknownAE0;
	int unknownAE4;
	float unknownAE8;
	float unknownAEC;
	float unknownAF0;
	int unknownAF4;
	int unknownAF8;
	float unknownAFC;
	float unknownB00;
	int unknownB04;
	float unknownB08;
	float unknownB0C;
	float unknownB10;
	int unknownB14;
	int unknownB18;
	int unknownB1C;
	int unknownB20;
	float unknownB24;
	float unknownB28;
	float unknownB2C;
	int unknownB30;
	float unknownB34;
	float unknownB38;
	float unknownB3C;
	int unknownB40;
	int unknownB44;
	float unknownB48;
	float unknownB4C;
	int unknownB50;
	float unknownB54;
	float unknownB58;
	float unknownB5C;
	int unknownB60;
	int unknownB64;
	int unknownB68;
	int unknownB6C;
	float unknownB70;
	float unknownB74;
	float unknownB78;
	int unknownB7C;
	float unknownB80;
	float unknownB84;
	float unknownB88;
	int unknownB8C;
	int unknownB90;
	float unknownB94;
	float unknownB98;
	int unknownB9C;
	float unknownBA0;
	float unknownBA4;
	float unknownBA8;
	int unknownBAC;
	int unknownBB0;
	int unknownBB4;
	int unknownBB8;
	float unknownBBC;
	float unknownBC0;
	float unknownBC4;
	int unknownBC8;
	float unknownBCC;
	float unknownBD0;
	float unknownBD4;
	int unknownBD8;
	int unknownBDC;
	float unknownBE0;
	float unknownBE4;
	int unknownBE8;
	float unknownBEC;
	float unknownBF0;
	float unknownBF4;
	float unknownBF8;
	float unknownBFC;
	int unknownC00;
	int unknownC04;
	float unknownC08;
	float unknownC0C;
	float unknownC10;
	int unknownC14;
	float unknownC18;
	float unknownC1C;
	float unknownC20;
	int unknownC24;
	int unknownC28;
	float unknownC2C;
	float unknownC30;
	int unknownC34;
	float unknownC38;
	float unknownC3C;
	float unknownC40;
	int unknownC44;
	int unknownC48;
	int unknownC4C;
	int unknownC50;
	float unknownC54;
	float unknownC58;
	float unknownC5C;
	int unknownC60;
	float unknownC64;
	float unknownC68;
	float unknownC6C;
	int unknownC70;
	int unknownC74;
	float unknownC78;
	float unknownC7C;
	int unknownC80;
	float unknownC84;
	float unknownC88;
	float unknownC8C;
	int unknownC90;
	int unknownC94;
	int unknownC98;
	int unknownC9C;
	float unknownCA0;
	float unknownCA4;
	float unknownCA8;
	int unknownCAC;
	float unknownCB0;
	float unknownCB4;
	float unknownCB8;
	int unknownCBC;
	int unknownCC0;
	float unknownCC4;
	float unknownCC8;
	int unknownCCC;
	float unknownCD0;
	float unknownCD4;
	float unknownCD8;
	int unknownCDC;
	int unknownCE0;
	int unknownCE4;
	int unknownCE8;
	float unknownCEC;
	float unknownCF0;
	float unknownCF4;
	int unknownCF8;
	float unknownCFC;
	float unknownD00;
	float unknownD04;
	int unknownD08;
	int unknownD0C;
	float unknownD10;
	float unknownD14;
	int unknownD18;
	float unknownD1C;
	float unknownD20;
	float unknownD24;
	int unknownD28;
	int unknownD2C;
	float unknownD30;
	int unknownD34;
	float unknownD38;
	float unknownD3C;
	float unknownD40;
	int unknownD44;
	float unknownD48;
	float unknownD4C;
	float unknownD50;
	int unknownD54;
	int unknownD58;
	float unknownD5C;
	float unknownD60;
	int unknownD64;
	float unknownD68;
	float unknownD6C;
	float unknownD70;
	int unknownD74;
	int unknownD78;
	int unknownD7C;
	int unknownD80;
	float unknownD84;
	float unknownD88;
	float unknownD8C;
	int unknownD90;
	float unknownD94;
	float unknownD98;
	float unknownD9C;
	int unknownDA0;
	int unknownDA4;
	float unknownDA8;
	float unknownDAC;
	int unknownDB0;
	float unknownDB4;
	float unknownDB8;
	float unknownDBC;
	int unknownDC0;
	int unknownDC4;
	int unknownDC8;
	int unknownDCC;
	float unknownDD0;
	float unknownDD4;
	float unknownDD8;
	int unknownDDC;
	float unknownDE0;
	float unknownDE4;
	float unknownDE8;
	int unknownDEC;
	int unknownDF0;
	float unknownDF4;
	float unknownDF8;
	int unknownDFC;
	float unknownE00;
	float unknownE04;
	float unknownE08;
	int unknownE0C;
	int unknownE10;
	int unknownE14;
	float unknownE18;
	float unknownE1C;
	float unknownE20;
	float unknownE24;
	float unknownE28;
	float unknownE2C;
	float unknownE30;
	float unknownE34;
	float unknownE38;
	float unknownE3C;
	int unknownE40;
	float unknownE44;
	int unknownE48;
	float unknownE4C;
	float unknownE50;
	float unknownE54;
	float unknownE58;
	float unknownE5C;
	int unknownE60;
	int ManagedSessionProcessPendingTimeout;
	int unknownE68;
	int IdlePeerJoiningTimeout;
	int PeerJoinTimedOut;
	int JoinQueueMaxWaitTime;
	int unknownE78;
	int unknownE7C;
	int IdlePeerJoinAbortTimeout;
	int unknownE84;
	int IdlePeerLeavingTimeout;
	int unknownE8C;
	int unknownE90;
	int unknownE94;
	int unknownE98;
	int unknownE9C;
	int unknownEA0;
	int unknownEA4;
	int unknownEA8;
	int unknownEAC;
	int unknownEB0;
	int unknownEB4;
	int unknownEB8;
	int unknownEBC;
	int unknownEC0;
	int unknownEC4;
	int unknownEC8;
	int unknownECC;
	int unknownED0;
	int unknownED4;
	int unknownED8;
	int unknownEDC;
	int unknownEE0;
	int unknownEE4;
	int unknownEE8;
	int unknownEEC;
	int unknownEF0;
	int unknownEF4;
	int unknownEF8;
	int unknownEFC;
	int unknownF00;
	int unknownF04;
	int unknownF08;
	int unknownF0C;
	int unknownF10;
	int unknownF14;
	int unknownF18;
	int unknownF1C;
	int unknownF20;
	int unknownF24;
	int unknownF28;
	int unknownF2C;
	int unknownF30;
	int ConnectionInitiationRetryCount;
	int unknownF38;
	int unknownF3C;
	int unknownF40;
	int unknownF44;
	int unknownF48;
	int unknownF4C;
	int unknownF50;
	int unknownF54;
	int unknownF58;
	int unknownF5C;
	int unknownF60;
	int unknownF64;
	int unknownF68;
	int unknownF6C;
	int unknownF70;
	int unknownF74;
	int unknownF78;
	int unknownF7C;
	int unknownF80;
	float unknownF84;
	float unknownF88;
	float unknownF8C;
	int unknownF90;
	float unknownF94;
	float unknownF98;
	float unknownF9C;
	float unknownFA0;
	float unknownFA4;
	float unknownFA8;
	float unknownFAC;
	int unknownFB0;
	int unknownFB4;
	int unknownFB8;
	int unknownFBC;
	int unknownFC0;
	int unknownFC4;
	int unknownFC8;
	int unknownFCC;
	int unknownFD0;
	int unknownFD4;
	float unknownFD8;
	float unknownFDC;
	float unknownFE0;
	float unknownFE4;
	int unknownFE8;
	int unknownFEC;
	int unknownFF0;
	int unknownFF4;
	float unknownFF8;
	int unknownFFC;
	int unknown1000;
	float unknown1004;
	int unknown1008;
	int unknown100C;
	float unknown1010;
	int unknown1014;
	int unknown1018;
	int unknown101C;
	int unknown1020;
	int unknown1024;
	int unknown1028;
	int unknown102C;
	int unknown1030;
	int unknown1034;
	__int8 unknown1038;
	int unknown103C;
	int unknown1040;
	int unknown1044;
	int unknown1048;
	int unknown104C;
	int unknown1050;
	int unknown1054;
	int unknown1058;
	int unknown105C;
	int unknown1060;
	int unknown1064;
	int unknown1068;
	int unknown106C;
	int unknown1070;
	int unknown1074;
	int unknown1078;
	int unknown107C;
	int unknown1080;
	int unknown1084;
	int unknown1088;
	int unknown108C;
	int unknown1090;
	int unknown1094;
	int unknown1098;
	int unknown109C;
	float unknown10A0;
	int unknown10A4;
	float unknown10A8;
	int unknown10AC;
	int unknown10B0;
	int unknown10B4;
	float unknown10B8;
	int unknown10BC;
	float unknown10C0;
	int unknown10C4;
	int unknown10C8;
	int unknown10CC;
	int unknown10D0;
	float unknown10D4;
	int unknown10D8;
	int unknown10DC;
	int unknown10E0;
	int unknown10E4;
	int unknown10E8;
	float unknown10EC;
	float unknown10F0;
	int unknown10F4;
	float unknown10F8;
	int unknown10FC;
	int unknown1100;
	int unknown1104;
	int unknown1108;
	int unknown110C;
	int unknown1110;
	int unknown1114;
	int unknown1118;
	int unknown111C;
	int unknown1120;
	float unknown1124;
	int unknown1128;
	int unknown112C;
	int unknown1130;
	__int16 unknown1134;
	__int8 unknown1136;
	int unknown1138;
	int unknown113C;
	int unknown1140;
	int unknown1144;
	int unknown1148;
	int unknown114C;
	int unknown1150;
	int unknown1154;
	int unknown1158;
	int unknown115C;
	int unknown1160;
	int unknown1164;
	int unknown1168;
	int unknown116C;
	int unknown1170;
	int unknown1174;
	int unknown1178;
	int unknown117C;
	int unknown1180;
	int unknown1184;
	int unknown1188;
	int unknown118C;
	int unknown1190;
	int unknown1194;
	int unknown1198;
	int unknown119C;
	int unknown11A0;
	int unknown11A4;
	int unknown11A8;
	int unknown11AC;
	int unknown11B0;
	int unknown11B4;
	int unknown11B8;
	int unknown11BC;
	int unknown11C0;
	int unknown11C4;
	int unknown11C8;
	int unknown11CC;
	int unknown11D0;
	int unknown11D4;
	int unknown11D8;
	int unknown11DC;
	int unknown11E0;
	int unknown11E4;
	int unknown11E8;
	int unknown11EC;
	int unknown11F0;
	int unknown11F4;
	int unknown11F8;
	int unknown11FC;
	int unknown1200;
	int unknown1204;
	int unknown1208;
	int unknown120C;
	int unknown1210;
	int unknown1214;
	int unknown1218;
	int unknown121C;
	int unknown1220;
	int unknown1224;
	int unknown1228;
	int unknown122C;
	int unknown1230;
	int unknown1234;
	float unknown1238;
	int unknown123C;
	int unknown1240;
	int unknown1244;
	int unknown1248;
	int unknown124C;
	int unknown1250;
	int unknown1254;
	int unknown1258;
	int unknown125C;
	int unknown1260;
	int unknown1264;
	float unknown1268;
	int unknown126C;
	int unknown1270;
	int unknown1274;
	int unknown1278;
	int unknown127C;
	int unknown1280;
	int unknown1284;
	int unknown1288;
	int unknown128C;
	int unknown1290;
	int unknown1294;
	float unknown1298;
	int unknown129C;
	int unknown12A0;
	int unknown12A4;
	int unknown12A8;
	int unknown12AC;
	int unknown12B0;
	int unknown12B4;
	int unknown12B8;
	int unknown12BC;
	int unknown12C0;
	int unknown12C4;
	float unknown12C8;
	int unknown12CC;
	int unknown12D0;
	int unknown12D4;
	int unknown12D8;
	int unknown12DC;
	int unknown12E0;
	int unknown12E4;
	int unknown12E8;
	int unknown12EC;
	int unknown12F0;
	int unknown12F4;
	int unknown12F8;
	int unknown12FC;
	int unknown1300;
	int unknown1304;
	int unknown1308;
	int unknown130C;
	int unknown1310;
	int unknown1314;
	int unknown1318;
	int unknown131C;
	int unknown1320;
	int unknown1324;
	int unknown1328;
	int unknown132C;
	int unknown1330;
	int unknown1334;
	int unknown1338;
	int unknown133C;
	float unknown1340;
	int unknown1344;
	int unknown1348;
	int unknown134C;
	int unknown1350;
	int unknown1354;
	int unknown1358;
	__int8 unknown135C;
	int unknown1360;
	int unknown1364;
	float unknown1368;
	float unknown136C;
	__int8 unknown1370;
	int unknown1374;
	int unknown1378;
	int unknown137C;
	__int8 unknown1380;
	int unknown1384;
	int unknown1388;
	float unknown138C;
	int unknown1390;
	int unknown1394;
	int unknown1398;
	int unknown139C;
	int unknown13A0;
	int LobbyFilmMaxPlayerCount;
	int unknown13A8;
	int unknown13AC;
	int unknown13B0;
	int unknown13B4;
	int unknown13B8;
	int unknown13BC;
	int unknown13C0;
	int unknown13C4;
	int unknown13C8;
	int unknown13CC;
	int unknown13D0;
	int unknown13D4;
	int unknown13D8;
	int unknown13DC;
	int unknown13E0;
	int unknown13E4;
	int unknown13E8;
	int unknown13EC;
	int unknown13F0;
	int unknown13F4;
	int unknown13F8;
	int unknown13FC;
	int unknown1400;
	int unknown1404;
	int unknown1408;
	int unknown140C;
	int unknown1410;
	int unknown1414;
	int unknown1418;
	int unknown141C;
	int unknown1420;
	int unknown1424;
	int unknown1428;
	int unknown142C;
	int unknown1430;
	int unknown1434;
	int unknown1438;
	int unknown143C;
	int unknown1440;
	int unknown1444;
	int unknown1448;
	int unknown144C;
	int unknown1450;
	int unknown1454;
	int unknown1458;
	int unknown145C;
	int unknown1460;
	int unknown1464;
	int unknown1468;
	int unknown146C;
	int unknown1470;
	int unknown1474;
	int unknown1478;
	int unknown147C;
	int unknown1480;
	int unknown1484;
	int unknown1488;
	int unknown148C;
	int unknown1490;
	int unknown1494;
	int unknown1498;
	int unknown149C;
	int unknown14A0;
	int unknown14A4;
	int unknown14A8;
	int unknown14AC;
	int unknown14B0;
	int unknown14B4;
	int unknown14B8;
	int unknown14BC;
	int unknown14C0;
	int unknown14C4;
	int unknown14C8;
	int unknown14CC;
	int unknown14D0;
	int unknown14D4;
	int unknown14D8;
	int unknown14DC;
	int unknown14E0;
	int unknown14E4;
	int unknown14E8;
	int unknown14EC;
	int unknown14F0;
	int unknown14F4;
	int unknown14F8;
	int unknown14FC;
	int unknown1500;
	int unknown1504;
	int unknown1508;
	int unknown150C;
	int unknown1510;
	int unknown1514;
	int unknown1518;
	int unknown151C;
	int unknown1520;
	int unknown1524;
	int unknown1528;
	int unknown152C;
	int unknown1530;
	int unknown1534;
	int unknown1538;
	int unknown153C;
	int unknown1540;
	int unknown1544;
	int unknown1548;
	int unknown154C;
	int unknown1550;
	int unknown1554;
	int unknown1558;
	int unknown155C;
	int unknown1560;
	int unknown1564;
	int unknown1568;
	int unknown156C;
	int unknown1570;
	int unknown1574;
	int unknown1578;
	int unknown157C;
	int unknown1580;
	int unknown1584;
	int unknown1588;
	int unknown158C;
	__int16 unknown1590;
	__int8 unknown1592[2];
	int NetworkModeDefault;
	int OfflineMaxPlayerCount;
	__int8 unknown159C;
	int unknown15A0;
	int unknown15A4;
	int unknown15A8;
	int unknown15AC;
	int unknown15B0;
	int unknown15B4;
	int unknown15B8;
	int unknown15BC;
	int unknown15C0;
	int unknown15C4;
	int unknown15C8;
	int unknown15CC;
	int unknown15D0;
	int unknown15D4;
	int unknown15D8;
	int unknown15DC;
	int unknown15E0;
	int unknown15E4;
	int unknown15E8;
	int unknown15EC;
	int unknown15F0;
	int unknown15F4;
	int unknown15F8;
	int unknown15FC;
	int unknown1600;
	int unknown1604;
	int unknown1608;
	int unknown160C;
	int unknown1610;
	int unknown1614;
	int unknown1618;
	int unknown161C;
	int unknown1620;
	int unknown1624;
	int unknown1628;
	int unknown162C;
	int unknown1630;
	int unknown1634;
	int unknown1638;
	int unknown163C;
	int unknown1640;
	int unknown1644;
	int unknown1648;
	int unknown164C;
	int unknown1650;
	int unknown1654;
	int unknown1658;
	int unknown165C;
	int unknown1660;
	int unknown1664;
	int unknown1668;
	int unknown166C;
	int unknown1670;
	int unknown1674;
	int unknown1678;
	int unknown167C;
	int unknown1680;
	int unknown1684;
	int unknown1688;
	int unknown168C;
	int unknown1690;
	int unknown1694;
	int unknown1698;
	int unknown169C;
	int unknown16A0;
	int unknown16A4;
	int unknown16A8;
	int unknown16AC;
	int unknown16B0;
	int unknown16B4;
	int unknown16B8;
	int DeterminismVersion;
	int unknown16C0;

	size_t Size()
	{
		return sizeof(*this);
	}

	void SetMaxOfflinePlayerCount(int player_count)
	{
		if (player_count == -1)
			return;

		OfflineMaxPlayerCount = player_count;
	}
	void SetMaxCoopPlayerCount(int player_count)
	{
		if (player_count == -1)
			return;

		LobbyCoopMaxPlayerCount = player_count;
	}
	void SetMaxForgePlayerCount(int player_count)
	{
		if (player_count == -1)
			return;

		LobbyMapeditorMaxPlayerCount = player_count;
	}
	void SetMaxTheaterPlayerCount(int player_count)
	{
		if (player_count == -1)
			return;

		LobbyFilmMaxPlayerCount = player_count;
	}
	void SetMaxPlayerCounts(int offline, int coop, int forge, int theater)
	{
		SetMaxOfflinePlayerCount(offline);
		SetMaxCoopPlayerCount(coop);
		SetMaxForgePlayerCount(forge);
		SetMaxTheaterPlayerCount(theater);
	}
};
auto& network_configuration = reference_get<s_network_configuration>(0x19A62C0);

int32_t achievement_string_ids[]{
	0x60000,
	0x60001,
	0x60002,
	0x60003,
	0x60004,
	0x60005,
	0x60006,
	0x60007,
	0x60008,
	0x60009,
	0x6000A,
	0x6000B,
	0x6000C,
	0x6000D,
	0x6000E,
	0x6000F,
	0x60010,
	0x60011,
	0x60012,
	0x60013,
	0x60014,
	0x60015,
	0x60016,
	0x60017,
	0x60018,
	0x60019,
	0x6001A,
	0x6001B,
	0x6001C,
	0x6001D,
	0x6001E,
	0x6001F,
	0x60020,
	0x60021,
	0x60022,
	0x60023,
	0x60024,
	0x60025,
	0x60026,
	0x60027,
	0x60028,
	0x60029,
	0x6002A,
	0x6002B,
	0x6002C,
	0x6002D,
	0x6002E
};

struct e_map_id
{
	enum : int
	{
		_null = 0, // mainmenu
		_mainmenu = 270735729,

		_005 = 3005,
		_010 = 3010,
		_020 = 3020,
		_030 = 3030,
		_040 = 3040,
		_050 = 3050,
		_070 = 3070,
		_100 = 3100,
		_110 = 3110,
		_120 = 3120,
		_130 = 3130,

		_zanzibar = 30,
		_construct = 300,
		_deadlock = 310,
		_guardian = 320,
		_isolation = 330,
		_riverworld = 340,
		_salvation = 350,
		_snowbound = 360,
		_chill = 380,
		_cyberdyne = 390,
		_shrine = 400,

		_bunkerworld = 410,
		_docks = 440,
		_sidewinder = 470,
		_warehouse = 480,
		_descent = 490,
		_spacecamp = 500,
		_lockout = 520,
		_armory = 580,
		_ghosttown = 590,
		_chillout = 600,
		_midship = 720,
		_sandbox = 730,
		_fortress = 740,

		_c100 = 4100,
		_c200 = 4200,
		_h100 = 5000,
		_l200 = 5200,
		_l300 = 5300,
		_sc100 = 6100,
		_sc110 = 6110,
		_sc120 = 6120,
		_sc130 = 6130,
		_sc140 = 6140,
		_sc150 = 6150,
	} value;

	const char* GetName()
	{
		if (value == _mainmenu)
			return "Main Menu";

		switch (value)
		{
		case _005:
			return "Arrival";
		case _010:
			return "Sierra 117";
		case _020:
			return "Crow's Nest";
		case _030:
			return "Tsavo Highway";
		case _040:
			return "The Storm";
		case _050:
			return "Floodgate";
		case _070:
			return "The Ark";
		case _100:
			return "The Covenant";
		case _110:
			return "Cortana";
		case _120:
			return "Halo";
		case _130:
			return "Epilogue";

		case _zanzibar:
			return "Last Resort";
		case _construct:
			return "Construct";
		case _deadlock:
			return "High Ground";
		case _guardian:
			return "Guardian";
		case _isolation:
			return "Isolation";
		case _riverworld:
			return "Valhalla";
		case _salvation:
			return "Epitaph";
		case _snowbound:
			return "Snowbound";
		case _chill:
			return "Narrows";
		case _cyberdyne:
			return "The Pit";
		case _shrine:
			return "Sandtrap";

		case _bunkerworld:
			return "Standoff";
		case _docks:
			return "Longshore";
		case _sidewinder:
			return "Avalanche";
		case _warehouse:
			return "Foundry";
		case _descent:
			return "Assembly";
		case _spacecamp:
			return "Orbital";
		case _lockout:
			return "Blackout";
		case _armory:
			return "Rat's Nest";
		case _ghosttown:
			return "Ghost Town";
		case _chillout:
			return "Cold Storage";
		case _midship:
			return "Heretic";
		case _sandbox:
			return "Sandbox";
		case _fortress:
			return "Citadel";

		case _c100:
			return "PREPARE TO DROP";
		case _c200:
			return "COASTAL HIGHWAY";
		case _h100:
			return "MOMBASA STREETS";
		case _l200:
			return "DATA HIVE";
		case _l300:
			return "COASTAL HIGHWAY";
		case _sc100:
			return "TAYARI PLAZA";
		case _sc110:
			return "UPLIFT RESERVE";
		case _sc120:
			return "KIZINGO BLVD.";
		case _sc130:
			return "ONI ALPHA SITE";
		case _sc140:
			return "NMPD HQ";
		case _sc150:
			return "KIKOWANI STN.";
		}

		return "";
	}

	const char* GetDescription()
	{
		if (value == _mainmenu)
			return "This is the main menu.";

		switch (value)
		{
		case _005:
			return "Brace for impact.";
		case _010:
			return "Rise up. Start the fight.";
		case _020:
			return "Clear the base, whatever it takes.";
		case _030:
			return "Mount up. Get to Voi.";
		case _040:
			return "Reclaim the city. Make a hole.";
		case _050:
			return "Stop the infestation. Find Cortana.";
		case _070:
			return "Search the waste for the Cartographer.";
		case _100:
			return "Breach the barrier. Stop Truth.";
		case _110:
			return "Cleanse High Charity. Save Cortana.";
		case _120:
			return "Light the ring. Destroy the Flood.";
		case _130:
			return "Epilogue";

		case _zanzibar:
			return "Remote industrial sites like this one are routinely requisitioned and razed as part of Spartan training exercises. 4-12 players";
		case _construct:
			return "Vast quantities of water and other raw materials are consumed in creating even the smallest orbital installations. 2-8 players";
		case _deadlock:
			return "A relic of older conflicts, this base was reactivated after the New Mombasa Slipspace Event. 4-12 players";
		case _guardian:
			return "Millennia of tending has produced trees as ancient as the Forerunner structures they have grown around. 2-6 players";
		case _isolation:
			return "Containment protocols are almost impervious to pre-Gravemind infestations. What could possibly go wrong? 2-10 players";
		case _riverworld:
			return "The crew of V-398 barely survived their unplanned landing in this gorge... this curious gorge. 6-16 players";
		case _salvation:
			return "Some believe the Forerunners preferred desolate places. Others suggest that few other sites survived the Flood. 2-6 players";
		case _snowbound:
			return "Hostile conditions did not prevent the Covenant from seeking salvage on this buried Forerunner construct. 2-8 players";
		case _chill:
			return "Without cooling systems such as these, excess heat from The Ark's forges would render the construct uninhabitable. 2-8 players";
		case _cyberdyne:
			return "Software simulations are held in contempt by the veteran instructors who run these training facilities. 4-10 players";
		case _shrine:
			return "Although the Brute occupiers have been driven from this ancient structure, they left plenty to remember them by. 6-16 players";

		case _bunkerworld:
			return "Once, nearby telescopes listened for a message from the stars. Now, these silos contain our prepared response. 4-12 players";
		case _docks:
			return "Abandoned during the invasion of Earth, the Mombasa Quays are now bereft of commerce, but rife with danger. 4-12 players";
		case _sidewinder:
			return "Freezing winds scour blasted terrain, and ancient battle scars are a grim reminder that this is a precious prize. 6-16 players";
		case _warehouse:
			return "After the orbital elevator fell, supply warehouses sending munitions to space were soon abandoned. 4-12 players";
		case _descent:
			return "The Covenant war machine continues its march to conquest; even with its head severed it is still dangerous. 2-8 players";
		case _spacecamp:
			return "With a lot of situational awareness, and a little luck, hopefully the only thing you will lose is your luggage. 4-12 players";
		case _lockout:
			return "Bathed in frozen moonlight, this abandoned drilling platform is now a monument to human frailty. 4-12 players";
		case _armory:
			return "Snowmelt from Kilimanjaro feeds reservoirs every bit as vital as the fuel and ammunition stores. 6-16 players";
		case _ghosttown:
			return "These fractured remains near Voi remind us that brave souls died here to buy our salvation. 4-12 players";
		case _chillout:
			return "Deep in the bowels of Installation 05 things have gotten a little out of hand. I hope you packed extra underwear. 2-6 players";
		case _midship:
			return "Because of its speed and luxury the Pious Inquisitor has become an irresistible prize during these dark times. 2-8 players";
		case _sandbox:
			return "This endless wasteland still holds many secrets. Some of them are held more deeply than others. 4-12 players";
		case _fortress:
			return "In the heart of this Forerunner structure, far above the troubled surface of the Ark, another battle rages. 2-6 players";

		case _c100:
			return "Start a new game, drop into the nighttime city.";
		case _c200:
			return "The end of the road.";
		case _h100:
			return "Explore the city, find your ODST team.";
		case _l200:
			return "Find Dare, secure the Superintendent.";
		case _l300:
			return "Escort the asset out of the city.";
		case _sc100:
			return "Beat the Covenant to Dare's crash-site.";
		case _sc110:
			return "Lead a Warthog charge, clear hostiles from the park.";
		case _sc120:
			return "Scorpion rampage through the heart of the city.";
		case _sc130:
			return "Fall back, deny access to this vital facility.";
		case _sc140:
			return "Pelican down. Keep your sniper rifle handy.";
		case _sc150:
			return "Aerial combat in the flooded city.";
		}

		return "";
	}

	const char* GetImageName()
	{
		return "test image name";

		switch (value)
		{
		case _005:
			return "c_005";
		case _010:
			return "c_010";
		case _020:
			return "c_020";
		case _030:
			return "c_030";
		case _040:
			return "c_040";
		case _050:
			return "c_050";
		case _070:
			return "c_070";
		case _100:
			return "c_100";
		case _110:
			return "c_110";
		case _120:
			return "c_120";
		case _130:
			return "c_130";

		case _zanzibar:
			return "m_zanzibar";
		case _construct:
			return "m_construct";
		case _deadlock:
			return "m_deadlock";
		case _guardian:
			return "m_guardian";
		case _isolation:
			return "m_isolation";
		case _riverworld:
			return "m_riverworld";
		case _salvation:
			return "m_salvation";
		case _snowbound:
			return "m_snowbound";
		case _chill:
			return "m_chill";
		case _cyberdyne:
			return "m_cyberdyne";
		case _shrine:
			return "m_shrine";

		case _bunkerworld:
			return "dlc_bunkerworld";
		case _docks:
			return "dlc_docks";
		case _sidewinder:
			return "dlc_sidewinder";
		case _warehouse:
			return "dlc_warehouse";
		case _descent:
			return "dlc_descent";
		case _spacecamp:
			return "dlc_spacecamp";
		case _lockout:
			return "dlc_lockout";
		case _armory:
			return "dlc_armory";
		case _ghosttown:
			return "dlc_ghosttown";
		case _chillout:
			return "dlc_chillout";
		case _midship:
			return "dlc_midship";
		case _sandbox:
			return "dl_sandboxc";
		case _fortress:
			return "dlc_fortress";

		case _c100:
			return "c_c100";
		case _c200:
			return "c_c200";
		case _h100:
			return "c_h100";
		case _l200:
			return "c_l200";
		case _l300:
			return "c_l300";
		case _sc100:
			return "c_sc100";
		case _sc110:
			return "c_sc110";
		case _sc120:
			return "c_sc120";
		case _sc130:
			return "c_sc130";
		case _sc140:
			return "c_sc140";
		case _sc150:
			return "c_sc150";
		}

		return "";
	}

	const char* GetInsertionPointName(e_insertion_point insertion_point)
	{
		if (value == _mainmenu)
			return "";

		if (insertion_point.value < 4 && value == _130 && insertion_point.value == 1)
			return "Epilogue";

		switch (value)
		{
		case _h100:
			if (insertion_point.value == 7)
				return "CRATER (NIGHT)";
			else if (insertion_point.value == 8)
				return "RALLY (NIGHT)";
			return insertion_point.GetName();
		case _l200:
			if (insertion_point.value == 6)
				return "CHASM TEN";
			else if (insertion_point.value == 7)
				return "DATA CORE";
			return insertion_point.GetName();
		case _l300:
			if (insertion_point.value == 7)
				return "LAST EXIT";
			return insertion_point.GetName();
		case _sc100:
			if (insertion_point.value == 4)
				return "CRATER";
			return insertion_point.GetName();
		case _sc110:
			if (insertion_point.value == 4)
				return "LOST PLATOON";
			return insertion_point.GetName();
		case _sc120:
			if (insertion_point.value == 5)
				return "RALLY POINT";
			return insertion_point.GetName();
		case _sc130:
			if (insertion_point.value == 4)
				return "SECURITY ZONE";
			else if (insertion_point.value == 5)
				return "ALPHA SITE";
			return insertion_point.GetName();
		case _sc140:
			if (insertion_point.value == 4)
				return "WINDWARD";
			return insertion_point.GetName();
		}

		return insertion_point.GetName();
	}

	const char* GetInsertionPointDescription(e_insertion_point insertion_point)
	{
		if (value == _mainmenu)
			return "";

		std::vector<const char*> names;

		if (insertion_point.value < 4)
		{
			switch (value) // Halo 3
			{
			case _005:
				if (insertion_point.value == 0)
					return "Brace for impact";
			case _010:
				names.push_back("Brutes on the prowl.");
				names.push_back("Hostile air inbound.");
				names.push_back("Rescue at the dam.");
				if (insertion_point.value < 3)
					return names[insertion_point.value];
			case _020:
				names.push_back("Perimeter breach.");
				names.push_back("Butchers in the barracks.");
				names.push_back("Bomb armed. Time to go.");
				if (insertion_point.value < 3)
					return names[insertion_point.value];
			case _030:
				names.push_back("Warning: Hitchhikers may have jetpacks.");
				names.push_back("Wraiths and Choppers.");
				if (insertion_point.value < 2)
					return names[insertion_point.value];
			case _040:
				names.push_back("Military Operations Urban Terrain.");
				names.push_back("Scarab. BFG. End of World.");
				if (insertion_point.value < 2)
					return names[insertion_point.value];
			case _050:
				names.push_back("Hot zone. Weapons free.");
				names.push_back("The Flood. It has evolved.");
				if (insertion_point.value < 2)
					return names[insertion_point.value];
			case _070:
				names.push_back("Sharpshooter.");
				names.push_back("Armor up.");
				names.push_back("Bang and clear.");
				if (insertion_point.value < 3)
					return names[insertion_point.value];
			case _100:
				names.push_back("Three teams. Three towers.");
				names.push_back("Close air support.");
				names.push_back("Storm the Citadel.");
				if (insertion_point.value < 3)
					return names[insertion_point.value];
			case _110:
				names.push_back("Graverobber.");
				names.push_back("Shoot your way out.");
				if (insertion_point.value < 2)
					return names[insertion_point.value];
			case _120:
				names.push_back("Assault on the Control Room.");
				names.push_back("Pedal to the metal.");
				if (insertion_point.value < 2)
					return names[insertion_point.value];
			case _130:
				if (insertion_point.value == 0)
					return "Epilogue";
			}
		}

		switch (value)
		{
		case _h100:
			if (insertion_point.value == 7)
				return "Fight in Dare's sunken crash-site.";
			else if (insertion_point.value == 8)
				return "Fight with your back against the wall.";
			return insertion_point.GetName();
		case _l200:
			if (insertion_point.value == 6 || insertion_point.value == 7)
				return "Fight in the infested underground.";
		case _l300:
			if (insertion_point.value == 7)
				return "Fight at the end of the road.";
		case _sc100:
			if (insertion_point.value == 4)
				return "Fight in Dare's sunken crash-site.";
		case _sc110:
			if (insertion_point.value == 4)
				return "Fight in the dead center of the park.";
		case _sc120:
			if (insertion_point.value == 5)
				return "Fight with your back against the wall.";
		case _sc130:
			if (insertion_point.value == 4)
				return "Fight in the wide-open ONI exterior.";
			else if (insertion_point.value == 5)
				return "Fight in the close-quarters ONI interior.";
			return insertion_point.GetName();
		case _sc140:
			if (insertion_point.value == 4)
				return "Fight high above the city streets.";
		}

		return insertion_point.GetName();
	}
};

struct e_achievement
{
	enum : signed int
	{
		_beat_sc100 = 0,
		_beat_sc110,
		_beat_sc120,
		_beat_sc130,
		_beat_sc140,
		_beat_sc150,
		_beat_l200,
		_beat_l300,
		_beat_campaign_normal,
		_beat_campaign_heroic,
		_beat_campaign_legendary,
		_wraith_killer,
		_naughty_naughty,
		_good_samaritan,
		_dome_inspector,
		_laser_blaster,
		_both_tubes,
		_i_like_fire,
		_my_clothes,
		_pink_and_deadly,
		_dark_times,
		_trading_down,
		_headcase,
		_boom_headshot,
		_ewww_sticky,
		_junior_detective,
		_gumshoe,
		_super_sleuth,
		_metagame_points_in_sc100,
		_metagame_points_in_sc110,
		_metagame_points_in_sc120,
		_metagame_points_in_sc130a,
		_metagame_points_in_sc130b,
		_metagame_points_in_sc140,
		_metagame_points_in_l200,
		_metagame_points_in_l300,
		_be_like_marty,
		_find_all_audio_logs,
		_find_01_audio_logs,
		_find_03_audio_logs,
		_find_15_audio_logs,
		_vidmaster_challenge_deja_vu,
		_vidmaster_challenge_endure,
		_vidmaster_challenge_classic,
		_heal_up,
		_stunning,
		_tourist,

		k_number_of_achievements
	} value;

	const char* GetName()
	{
		const char* names[]{
			"beat sc110",
			"beat sc120",
			"beat sc130",
			"beat sc140",
			"beat sc150",
			"beat l200",
			"beat l300",
			"beat campaign normal",
			"beat campaign heroic",
			"beat campaign legendary",
			"wraith killer",
			"naughty naughty",
			"good samaritan",
			"dome inspector",
			"laser blaster",
			"both tubes",
			"i like fire",
			"my clothes",
			"pink and deadly",
			"dark times",
			"trading down",
			"headcase",
			"boom headshot",
			"ewww sticky",
			"junior detective",
			"gumshoe",
			"super sleuth",
			"metagame points in sc100",
			"metagame points in sc110",
			"metagame points in sc120",
			"metagame points in sc130a",
			"metagame points in sc130b",
			"metagame points in sc140",
			"metagame points in l200",
			"metagame points in l300",
			"be like marty",
			"find all audio logs",
			"find 01 audio logs",
			"find 03 audio logs",
			"find 15 audio logs",
			"vidmaster challenge deja vu",
			"vidmaster challenge endure",
			"vidmaster challenge classic",
			"heal up",
			"stunning",
			"tourist",
		};
		return names[value];
	}

	const char* GetDescription()
	{
		const char* description[]{
			"Complete Uplift Reserve on Normal, Heroic, or Legendary to unlock a new Firefight character.",
			"Complete Kizingo Blvd. on Normal, Heroic, or Legendary to unlock a new Firefight character.",
			"Complete ONI Alpha Site on Normal, Heroic, or Legendary to unlock a new Firefight mission.",
			"Complete NMPD HQ on Normal, Heroic, or Legendary to unlock a new Firefight character.",
			"Complete Kikowani Station on Normal, Heroic, or Legendary.",
			"Complete Data Hive on Normal, Heroic, or Legendary to unlock a new Firefight mission.",
			"Complete Coastal Highway on Normal, Heroic, or Legendary to unlock a new Firefight mission.",
			"Complete the Campaign on Normal difficulty.",
			"Complete the Campaign on Heroic difficulty.",
			"Complete the Campaign on Legendary to unlock a new Firefight character.",
			"Kill all Wraiths in Uplift Reserve.",
			"Killing things that are new and different is good, alone or with another ODST.",
			"Killing things that are new and different is bad, alone or with another ODST.",
			"Get 15 headshot kills on NMPD HQ.",
			"Get 10 Spartan Laser kills on ONI Alpha Site.",
			"Get 10 Rocket kills on Kizingo Boulevard.",
			"Kill 10 enemies with the Flamethrower on Data Hive.",
			"Plasma Pistol Overcharge and quickly kill 10 Brutes.",
			"Get 10 Needler supercombine kills on any covenant.",
			"Kill 5 enemies while using VISR mode.",
			"Trade weapons with a fellow character.",
			"Finish any level with at least one Skull activated.",
			"Get 10 automag headshot kills in any level.",
			"Get 5 sticky grenade kills in any level.",
			"Find the first clue unraveling the mystery.",
			"Find the 3rd clue unraveling the mystery, alone or with another ODST.",
			"Find the final clue unraveling the mystery, alone or with another ODST.",
			"Score over 200,000 points in Firefight on Crater.",
			"Score over 200,000 points in Firefight on Lost Platoon.",
			"Score over 200,000 points in Firefight on Rally Point.",
			"Score over 200,000 points in Firefight on Security Zone.",
			"Score over 200,000 points in Firefight on Alpha Site.",
			"Score over 200,000 points in Firefight on Windward.",
			"Score over 200,000 points in Firefight on Chasm Ten.",
			"Score over 200,000 points in Firefight on Last Exit.",
			"In Firefight, finish a full round without killing a single enemy.",
			"Find all Audio Logs, alone or with another ODST.",
			"Find the first Audio Log.",
			"Find 3 Audio Logs, alone or with another ODST.",
			"Find 15 Audio Logs, alone or with another ODST.",
			"Complete Highway on 4-player Legendary LIVE co-op, with Iron, and no 'Hog or Scorpion.",
			"In Firefight, on any mission, pass the 4th Set on 4-player Heroic LIVE co-op.",
			"Finish any level solo on Legendary, on LIVE, with no shots fired or grenades thrown.",
			"Find the first Medical Kiosk and heal yourself.",
			"Stun a vehicle with an overcharged plasma pistol and quickly kill the driver.",
			"Access and download the city map to your VISR.",
		};
		return description[value];
	}

	bool check_is_valid(int local_user_index, int index)
	{
		if (index < k_number_of_achievements)
			return ((1 << (index & 31)) & reference_get<c_controller_interface>(0x524EC48, local_user_index).Achievements[index >> 5]) != 0;
		return false;
	}

	bool __cdecl get_if_valid(int local_user_index, int index)
	{
		return check_is_valid(local_user_index, index) || (1 << (index & 31)) & reference_get<int>(0x584BA20, (index >> 5) + 2 * local_user_index);
	}

	signed int grant(int local_user_index, int index)
	{
		signed int result = ((get_if_valid(local_user_index, index) && true) ? 6 : -1);
		if (result == -1)
		{
			result = 1 << (index & 31);
			reference_get<int>(0x584BA20, (index >> 5) + 2 * local_user_index) |= result;
		}
		return result;
	}

	signed int grant_level(int local_user_index, int map_id, int campaign_difficulty)
	{
		signed int result = -1;
		if (campaign_difficulty > e_difficulty_level::k_number_of_difficulty_levels)
			for (size_t achievement_index = 0; achievement_index <= _beat_l300; achievement_index++)
				result = grant(local_user_index, achievement_index);
		return result;
	}

	signed int get_from_string_id(int achievement_string_id)
	{
		for (size_t achievement_index = 0; achievement_index < k_number_of_achievements; achievement_index++)
			if (achievement_string_ids[achievement_index] == achievement_string_id)
				return achievement_index;
		return -1;
	}
};

struct e_tag_runtime
{
	enum e : __int32
	{
		_ui,

		_resources,
		_textures,
		_textures_b,
		_audio,
		_video,

		_tags = 8,

		k_number_of_tag_runtimes = 15
	} value;

	e_tag_runtime(int val)
	{
		value = (e)val;
	}

	const char* GetName()
	{
		const char* result = "<unknown>";
		switch (value)
		{
		case _ui:
			result = "ui";
		case _resources:
			result = "resources";
		case _textures:
			result = "textures";
		case _textures_b:
			result = "textures_b";
		case _audio:
			result = "audio";
		case _video:
			result = "video";
		case _tags:
			result = "tags";
		}
		return result;
	}
};

enum class alignas(2) e_cache_file_type : char { none = -1, campaign, multiplayer, mainmenu, shared, shared_campaign, unknown5, unknown6, k_number_of_cache_file_types };
enum class alignas(2) e_cache_file_shared_type : char { none = -1, mainmenu, shared, campaign, unknown3, unknown4, unknown5, k_number_of_cache_file_shared_types };
enum class alignas(4) e_external_dependency : char {
	ui = 1 << e_tag_runtime::_ui,
	resources = 1 << e_tag_runtime::_resources,
	textures = 1 << e_tag_runtime::_textures,
	textures_b = 1 << e_tag_runtime::_textures_b,
	audio = 1 << e_tag_runtime::_audio,
	video = 1 << e_tag_runtime::_video

	//	added in later builds
	//  lightmaps = 1 << 6
	//	render_models = 1 << 7
};
enum class alignas(4) e_cache_file_partition_type : char { resources, sound_resources, global_tags, shared_tags, base, map_tags, k_number_of_cache_file_partition_types };
enum class alignas(4) e_cache_file_section_type : char { debug, resource, tag, localization, k_number_of_cache_file_section_types };
struct s_cache_file_header
{
	char HeadTag[4]; // 'head'

	int32_t Version; // 12

	int32_t FileLength; // 339984

	int32_t unknownC; // 0

	uint32_t TagIndexAddress; // 0
	int32_t MemoryBufferOffset; // 0
	int32_t MemoryBufferSize; // 0

	char SourceFile[256]; // 0, runtime

	char Build[32]; // 1.106708 cert_ms23

	e_cache_file_type CacheType; // campaign
	e_cache_file_shared_type SharedType; // none

	bool unknown140; // true
	bool TrackedBuild; // true
	bool unknown142; // false
	uint8_t unknown143; // 0

	FILETIME DateTime_Unknown; // 0

	int32_t unknown14C;	// 0
	int32_t unknown150;	// 0
	int32_t unknown154;	// 0

	int32_t StringIDsCount; // 0
	int32_t StringIDsBufferSize; // 0
	int32_t StringIDsIndicesOffset; // 0
	int32_t StringIDsBufferOffset; // 0

	char __declspec(align(4)) ExternalDependencies; // 62, 00111110, resources|textures|textures_b|audio|video

	// 84 1F 26 07 1C 63 D0 01
	FILETIME DateTime;

	// { 04 17 79 CC 1B 63 D0 01, 1B 93 92 CC 1B 63 D0 01, 1B 93 92 CC 1B 63 D0 01, 1B 93 92 CC 1B 63 D0 01, 1B 93 92 CC 1B 63 D0 01, 1B 93 92 CC 1B 63 D0 01 }
	FILETIME DateTime_CacheFileShared[6];

	char Name[32]; // mainmenu

	int32_t unknown1C4; // 0

	char scenario_path[256];	// levels\ui\mainmenu\mainmenu

	int32_t MinorVersion; // -1

	int32_t TagNamesCount; // 0
	int32_t TagNamesBufferOffset; // 0
	int32_t TagNamesBufferSize; // 0
	int32_t TagNamesIndicesOffset; // 0

	struct s_cache_file_partition
	{
		uint32_t BaseAddress; // 13200
		int32_t Size; // 326784
	} Partitions[1];

	int32_t UnkownCount; // 0

	// { 67 64 03 CF, AE D0 75 DF, 50 E7 5B 75, 6B 4A BB F4 }
	uint32_t unknown2E8[4];

	// { E8 54 8F C6, D6 CC 92 15, 97 DC F5 EE, B9 3C 01 3C, 00 00 00 00 }
	int32_t SHA1_A[5];
	// { F4 17 00 00, 00 00 00 00, 00 00 00 00, FC 7B 19 64, A6 0E 80 17 }
	int32_t SHA1_B[5];
	// { B6 C9 33 03, FF 54 BF 54, CE AE 9E F2, F8 F5 F4 9F, E2 44 00 F3 }
	int32_t SHA1_C[5];
	// { 60 13 95 76, B3 99 02 B9, 92 04 46 C5, B5 68 D5 02, 3C 3C 6B 49, 98 93 31 52, DB 88 CB BA, B9 E5 FB 8F, 
	//   1F BC 16 61, DE 51 1F 05, 95 DD C2 02, 0C 41 6A F2, B6 36 C4 CA, DC E0 40 2A, 84 9E 3C 29, FD F4 A1 02, 
	//   C1 39 00 F2, 58 6D 63 BE, 9D 8E 40 6D, 67 78 E9 F3, 77 50 CB C8, 08 8E 12 F7, F7 44 08 4F, 7D 1F 4C CE, 
	//   1E 4C C4 23, 1E 7D 7D B4, F1 3C 58 50, E2 76 34 AA, 14 B5 85 5C, EC 6D BC FC, C8 A4 89 EA, 07 C8 3B 69, 
	//   26 0C 2C 8A, 72 76 D6 D6, 2D D8 ED 1D, 74 32 E4 C4, B2 BA B8 0A, 39 DC BF 4E, B4 87 7D EC, 03 61 75 72, 
	//   0A 32 0E 21, C2 65 DB 5F, 04 97 BD C6, 40 EB 4E C7, 3C 26 9A CC, 1F 2A 05 02, EB 03 B7 BD, 9C 0B 24 EA, 
	//   5C E1 33 84, E1 5E 84 93, 63 EA 59 94, 0D AD 59 62, 8E 2C 0C EB, BA 58 3D 19, 2A 65 E1 FA, BF 56 A9 34, 
	//   06 C3 61 49, 2C F4 0E 88, 75 F9 8F AC, 23 08 A5 22, 9F 5B 1E 56, 9A FE 00 0C, A4 33 D4 A5, E8 FF F8 A5  }
	int32_t RSA[64];

	struct s_cache_file_interop
	{
		uint32_t ResourceBaseAddress; // 0
		int32_t DebugSectionSize; // 0
		uint32_t RuntimeBaseAddress; // 0
		uint32_t UnknownBaseAddress; // 0
		struct s_cache_file_section
		{
			uint32_t VirtualAddress; // 13200, 13200, 13200, -1
			int32_t Size; // 326784, 0, 0, 0
		} Sections[4];
	} Interop;

	UUID GUID;

	short unknown474; // 0
	short unknown476; // 0

	int32_t unknown478; // 0

	UUID CompressionGUID; // 0

	uint8_t Elements1[0x2300]; // 0

	// requires unknown142 be enabled
	int32_t CampaignInsertionPoint; // 0
	struct s_cache_file_insertion
	{
		uint8_t data[0xB4]; // 0
	} CampaignInsertion[9];

	uint32_t TagAddressOffset; // 0
	int32_t TagIndexCount; // 0

	e_map_id map_id; // 0
	int32_t ScenarioTagIndex; // 0x27C3

	uint8_t Elements2[0x468]; // 0

	uint8_t unknown325C[0x12C]; // 0

	uint32_t unknown3388; // 0

	char FootTag[4]; // 'foot'

	size_t Size()
	{
		return sizeof(*this);
	}

	bool MoveTo(s_cache_file_header* cache_file_header)
	{
		memset(cache_file_header, 0, sizeof(s_cache_file_header));
		memmove(cache_file_header, this, sizeof(s_cache_file_header));

		return true;
	}
	bool MoveFrom(s_cache_file_header* cache_file_header)
	{
		memset(this, 0, sizeof(s_cache_file_header));
		memmove(this, cache_file_header, sizeof(s_cache_file_header));

		return true;
	}
	bool CopyTo(s_cache_file_header* cache_file_header)
	{
		memset(cache_file_header, 0, sizeof(s_cache_file_header));
		memcpy(cache_file_header, this, sizeof(s_cache_file_header));

		return true;
	}
	bool CopyFrom(s_cache_file_header* cache_file_header)
	{
		memset(this, 0, sizeof(s_cache_file_header));
		memcpy(this, cache_file_header, sizeof(s_cache_file_header));

		return true;
	}
};
static_assert(sizeof(s_cache_file_header) == 0x3390, "s_cache_file_header wrong size");
auto& g_cache_file_header = reference_get<s_cache_file_header>(0x22AB018);

struct s_cache_file_tag_runtime
{
	LPVOID FileHandle;
	uint32_t unknown4;

	s_cache_file_header Header;

	uint32_t IoCompletionKey;
	LPVOID FileHandle2;

	size_t Size()
	{
		return sizeof(*this);
	}

	void InvalidateHandles()
	{
		FileHandle = nullptr;
		FileHandle2 = nullptr;
	}

	bool MoveTo(s_cache_file_tag_runtime* tag_runtime)
	{
		memset(tag_runtime, 0, sizeof(s_cache_file_tag_runtime));
		memmove(tag_runtime, this, sizeof(s_cache_file_tag_runtime));

		return true;
	}
	bool MoveFrom(s_cache_file_tag_runtime* tag_runtime)
	{
		memset(this, 0, sizeof(s_cache_file_tag_runtime));
		memmove(this, tag_runtime, sizeof(s_cache_file_tag_runtime));

		return true;
	}
	bool CopyTo(s_cache_file_tag_runtime* tag_runtime)
	{
		memset(tag_runtime, 0, sizeof(s_cache_file_tag_runtime));
		memcpy(tag_runtime, this, sizeof(s_cache_file_tag_runtime));

		return true;
	}
	bool CopyFrom(s_cache_file_tag_runtime* tag_runtime)
	{
		memset(this, 0, sizeof(s_cache_file_tag_runtime));
		memcpy(this, tag_runtime, sizeof(s_cache_file_tag_runtime));

		return true;
	}
};
static_assert(sizeof(s_cache_file_tag_runtime) == 0x33A0, "s_cache_file_tag_runtime wrong size");

struct s_cache_file
{
	s_cache_file_tag_runtime TagRuntimes[e_tag_runtime::k_number_of_tag_runtimes];

	int32_t RuntimeIndex;

	int32_t unknown30664;

	int32_t RuntimeCount;

	int32_t UnknownType;

	uint8_t unknown30670[8][0x108];

	void InvalidateAllHandles()
	{
		for (int i = 0; i < (int)e_tag_runtime::k_number_of_tag_runtimes; i++)
			TagRuntimes[i].InvalidateHandles();
	}
};
static_assert(sizeof(s_cache_file) == 0x30EB0, "s_cache_file wrong size");

struct s_cache
{
	bool initialized;

	uint8_t unknown1[7];

	s_cache_file CacheFile;

	uint8_t part2[0x36E8];
	uint8_t part3[0x3B8];
};
static_assert(sizeof(s_cache) == 0x34958, "s_cache wrong size");
auto& g_cache = reference_get<s_cache>(0x240B1E0);

auto g_default_map_path = "maps\\";
std::string g_map_path = g_default_map_path;

template<typename T>
struct point2d
{
	T X, Y;
};

template<typename T>
struct point3d
{
	T X, Y, Z;
};

template<typename T>
struct point4d
{
	T X, Y, Z, W;
};

template<typename T>
struct vector2d
{
	T I, J;
};

template<typename T>
struct vector3d
{
	T I, J, K;
};

template<typename T>
struct vector4d
{
	T I, J, K, W;
};

template<typename T>
struct clip_plane
{
	T Near, Far;
};

struct s_field_of_view
{
	float Radians;

	float Get()
	{
		return (float)(Radians / 0.0174533);
	}
	s_field_of_view* Set(float fov)
	{
		Radians = (float)(fov * 0.0174533);

		return this;
	}
	s_field_of_view* ConvertForWeapon(float* weapon_fov, float(__cdecl* map)(double, double, double, double, double))
	{
		auto fov = Get();
		if (fov > 90)
		{
			auto new_val = fov < 90 ? map(fov, 55, 70, 1.15, 1.0) : map(fov, 55, 120, 1.15, 0.7);
			*weapon_fov = new_val +
				fov < 90 ? new_val :
				fov < 100 ? new_val + 0.05f :
				fov < 110 ? new_val + 0.15f :
				fov < 120 ? new_val + 0.25f :
				fov < 130 ? new_val + 0.35f :
				fov < 140 ? new_val + 0.45f :
				new_val + 0.55f;
		}

		return this;
	}
};

struct s_camera_definition
{
	uint32_t StateFlags;
	vector3d<float> Position;
	vector3d<float> PositionShift;
	float Look;
	float LookShift;
	float Depth;
	s_field_of_view FieldOfView;
	vector3d<float> Forward;
	vector3d<float> Up;
	vector3d<float> Direction;
	uint8_t unknown50[56];
	vector3d<float> Center; // unsure
	float unknown94;
	uint32_t RootObjectHandle;
	uint8_t unknown9C[28];
	byte FlagsB8;
	uint8_t unknownB9[3];
	uint8_t unknownBC;
	uint8_t unknownBD[19];
	float ZoomTransitionTime;
	uint8_t unknownD4[4];
	uint32_t FlagsD8;
	uint8_t unknownDC[16];

	s_camera_definition(uint8_t* camera_definition)
	{
		*this = *(s_camera_definition*)camera_definition;
	}

	size_t Size()
	{
		return sizeof(*this);
	}

	s_camera_definition* Validate(bool* result)
	{
		*result = ((char(__cdecl*)(uint8_t*))0x614CB0)((uint8_t*)this);

		return this;
	}

	s_camera_definition* ConvertForWeapon(float* weapon_fov, float(__cdecl* map)(double, double, double, double, double))
	{
		if (LookShift == 0.17f) // check the crosshair is lower third
			FieldOfView.ConvertForWeapon(weapon_fov, map); // scales the biped arms doesn't pull the weapon back, thus still covers 1/3rd the screen space

		return this;
	}

	s_camera_definition* Print(bool position_and_shift, bool look_and_depth_and_fov, bool forward_and_up_and_direction, bool center_and_zoom_transition_time)
	{
		if (Direction.I != 0.f || Direction.J != 0.f || Direction.K != 0.f)
		{
			if (position_and_shift)
				printf_s("pos: %.2f %.2f %.2f, pos_shift: %.2f %.2f %.2f\n", Position.I, Position.J, Position.K, PositionShift.I, PositionShift.J, PositionShift.K);
			if (look_and_depth_and_fov)
				printf_s("look: %.2f, look_shift: %.2f, depth: %.2f, fov: %.0f\n", Look, LookShift, Depth, FieldOfView.Get());
			if (forward_and_up_and_direction)
				printf_s("forward: %.2f %.2f %.2f, up: %.2f %.2f %.2f, direction: %.2f %.2f %.2f\n", Forward.I, Forward.J, Forward.K, Up.I, Up.J, Up.K, Direction.I, Direction.J, Direction.K);
			if (center_and_zoom_transition_time)
				printf_s("center: %.2f %.2f %.2f, zoom_transition_time: %.2f\n", Center.I, Center.J, Center.K, ZoomTransitionTime);
		}

		return this;
	}
};
_STATIC_ASSERT(sizeof(s_camera_definition) == 0xEC);

struct s_global_cache_info
{
	uint8_t*** tag_table_ptr = (uint8_t***)0x22AAFF8;
	uint32_t** tag_index_table_ptr = (uint32_t**)0x22AAFFC;
	uint32_t* max_tag_count_ptr = (uint32_t*)0x22AB008;

	uint8_t*** resource_table_ptr = (uint8_t***)0x22AB00C;
	uint32_t** resource_index_table_ptr = (uint32_t**)0x22AB010;
	uint32_t* max_resource_count_ptr = (uint32_t*)0x22AB014;

	uint16_t last_tag_index = 0xFFFF;
	uint32_t last_tag_group = 'null';
	uint16_t globals_tag = 0xFFFF;
} g_cache_info;

struct s_tag
{
	enum e_tag_header_offsets
	{
		_definition = 0x10,
		_group_tag = 0x14
	};

	uint32_t Index;
	uint32_t Group;
	std::string GroupString;

	s_tag(uint32_t index, uint32_t group = 'llun')
	{
		g_cache_info.last_tag_index = Index = index;
		g_cache_info.last_tag_group = Group = group;
	}
	uint8_t* GetHeader(size_t offset = 0)
	{
		if (Index == 0xFFFF || Index >= *g_cache_info.max_tag_count_ptr * 4)
			return nullptr;
		if ((*g_cache_info.tag_index_table_ptr)[Index] == -1 || (*g_cache_info.tag_index_table_ptr)[Index] >= *g_cache_info.max_tag_count_ptr * 4)
			return nullptr;
		if (!(*g_cache_info.tag_table_ptr)[(*g_cache_info.tag_index_table_ptr)[Index]])
			return nullptr;

		return (*g_cache_info.tag_table_ptr)[(*g_cache_info.tag_index_table_ptr)[Index]] + offset;
	}
	bool HeaderIsValid()
	{
		if ((GetHeader() == nullptr) || ((uint32_t)GetHeader() < 0x400000))
			return false;
		return true;
	}
	uint32_t GetGroupTag()
	{
		return HeaderIsValid() ? *(uint32_t*)GetHeader(_group_tag) : Group;
	}
	template<typename T>
	T* GetDefinition()
	{
		return (T*)GetHeader(*(uint32_t*)GetHeader(_definition));
	}
	void UpdateGroupString()
	{
		GroupString = "";
		for (size_t i = 4; i > 0; ) GroupString += ((char*)GetHeader(_group_tag))[--i];
	}
	s_tag* Print(bool should_print, uint32_t group = -1)
	{
		if (!should_print)
			return this;

		UpdateGroupString();

		if (group == -1 || group == GetGroupTag())
			printf_s("['%s', 0x%04X]\n", GroupString.c_str(), Index);

		return this;
	}
};

struct s_join_data
{
	char a1;
	int a2;
	XnkAddr* a3, * a4, * a5;
	bool succeeded;

	s_join_data(char a1_, int a2_, XnkAddr* a3_, XnkAddr* a4_, XnkAddr* a5_)
	{
		a1 = a1_;
		a2 = a2_;
		a3 = a3_;
		a4 = a4_;
		a5 = a5_;
		succeeded = false;
	}

	bool Join(bool use_network_join_to_remote_squad = false)
	{
		if (use_network_join_to_remote_squad)
			return ((char(__cdecl*)(char, char, char, int, XnkAddr*, XnkAddr*, XnkAddr*))0x47ECF0)(((char(__cdecl*)())0x455320)() == false, a1, true, a2, a3, a5, a4);
		return ((char(__cdecl*)(char, int, XnkAddr*, XnkAddr*, XnkAddr*))0xA7E3C0)(a1, a2, a3, a4, a5);
	}

	s_join_data* Print()
	{
		printf_s("%s | %d | %s | %s | %s\n", a1 ? "true" : "false", a2, a3->String(), a4->String(), a5->String());

		return this;
	}
};

struct s_session_membership
{
	uint8_t m_data[0x1A3F20];

public:
	size_t Size()
	{
		return sizeof(*this);
	}
};
_STATIC_ASSERT(sizeof(s_session_membership) == 0x1A3F20);
struct s_session_parameters
{
	uint8_t m_data[0xB7928];

public:
	size_t Size()
	{
		return sizeof(*this);
	}

	void* requested_remote_join_data_get()
	{
		return (void*)(m_data + 0xB5880);
	}
};
_STATIC_ASSERT(sizeof(s_session_parameters) == 0xB7928);
class c_network_session
{
	uint8_t m_data[0x25BC40];

public:
	size_t Size()
	{
		return sizeof(*this);
	}

	s_session_membership* session_membership_get()
	{
		return (s_session_membership*)(m_data + 0x20);
	}
	s_session_parameters* session_parameters_get()
	{
		return (s_session_parameters*)(m_data + 0x1A3F40);
	}
	long local_state_get()
	{
		return *(long*)(m_data + 0x25B870);
	}
	long managed_session_index_get()
	{
		return *(long*)(m_data + 0x25BBF0);
	}
};
_STATIC_ASSERT(sizeof(c_network_session) == 0x25BC40);
auto& g_network_squad_session = reference_get<c_network_session>(0x19AB848);

enum e_network_session_class
{
	_network_session_class_none,
	_network_session_class_offline,
	_network_session_class_system_link,
	_network_session_class_xbox_live,

	k_network_session_class_count
};

struct s_transport_secure_address
{
	long : 32;
	long : 32;
	long : 32;
	long : 32;
};

struct s_transport_secure_identifier
{
	long : 32;
	long : 32;
	long : 32;
	long : 32;
};

struct s_network_session_remote_session_join_data
{
	/* 0x00 */	long : 32;
	/* 0x04 */	long : 32;
	/* 0x08 */	long : 32;
	/* 0x0C */	long : 32;
	/* 0x10 */	long long join_nonce;
	/* 0x18 */	long transport_platform;
	/* 0x1C */	s_transport_secure_identifier session_id;
	/* 0x2C */	long key[4];
	/* 0x3C */	s_transport_secure_address host_address;
	/* 0x4C */	long session_class;
	/* 0x50 */	long status;
	/* 0x54 */	long __unknown54;

	s_network_session_remote_session_join_data(long __unknown54, long session_class, s_transport_secure_identifier* session_id, s_transport_secure_address* host_address) :
		join_nonce(((long long(__cdecl*)())0x431010)()),
		transport_platform(1),
		session_id(*session_id),
		host_address(*host_address),
		session_class(session_class),
		status(1),
		__unknown54(__unknown54)
	{

	}
};
_STATIC_ASSERT(sizeof(s_network_session_remote_session_join_data) == 0x58);
auto& g_remote_session_join_data = reference_get<s_network_session_remote_session_join_data>(0x2240B98);

struct thread_local_storage
{
	enum e : int
	{
		_simulation_gamestate_entities = 2,
		_main_gamestate_timing,
		_main_render_timing,
		_main_time_globals,
		_preferences,
		_random_math_globals = 13,
		_filo_related,
		_game_globals,
		_players_header,
		_players_globals,
		_game_engine_globals,
		_local_game_engine_globals,
		_game_time,
		_breakable_surface_globals,
		_breakable_surface_set_broken_event,
		_player_mapping,
		_director_globals,
		_director_scripting,
		_hs_thread_deterministic_data,
		_hs_runtime,
		_hs_global_data,
		_hs_distributed_global_data,
		_hs_thread_tracking_data,
		_hs_thread_non_deterministic_data,
		_effect = 41,
		_effect_event,
		_effect_location,
		_effect_counts,
		_effect_geometry_sample,
		_effect_messaging_queue,
		_effect_lightprobes,
		_havok_gamestate,
		_player_control_globals = 50,
		_player_control_globals_deterministic,
		_object_looping_sounds,
		_game_sound_globals,
		_game_sound_scripted_impulses,
		_structure_seam_globals,
		_visibility_active_portals,
		_campaign_metagame,
		_observer_gamestate,
		_observer_globals,
		_rumble_globals,
		_bink_gamestate,
		_c_font_cache_mt_safe = 63,
		_sound_classes,
		_game_allegiance_globals,
		_atmosphere_fog_globals,
		_scenario_soft_surface_globals,
		_game_sound_player_effects_globals,
		_havok_proxies,
		_cinematic_new_globals = 176,
		_cinematic_globals,
		_cinematic_light_globals,
		_physics_constants,
		_recorded_animations,
		_game_save_globals,
		_rasterizer_screen_effects,
		_player_effect_globals,
		_scenario_interpolator_globals,
		_survival_mode_globals,
		_player_training_globals,
		_scenario_kill_trigger_volume_state,
		_deterministic_game_sound_globals,
		_decal_system,
		_decal_counts,
		_decal,
		_decal_messaging_queue,
		_impact_globals,
		_impacts,
		_impact_arrays,
		_object_list_header,
		_list_object,
		_scripted_camera_globals,
		_particles,
		_particle_system,
		_contrail_system,
		_contrail,
		_contrail_location,
		_contrail_profile,
		_particle_location,
		_light_volume_system,
		_light_volume_location,
		_light_volume,
		_beam_system,
		_beam,
		_beam_location,
		_ragdolls = 213,
		_particle_emitter,
		_rasterizer_game_states,
		_hue_saturation_control,
		_scripted_exposure_globals = 218,
		_render_hud_globals,
		_water_interaction_ripples,
		_render_texture_globals,
		_render_game_globals,
		_depth_of_field_globals,
		_cached_object_render_states,
		_particle_emitter_gpu_row,
		_particle_emitter_gpu_1,
		_particle_emitter_gpu_2,
		_beam_gpu,
		_beam_gpu_row,
		_particle_emitter_gpu_3,
		_contrail_gpu_row,
		_contrail_gpu,
		_particle_emitter_gpu_4,
		_light_volume_gpu,
		_light_volume_gpu_row,
		_particle_emitter_gpu_5,
		_rasterizer_implicit_geometry_data,
		_render_object_globals,
		_shield_render_cache_message,
		_chud_persistent_user_data,
		_chud_persistent_global_data,
		_user_widget_0,
		_user_widget_1,
		_user_widget_2,
		_user_widget_3,
		_first_person_orientation_globals,
		_first_person_weapon_globals,
		_cortana_globals,
		_campaign_objectives,
		_object_header,
		_object_globals,
		_objects_memory_pool,
		_object_name_list,
		_object_messaging_queue,
		_collideable_object,
		_damage_globals,
		_noncollideable_object = 258,
		_object_render_data = 261,
		_damage,
		_object_placement,
		_device_groups,
		_object_scripting,
		_object_broadphase,
		_object_early_movers,
		_object_schedule_globals,
		_object_activation_regions,
		_lights,
		_lights_globals,
		_light_data_reference,
		_light_cluster_reference,
		_light_first_data,
		_nondeterministic_render_light_data,
		_widget,
		_recycling_volumes,
		_recycling_group,
		_muffin,
		_leaf_system,
		_antenna,
		_cloth,
		_actor = 327,
		_actor_firing_position,
		_ai_reference_frame,
		_ai_globals,
		_ai_player_state,
		_vocalization_records,
		_vocalization_timers,
		_command_scripts,
		_objectives,
		_task_records,
		_squad,
		_squad_group,
		_swarm,
		_swarm_spawner,
		_spawner_globals,
		_dynamic_firing_points,
		_propref,
		_prop,
		_tracking,
		_joint_state,
		_clump,
		_squad_patrol,
		_flocks,
		_formations,
		_vision_mode,

		k_number_of_tls_members = 353
	} value;

	thread_local_storage(int val)
	{
		value = (e)val;
	}

	template<typename T>
	T* GetDefinition(size_t offset = 0, bool data_array = false)
	{
		if (data_array)
			return (T*)(GetMainTls(4 * value)[0](0x44)(offset));
		return (T*)(GetMainTls(4 * value)[0](offset));
	}
};

struct e_biped_palette
{
	enum e : int
	{
		_mp_masterchief,
		_mp_elite,
		_odst,
		_marine,
		_mp_masterchief_ui,
		_mp_elite_ui,
		_mp_masterchief_mannequin,
		_mp_elite_mannequin,

		k_number_of_biped_palettes
	} value;

	e_biped_palette(int val)
	{
		if (val >= _mp_masterchief && val < k_number_of_biped_palettes)
			value = (e)val;
	}

	const char* GetName()
	{
		const char* names[]{
			"mp_masterchief",
			"mp_elite",
			"odst",
			"marine",
			"mp_masterchief_ui",
			"mp_elite_ui",
			"mp_masterchief_mannequin",
			"mp_elite_mannequin",
		};
		return names[value];
	}
};

struct e_hangar
{
	enum e : int
	{
		_human,
		_covenant,

		k_number_of_hangars
	} value;

	e_hangar(int val)
	{
		if (val >= _human && val < k_number_of_hangars)
			value = (e)val;
	}

	const char* GetName()
	{
		const char* names[]{
			"human",
			"covenant",
		};
		return names[value];
	}
};