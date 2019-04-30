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
	char *cmd = GetCommandLineA();
	int offset = 0;
	if (cmd[offset] == '"')
		while (cmd[++offset] != '"');
	while (cmd[++offset] != ' ');
	return static_cast<std::string>(GetCommandLineA()).c_str();
}

#pragma warning( push )
#pragma warning( disable : 4244)
template <typename T>
void SetMemoryAtOffset(size_t off, T val)
{
	if (Pointer(off).Read<T>() != static_cast<T>(val))
		Pointer(off).Write<T>(val);
}
#pragma warning( pop )

template<typename T>
T *GetStructure(size_t ptr, int itr = 0, int off = 0)
{
	return (T *)((ptr + off) + (itr * sizeof(T)));
}

size_t GetAddress(void *addr, bool base = false)
{
	return base ? (size_t)addr - 0x400000 : (size_t)addr;
}

ConMan PreferenceManager;
const char *PreferenceManagerAppname;

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

	const char *GetName()
	{
		const char *names[] {
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

	const char *GetName()
	{
		const char *names[] {
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

	const char *GetName()
	{
		const char *names[] {
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

	const char *GetName()
	{
		const char *names[] {
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

	const char *GetName()
	{
		const char *names[] {
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

	const char *GetName()
	{
		const char *names[] {
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

	const char *GetName()
	{
		const char *names[] {
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
	const char *GetRegion()
	{
		const char *names[] {
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

	const wchar_t *GetLoadingText()
	{
		const wchar_t *names[] {
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
};

bool g_use_default_system_ui_language = true;
auto g_new_system_ui_language = -1;

struct e_scenario_type
{
	enum : int
	{
		_none = 0,

		_campaign,
		_multiplayer,
		_mainmenu,
		_shared, // not sure

		k_number_of_scenario_types
	} value;

	const char *GetName()
	{
		const char *names[] {
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

	const char *GetName()
	{
		const char *names[] {
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

	const char *GetName()
	{
		const char *names[] {
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

	const char *GetName()
	{
		const char *names[] {
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

	const char *GetName()
	{
		const char *names[] {
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

	const char *GetName()
	{
		const char *names[] {
			"off",
			"team",
			"free for all"
		};
		return names[value];
	}
};

struct s_unit_action_info
{
	const char *Name;
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

	const char *GetName()
	{
		return GetStructure<s_unit_action_info>(0x1947A58, value)->Name;
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

	const char *GetName()
	{
		const char *names[] {
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

	const char *GetName()
	{
		const char *names[] {
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

struct e_network_mode
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

	const char *GetName()
	{
		const char *names[] {
			"_open_to_public",
			"_open_to_friends",
			"_invite_only",
			"_system_link",
			"_offline"
		};
		return names[value];
	}
};

struct e_game_state
{
	enum : int
	{
		_unknown0 = 0,
		_unknown1,
		_screenshots_loader_optional_cache,
		_transport,
		_unknown4,
		_unknown5,
		_unknown6,
		_xoverlapped_memory_pool,
		_random_math_globals,
		_network_game_packets,
		_unknown10,
		_unknown11,
		_unknown12,
		_unknown13,
		_unknown14,
		_input_globals,
		_unknown16,
		_levels,
		_unknown18,
		_unknown19,
		_unknown20,
		_game_state_header,
		_game_time_globals,
		_unknown23,
		_game_allegiance_globals,
		_players_globals,
		_player_control_globals,
		_player_training_globals,
		_game_engine_globals,
		_simulation_globals,
		_structure_seam_globals,
		_physics_globals,
		_unknown32,
		_object_globals,
		_object_early_mover_globals,
		_objects_scripting_globals,
		_object_schedule,
		_object_activation_regions,
		_kill_volumes,
		_unknown39,
		_soft_surface_globals,
		_campaign_metagame_globals,
		_cache1_autosave,
		_unknown43,
		_survival_mode_globals,
		_rasterizer_globals,
		_render_object_globals,
		_unknown47,
		_breakable_surface_set_broken_events,
		_director_globals,
		_observer_globals,
		_depth_of_field_globals,
		_water_interaction_ripples,
		_render_texture_globals,
		_render_hud_globals,
		_scripted_exposure_globals,
		_render_game_globals,
		_decals,
		_effects,
		_unknown59,
		_atmosphere_fog_globals,
		_screen_effect,
		_sound_classes,
		_sound_globals,
		_deterministic_game_sound_globals,
		_object_looping_sounds,
		_game_sound_player_effects_globals,
		_user_interface_controllers,
		_player_effects,
		_unknown69,
		_interface_globals,
		_chud_cortana_effect,
		_unknown72,
		_unknown73,
		_cinematic_globals,
		_unknown75,
		_unknown76,
		_unknown77,
		_hs_globals,
		_recorded_animations,
		_unknown80,
		_unknown81,
		_object_placement_globals,
		_havok_shit,
		_object_broadphase_globals,
		_havok_proxies,
		_unknown86,
		_ai_globals,
		_visibility_active_portals,
		_scenario_interpolator,
		_game_save_globals,
		_unknown91,
		_bink_globals,
		_unknown93,
		_unknown94,

		k_number_of_game_states
	} value;

	const char *GetName()
	{
		const char *names[] {
			"unknown0",
			"unknown1",
			"screenshots loader optional cache",
			"transport",
			"unknown4",
			"unknown5",
			"unknown6",
			"xoverlapped memory pool",
			"random math globals",
			"network game packets",
			"unknown10",
			"unknown11",
			"unknown12",
			"unknown13",
			"unknown14",
			"input globals",
			"unknown16",
			"levels",
			"unknown18",
			"unknown19",
			"unknown20",
			"game state header",
			"game time globals",
			"unknown23",
			"game allegiance globals",
			"players globals",
			"player control globals",
			"player training globals",
			"game engine globals",
			"simulation globals",
			"structure seam globals",
			"physics globals",
			"unknown32",
			"object globals",
			"object early mover globals",
			"objects scripting globals",
			"object schedule",
			"object activation regions",
			"kill volumes",
			"unknown39",
			"soft surface globals",
			"campaign metagame globals",
			"cache1 autosave",
			"unknown43",
			"survival mode globals",
			"rasterizer globals",
			"render object globals",
			"unknown47",
			"breakable surface set broken events",
			"director globals",
			"observer globals",
			"depth of field globals",
			"water interaction ripples",
			"render texture globals",
			"render hud globals",
			"scripted exposure globals",
			"render game globals",
			"decals",
			"effects",
			"unknown59",
			"atmosphere fog globals",
			"screen effect",
			"sound classes",
			"sound globals",
			"deterministic game sound globals",
			"object looping sounds",
			"game sound player effects globals",
			"user interface controllers",
			"player effects",
			"unknown69",
			"interface globals",
			"chud cortana effect",
			"unknown72",
			"unknown73",
			"cinematic globals",
			"unknown75",
			"unknown76",
			"unknown77",
			"hs globals",
			"recorded animations",
			"unknown80",
			"unknown81",
			"object placement globals",
			"havok shit",
			"object broadphase globals",
			"havok proxies",
			"unknown86",
			"ai globals",
			"visibility active portals",
			"scenario interpolator",
			"game save globals",
			"unknown91",
			"bink globals",
			"unknown93",
			"unknown94"
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

	const char *GetName()
	{
		const char *names[] {
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

	const char *GetName()
	{
		const char *names[] {
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

	const char *GetName()
	{
		const char *names[] {
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

	const char *GetName()
	{
		const char *names[] {
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

struct vftable
{
	uint32_t address;

	const char *GetName()
	{
		switch (address)
		{
		case 0x165FC44:
			return "c_draw_string::`vftable'";
		case 0x165FCB0:
			return "c_font_cache_base::`vftable'";
		case 0x165FCCC:
			return "c_font_cache_mt_safe::`vftable'";
		case 0x165FCE8:
			return "c_null_font_cache::`vftable'";
		case 0x166DB68:
			return "c_gui_selected_item::`vftable'";
		case 0x166DB94:
			return "c_gui_saved_screenshot_selected_item::`vftable'";
		case 0x166DBC4:
			return "c_screenshots_loader_optional_cache_callback::`vftable'";
		case 0x1697104:
			return "c_simple_font_draw_string::`vftable'";
		case 0x1699240:
			return "c_simple_font_cache::`vftable'";
		case 0x1699FD4:
			return "c_message::`vftable'";
		case 0x1699FE4:
			return "c_controller_input_message::`vftable'";
		case 0x1699FF4:
			return "c_xenon_message::`vftable'";
		case 0x169A004:
			return "c_load_screen_message::`vftable'";
		case 0x169A018:
			return "c_screen_custom_message::`vftable'";
		case 0x169A028:
			return "c_load_alert_screen_message::`vftable'";
		case 0x169A03C:
			return "c_load_dialog_screen_message::`vftable'";
		case 0x169A050:
			return "c_load_in_progress_screen_message::`vftable'";
		case 0x169A064:
			return "c_load_in_progress_mini_screen_message::`vftable'";
		case 0x169A078:
			return "c_dialog_result_message::`vftable'";
		case 0x169A088:
			return "c_load_spartan_milestone_screen_message::`vftable'";
		case 0x169A09C:
			return "c_load_spartan_rank_screen_message::`vftable'";
		case 0x169A144:
			return "c_chud_draw_string::`vftable'";
		case 0x169A8C4:
			return "c_game_tag_parser::`vftable'";
		case 0x169A8D4:
			return "c_simple_game_tag_parser::`vftable'";
		case 0x169A8E4:
			return "c_magic_string_game_tag_parser::`vftable'";
		case 0x169A9AC:
			return "c_gui_screen_terminal::`vftable'";
		case 0x169AD9C:
			return "c_gui_screen_widget::`vftable'";
		case 0x169AE7C:
			return "c_gui_screen_codeless_widget::`vftable'";
		case 0x169AF9C:
			return "c_gui_screen_scoreboard::`vftable'";
		case 0x169B07C:
			return "c_scoreboard_load_screen_message::`vftable'";
		case 0x169B094:
			return "c_gui_scoreboard_data::`vftable'";
		case 0x169B148:
			return "c_user_interface_allocation::`vftable'";
		case 0x169B1E4:
			return "c_load_boot_betrayer_screen_message::`vftable'";
		case 0x169B1FC:
			return "c_gui_screen_boot_betrayer::`vftable'";
		case 0x169B344:
			return "c_gui_widget::`vftable'";
		case 0x169B3DC:
			return "c_sized_user_interface_text<1024>::`vftable'";
		case 0x169B3F4:
			return "c_gui_sized_text_widget<1024>::`vftable'";
		case 0x169B4A4:
			return "c_sized_user_interface_text<256>::`vftable'";
		case 0x169B4BC:
			return "c_gui_sized_text_widget<256>::`vftable'";
		case 0x169B56C:
			return "c_sized_user_interface_text<48>::`vftable'";
		case 0x169B584:
			return "c_gui_sized_text_widget<48>::`vftable'";
		case 0x169B6A0:
			return "c_load_game_camera_list_screen_message::`vftable'";
		case 0x169B6B4:
			return "c_observer_camera_list_screen::`vftable'";
		case 0x169B794:
			return "c_camera_list_datasource::`vftable'";
		case 0x169CAC8:
			return "c_user_interface_text::`vftable'";
		case 0x169CCAC:
			return "c_gui_carnage_report_loading_screen::`vftable'";
		case 0x169CD8C:
			return "c_load_carnage_report_loading_screen_message::`vftable'";
		case 0x169CDA4:
			return "c_gui_screen_carnage_report::`vftable'";
		case 0x169CE84:
			return "c_metagame_tally_datasource::`vftable'";
		case 0x169D2C8:
			return "c_load_pregame_selection_screen_message::`vftable'";
		case 0x169D2DC:
			return "c_load_pregame_players_selection_screen_message::`vftable'";
		case 0x169D334:
			return "c_gui_custom_bitmap_widget::`vftable'";
		case 0x169D65C:
			return "c_http_stored_buffer_downloader<4096>::`vftable'";
		case 0x169DA04:
			return "c_gui_data::`vftable'";
		case 0x169DA74:
			return "c_gui_data_array::`vftable'";
		case 0x169DAE4:
			return "c_gui_data_array_test::`vftable'";
		case 0x169DB54:
			return "c_gui_ordered_data::`vftable'";
		case 0x169DBCC:
			return "c_gui_tag_datasource::`vftable'";
		case 0x169DDD4:
			return "c_gui_alert_screen_widget::`vftable'";
		case 0x169DEF4:
			return "c_gui_dialog_screen_widget::`vftable'";
		case 0x169DFD4:
			return "c_dialog_screen_widget_dialog_items_datasource::`vftable'";
		case 0x169E23C:
			return "c_gui_map_selected_item::`vftable'";
		case 0x169E26C:
			return "c_gui_map_category_datasource::`vftable'";
		case 0x169E2E4:
			return "c_gui_map_subitem_selectable_item_datasource::`vftable'";
		case 0x169E3F4:
			return "c_gui_difficulty_selected_item::`vftable'";
		case 0x169E424:
			return "c_gui_difficulty_category_datasource::`vftable'";
		case 0x169E4DC:
			return "c_gui_game_variant_selected_item::`vftable'";
		case 0x169E50C:
			return "c_gui_game_variant_category_datasource::`vftable'";
		case 0x169E584:
			return "c_gui_game_variant_subitem_selectable_item_datasource::`vftable'";
		case 0x169E6A4:
			return "c_gui_saved_film_selected_item::`vftable'";
		case 0x169E6D4:
			return "c_gui_saved_film_category_datasource::`vftable'";
		case 0x169E74C:
			return "c_gui_saved_film_subitem_datasource::`vftable'";
		case 0x169E8AC:
			return "c_game_info_datasource::`vftable'";
		case 0x169E93C:
			return "c_gui_game_info_screen::`vftable'";
		case 0x169EA1C:
			return "c_gui_game_browser::`vftable'";
		case 0x169EB0C:
			return "c_available_games_info_datasource::`vftable'";
		case 0x169EC2C:
			return "c_load_start_menu_pane_screen_message::`vftable'";
		case 0x169EC44:
			return "c_start_menu_screen_widget::`vftable'";
		case 0x169ED24:
			return "c_load_start_menu_screen_message::`vftable'";
		case 0x169ED3C:
			return "c_start_menu_screen_widget_sidebar_items_datasource::`vftable'";
		case 0x169EDF4:
			return "c_gui_data_proxy::`vftable'";
		case 0x169EE6C:
			return "c_sandbox_budget_summary_screen_widget::`vftable'";
		case 0x169EF4C:
			return "c_sandbox_object_menu_screen_widget::`vftable'";
		case 0x169F02C:
			return "c_gui_placeable_object_datasource::`vftable'";
		case 0x169F0A4:
			return "c_gui_budget_range_datasource::`vftable'";
		case 0x169F11C:
			return "c_load_object_creation_screen_message::`vftable'";
		case 0x169F130:
			return "c_load_object_property_panel_screen_message::`vftable'";
		case 0x169F144:
			return "c_load_budget_screen_message::`vftable'";
		case 0x169F15C:
			return "c_sandbox_budget_items_datasource::`vftable'";
		case 0x169F214:
			return "c_sandbox_object_properties_screen_widget::`vftable'";
		case 0x169F2F4:
			return "c_gui_property_value_datasource::`vftable'";
		case 0x169F36C:
			return "c_sandbox_object_properties_items_datasource::`vftable'";
		case 0x169F424:
			return "c_saved_film_control_pad::`vftable'";
		case 0x169F59C:
			return "c_saved_film_take_screenshot::`vftable'";
		case 0x169F7A4:
			return "c_saved_film_snippet_screen::`vftable'";
		case 0x169F8C4:
			return "c_error_dialog_screen_widget::`vftable'";
		case 0x169F9A4:
			return "c_error_dialog_ok_screen_widget::`vftable'";
		case 0x169FACC:
			return "c_gui_screen_alpha_motd::`vftable'";
		case 0x169FBAC:
			return "c_load_alpha_motd_screen_message::`vftable'";
		case 0x169FC10:
			return "c_http_stored_buffer_downloader<4665>::`vftable'";
		case 0x169FC1C:
			return "c_main_menu_screen_widget::`vftable'";
		case 0x169FCFC:
			return "c_load_campaign_select_difficulty_screen_message::`vftable'";
		case 0x169FD7C:
			return "c_start_menu_game_campaign::`vftable'";
		case 0x169FF1C:
			return "c_start_menu_game_multiplayer::`vftable'";
		case 0x16A008C:
			return "c_start_menu_game_editor::`vftable'";
		case 0x16A0174:
			return "c_gui_gametype_category_datasource::`vftable'";
		case 0x16A01E8:
			return "c_load_legal_screen_message::`vftable'";
		case 0x16A02C4:
			return "c_start_menu_game_saved_film::`vftable'";
		case 0x16A03E8:
			return "c_http_stored_buffer_downloader<2721>::`vftable'";
		case 0x16A03F0:
			return "c_http_stored_buffer_downloader<61440>::`vftable'";
		case 0x16A03FC:
			return "c_start_menu_headquarters::`vftable'";
		case 0x16A056C:
			return "c_gui_start_menu_hq_service_record_pane::`vftable'";
		case 0x16A0654:
			return "c_gui_start_menu_hq_service_record::`vftable'";
		case 0x16A073C:
			return "c_gui_start_menu_hq_service_record_insignia_datasource::`vftable'";
		case 0x16A0844:
			return "c_gui_start_menu_hq_service_record_file_share::`vftable'";
		case 0x16A0928:
			return "c_load_file_share_choose_category_screen_message::`vftable'";
		case 0x16A093C:
			return "c_load_file_share_choose_item_screen_message::`vftable'";
		case 0x16A0950:
			return "c_load_file_share_item_selected_screen_message::`vftable'";
		case 0x16A0964:
			return "c_load_transfers_item_selected_screen_message::`vftable'";
		case 0x16A097C:
			return "c_gui_file_share_slots_datasource::`vftable'";
		case 0x16A0ACC:
			return "c_gui_start_menu_hq_service_record_file_share_choose_category::`vftable'";
		case 0x16A0BEC:
			return "c_gui_start_menu_hq_service_record_file_share_choose_item::`vftable'";
		case 0x16A0CCC:
			return "c_gui_content_item_datasource::`vftable'";
		case 0x16A0E3C:
			return "c_gui_start_menu_hq_service_record_file_share_item_selected::`vftable'";
		case 0x16A0F1C:
			return "c_load_screenshots_file_share_previewer_screen_message::`vftable'";
		case 0x16A0F34:
			return "c_gui_file_share_selected_item_datasource::`vftable'";
		case 0x16A10B4:
			return "c_gui_start_menu_hq_screenshots::`vftable'";
		case 0x16A1198:
			return "c_load_screenshots_viewer_screen_message::`vftable'";
		case 0x16A11AC:
			return "c_load_hq_screenshots_options_screen_message::`vftable'";
		case 0x16A11C4:
			return "c_player_screenshots_datasource::`vftable'";
		case 0x16A133C:
			return "c_gui_start_menu_hq_screenshots_options::`vftable'";
		case 0x16A14F4:
			return "c_screenshots_screen_widget_base::`vftable'";
		case 0x16A15DC:
			return "c_screenshots_viewer_screen_widget::`vftable'";
		case 0x16A16C4:
			return "c_http_stored_buffer_downloader<317440>::`vftable'";
		case 0x16A16CC:
			return "c_screenshots_file_share_previewer_screen_widget::`vftable'";
		case 0x16A1824:
			return "c_gui_start_menu_hq_transfers::`vftable'";
		case 0x16A190C:
			return "c_active_transfers_datasource::`vftable'";
		case 0x16A19C4:
			return "c_gui_start_menu_hq_transfers_item_selected::`vftable'";
		case 0x16A1AA4:
			return "c_gui_transfers_selected_item_datasource::`vftable'";
		case 0x16A1B5C:
			return "c_start_menu_settings::`vftable'";
		case 0x16A1C84:
			return "c_start_menu_settings_controls::`vftable'";
		case 0x16A1D6C:
			return "c_settings_controls_sidebar_items_datasource::`vftable'";
		case 0x16A1E94:
			return "c_start_menu_settings_controls_button::`vftable'";
		case 0x16A1FBC:
			return "c_start_menu_settings_controls_thumbstick::`vftable'";
		case 0x16A20E4:
			return "c_start_menu_settings_appearance::`vftable'";
		case 0x16A22CC:
			return "c_start_menu_settings_appearance_model::`vftable'";
		case 0x16A23B4:
			return "c_model_customization_selections_datasource::`vftable'";
		case 0x16A242C:
			return "c_settings_appearance_model_sidebar_items_datasource::`vftable'";
		case 0x16A2554:
			return "c_start_menu_settings_appearance_colors::`vftable'";
		case 0x16A263C:
			return "c_color_swatch_focus_list_item_widget::`vftable'";
		case 0x16A27B4:
			return "c_start_menu_settings_camera::`vftable'";
		case 0x16A289C:
			return "c_settings_camera_sidebar_items_datasource::`vftable'";
		case 0x16A298C:
			return "c_start_menu_settings_display::`vftable'";
		case 0x16A2A74:
			return "c_settings_display_sidebar_items_datasource::`vftable'";
		case 0x16A2B64:
			return "c_start_menu_settings_film_autosave::`vftable'";
		case 0x16A2C4C:
			return "c_settings_film_autosave_sidebar_items_datasource::`vftable'";
		case 0x16A2D4C:
			return "c_gui_screen_in_progress::`vftable'";
		case 0x16A2E6C:
			return "c_gui_spartan_milestone::`vftable'";
		case 0x16A2F8C:
			return "c_gui_spartan_rank::`vftable'";
		case 0x16A30B4:
			return "c_gui_screen_campaign_select_difficulty::`vftable'";
		case 0x16A31DC:
			return "c_gui_screen_campaign_select_level::`vftable'";
		case 0x16A32BC:
			return "c_gui_level_selected_item::`vftable'";
		case 0x16A32EC:
			return "c_gui_survival_level_datasource::`vftable'";
		case 0x16A3434:
			return "c_gui_screen_campaign_select_scoring::`vftable'";
		case 0x16A35DC:
			return "c_gui_screen_campaign_select_skulls::`vftable'";
		case 0x16A36BC:
			return "c_gui_primary_skulls_data::`vftable'";
		case 0x16A3734:
			return "c_gui_secondary_skulls_data::`vftable'";
		case 0x16A37F0:
			return "c_gui_screen_pregame_lobby_campaign::`vftable'";
		case 0x16A38F4:
			return "c_load_campaign_select_level_screen_message::`vftable'";
		case 0x16A39DC:
			return "c_gui_screen_pregame_lobby_survival::`vftable'";
		case 0x16A3B24:
			return "c_gui_screen_pregame_lobby_multiplayer::`vftable'";
		case 0x16A3CCC:
			return "c_http_stored_buffer_downloader<2465>::`vftable'";
		case 0x16A3CD4:
			return "c_http_stored_buffer_downloader<102400>::`vftable'";
		case 0x16A3CDC:
			return "c_gui_screen_pregame_lobby_matchmaking::`vftable'";
		case 0x16A3EF4:
			return "c_gui_screen_pregame_lobby_mapeditor::`vftable'";
		case 0x16A4064:
			return "c_gui_screen_pregame_lobby_theater::`vftable'";
		case 0x16A4234:
			return "c_gui_screen_pregame_switch_lobby::`vftable'";
		case 0x16A435C:
			return "c_gui_screen_pregame_selection::`vftable'";
		case 0x16A453C:
			return "c_gui_screen_matchmaking_advanced_options::`vftable'";
		case 0x16A470C:
			return "c_gui_screen_postgame_lobby::`vftable'";
		case 0x16A4870:
			return "c_load_player_select_screen_message::`vftable'";
		case 0x16A4884:
			return "c_gui_player_select_screen_widget::`vftable'";
		case 0x16A4964:
			return "c_player_select_actions_datasource::`vftable'";
		case 0x16A49DC:
			return "c_player_select_medals_datasource::`vftable'";
		case 0x16A4D2C:
			return "c_gui_screen_maximum_party_size::`vftable'";
		case 0x16A4E4C:
			return "c_load_game_details_screen_message::`vftable'";
		case 0x16A4E64:
			return "c_gui_game_details::`vftable'";
		case 0x16A4F44:
			return "c_specific_game_info_datasource::`vftable'";
		case 0x16A5004:
			return "c_load_game_options_screen_message::`vftable'";
		case 0x16A501C:
			return "c_gui_screen_game_options::`vftable'";
		case 0x16A50FC:
			return "c_game_options_parameter_datasource::`vftable'";
		case 0x16A5174:
			return "c_game_options_category_datasource::`vftable'";
		case 0x16A52EC:
			return "c_gui_screen_alpha_legal::`vftable'";
		case 0x16A540C:
			return "c_gui_screen_alpha_locked_down::`vftable'";
		case 0x16A5534:
			return "c_gui_screen_forge_legal::`vftable'";
		case 0x16A5654:
			return "c_gui_screen_matchmaking_searching::`vftable'";
		case 0x16A591C:
			return "c_gui_screen_matchmaking_match_found::`vftable'";
		case 0x16A5E34:
			return "c_motd_popup_screen_widget::`vftable'";
		case 0x16A5F6C:
			return "c_gui_group_widget::`vftable'";
		case 0x16A600C:
			return "c_gui_button_key_widget::`vftable'";
		case 0x16A60EC:
			return "c_gui_list_widget::`vftable'";
		case 0x16A61CC:
			return "c_gui_bitmap_widget::`vftable'";
		case 0x16A62F4:
			return "c_gui_list_item_widget::`vftable'";
		case 0x16A63D4:
			return "c_gui_text_widget::`vftable'";
		case 0x16A6564:
			return "c_gui_model_widget::`vftable'";
		case 0x16A6684:
			return "c_gui_game_results_data::`vftable'";
		case 0x16A66FC:
			return "c_gui_game_results_team_data::`vftable'";
		case 0x16A6774:
			return "c_gui_top_medals_data::`vftable'";
		case 0x16A685C:
			return "c_gui_campaign_results_data::`vftable'";
		case 0x16A6910:
			return "c_html_comment_game_tag_parser::`vftable'";
		case 0x16A6920:
			return "c_html_line_break_game_tag_parser::`vftable'";
		case 0x16A6930:
			return "c_html_paragraph_game_tag_parser::`vftable'";
		case 0x16A6940:
			return "c_html_paragraph_close_game_tag_parser::`vftable'";
		case 0x16A6950:
			return "c_html_div_game_tag_parser::`vftable'";
		case 0x16A6960:
			return "c_html_div_close_game_tag_parser::`vftable'";
		case 0x16A6970:
			return "c_html_font_game_tag_parser::`vftable'";
		case 0x16A6980:
			return "c_html_font_close_game_tag_parser::`vftable'";
		case 0x16A6990:
			return "c_color_game_tag_parser::`vftable'";
		case 0x16A69A0:
			return "c_color_close_game_tag_parser::`vftable'";
		case 0x16A6BE0:
			return "c_start_menu_custom_message::`vftable'";
		case 0x16A6BF4:
			return "c_start_menu_pane_screen_widget::`vftable'";
		case 0x16A6D9C:
			return "c_gui_level_category_datasource::`vftable'";
		case 0x16A6E14:
			return "c_gui_level_subitem_selectable_item_datasource::`vftable'";
		case 0x16A6ECC:
			return "c_gui_screen_campaign_settings::`vftable'";
		case 0x16A6FF4:
			return "c_gui_screen_pregame_lobby::`vftable'";
		case 0x16A7384:
			return "c_gui_network_mode_selected_item::`vftable'";
		case 0x16A73B4:
			return "c_gui_network_mode_category_datasource::`vftable'";
		case 0x16A742C:
			return "c_gui_network_mode_subitem_selectable_item_datasource::`vftable'";
		case 0x16A74E4:
			return "c_gui_hopper_selected_item::`vftable'";
		case 0x16A7514:
			return "c_gui_hopper_category_datasource::`vftable'";
		case 0x16A758C:
			return "c_gui_hopper_subitem_selectable_item_datasource::`vftable'";
		case 0x16A7644:
			return "c_gui_roster_data::`vftable'";
		case 0x16A76C4:
			return "c_gui_active_roster_data::`vftable'";
		case 0x16A7744:
			return "c_gui_static_roster_data::`vftable'";
		case 0x16A7814:
			return "c_gui_roster_list_widget::`vftable'";
		default:
			return (static_cast<std::stringstream const&>(std::stringstream() << "0x" << std::hex << address)).str().c_str();
		}
	}
};

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

	const char *GetName()
	{
		const char *names[] {
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

	const char *GetName()
	{
		const char *names[] {
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
		char *Data;
		char **Strings;

		StringIDCache();
		~StringIDCache();

		static StringIDCache Instance;

		bool Load(const std::string &path);
		char *GetString(const uint32_t stringID);
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

	bool StringIDCache::Load(const std::string &path)
	{
		std::ifstream stream;
		stream.open(path, std::ios::binary);

		if (!stream.good())
			return false;

		stream.read((char *)&Header, sizeof(StringIDCacheHeader));

		Data = new char[Header.StringDataSize + 1];
		Strings = new char *[Header.StringCount];

		auto *stringOffsets = new int32_t[Header.StringCount];
		stream.read((char *)stringOffsets, sizeof(int32_t) * Header.StringCount);

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

	char *StringIDCache::GetString(const uint32_t StringID)
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
}
#pragma warning( pop )

struct string_id
{
	uint32_t value;

	const char *GetName()
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

	char *String()
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
	e_scenario_type ScenarioType;
	e_game_simulation GameSimulation;
	int16_t FrameLimit;
	int32_t GameInstance;
	int16_t wordC[2];
	int32_t RandomSeed;
	int32_t Language;
	int32_t DeterminismVersion;
	int32_t CampaignId;
	int32_t MapId;
	char ScenarioPath[260];
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
		uint8_t unknown8[0x18];
		char PlayerProperties[0x1620]; // Blam::Players::PlayerProperties
	} InitialParticipantsArray[16];
} game_options;
static_assert(sizeof(s_game_options) == 0x24B48u, "game_options wrong size");

struct s_progression
{
	unsigned char unknown[0x80];
};

struct game_globals
{
	unsigned char unknown0;
	unsigned char unknown1;
	unsigned char unknown2;
	unsigned char unknown3;
	unsigned long structure_bsp_index;
	unsigned long unknown8;
	unsigned long unknownC;

	s_game_options game_options;

	unsigned long unknown24B58; // mapname string_id?

	s_progression progression;
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
	unsigned long end_match_wait_time;
	unsigned long PrimarySkullFlags;
	unsigned long SecondarySkullFlags;
	unsigned char unknown24BF4[4];
	struct {
		struct {
			unsigned char unknown[32];
		} unknown[16];
	} unknown24BF8[3];
	bool cinematic_is_playing;
	unsigned char unknown251F9[15];
};
static_assert(sizeof(game_globals) == 0x25208u, "game_globals wrong size");
//static_assert(sizeof(game_globals) == 0x1A908, "game_globals wrong size");

struct s_lobby_data
{
	e_lobby_type lobby_type;
	uint8_t *data;
};

struct s_saved_game_data
{
	struct s_campaign_data
	{
		uint8_t unknown0;
		uint8_t unknown1;
		uint8_t unknown2;
		uint8_t unknown3;
		uint32_t campaign_id;
		uint32_t map_id;
		uint16_t campaign_insertion_point;
		uint16_t unknownE;
		uint32_t campaign_difficulty_level;
		uint32_t campaign_metagame_scoring_options;
		uint32_t campaign_skulls_primary;
		uint32_t campaign_skulls_secondary;
		char players_armaments[0x78];
		s_progression progression;
		char unknown118[0x80];
	};
	struct s_matchmaking_data
	{
		uint8_t unknown0;
		uint8_t unknown1;
		uint16_t unknown2;
		uint8_t unknown4;
		uint8_t unknown5;
		uint16_t matchmaking_hopper;
	};
	struct s_multiplayer_data
	{
		uint8_t unknown0;
		uint8_t unknown1;
		uint8_t unknown2;
		uint8_t unknown3;
		uint8_t game_variant[0x264];
		uint8_t unknown4[0x210];
		uint8_t map_variant[0xE090];
		uint8_t unknownE508[0x210];
	};
	struct s_mapeditor_data
	{
		uint8_t unknown0;
		uint8_t unknown1;
		uint8_t unknown2;
		uint8_t unknown3;
		uint32_t unknown4;
		uint8_t map_variant[0xE090];
		uint8_t unknownE098[0x210];
	};
	struct s_theater_data
	{
		uint8_t unknown0;
		uint8_t unknown1;
		uint8_t unknown2;
		uint8_t unknown3;
		uint8_t unknown4[0x10];
		struct s_saved_film_description
		{
			uint32_t campaign_id;
			uint32_t map_id;
			uint8_t unknown8[8];
			uint32_t unknown10;
			uint16_t unknown14;
			uint8_t unknown16[0x1FE];
			uint16_t unknown214;
			uint8_t unknown216[0x42];
			uint8_t unknown258[0xBA];
			uint32_t unknown316;
			uint32_t unknown31A;
		} saved_film_description;
		s_game_options game_options;
		uint8_t unknown24E78[8];
	};

	s_campaign_data campaign_data;
	s_campaign_data survival_data;
	s_matchmaking_data matchmaking_data;
	s_multiplayer_data multiplayer_data;
	s_mapeditor_data mapeditor_data;
	s_theater_data theater_data;

} gamemode_data;

struct s_save_data
{
	const wchar_t *path;
	DWORD size;
	LPVOID buffer;
};

std::vector<s_save_data> save_data = {
	{ L"mods\\saves\\lobby\\campaign.dat", sizeof(gamemode_data.campaign_data), &gamemode_data.campaign_data },
	{ L"mods\\saves\\lobby\\matchmaking.dat", sizeof(gamemode_data.matchmaking_data), &gamemode_data.matchmaking_data },
	{ L"mods\\saves\\lobby\\multiplayer.dat", sizeof(gamemode_data.multiplayer_data), &gamemode_data.multiplayer_data },
	{ L"mods\\saves\\lobby\\mapeditor.dat", sizeof(gamemode_data.mapeditor_data), &gamemode_data.mapeditor_data },
	{ L"mods\\saves\\lobby\\theater.dat", sizeof(gamemode_data.theater_data), &gamemode_data.theater_data },
	{ L"mods\\saves\\lobby\\survival.dat", sizeof(gamemode_data.survival_data), &gamemode_data.survival_data },
	{ L"mods\\saves\\lobbies.dat", sizeof(gamemode_data), &gamemode_data }
};

struct lobby
{
	const char *name;
	s_lobby_data *get(s_lobby_data *a1)
	{
		memmove(&a1->data, save_data[a1->lobby_type.value].buffer, save_data[a1->lobby_type.value].size);
		return a1;
	}
	void set(s_lobby_data *a1)
	{
		printf_s("Saving %s: %s\n", name, a1->lobby_type.GetName());
		memmove(save_data[a1->lobby_type.value].buffer, &a1->data, save_data[a1->lobby_type.value].size);
	}
};

struct gamemode
{
	const char *name;
	s_saved_game_data *get()
	{
		memmove(&gamemode_data, save_data[6].buffer, save_data[6].size);
		return &gamemode_data;
	}
	void set(s_saved_game_data *a1)
	{
		printf_s("Saving %s\n", name);
		memmove(save_data[6].buffer, &a1, save_data[6].size);
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
	const char *ToString()
	{
		return (std::to_string(width) + "x" + std::to_string(height)).c_str();
	}
};

struct screen_resolution
{
	int width, height;
	const char *name;
	bool locked;
	void get(int *a1, int *a2)
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
	void set(s_screen_resolution *a1)
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
	const char *name;
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
	const char *name;
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
	const char *name;
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
	const char *name;
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
	const char *name;
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
	const char *name;
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
	const char *name;
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
	const char *name;
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
	const char *name;
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

uint8_t *Transport()
{
	return reinterpret_cast<uint8_t*>(0x199FA28);
}

auto game_globals_get = []() { return (game_globals *)GetMainTls(0x3C)[0]; };
auto game_options_get = []() { return &game_globals_get()->game_options; };
auto scenario_type_get = []() { return game_options_get()->ScenarioType.value; };
auto game_progression_get = []() { return game_globals_get()->progression; };

struct s_levels
{
	uint8_t unknown0[2];
	uint16_t campaign_id;
	uint32_t map_id;
	wchar_t map_name[32];
	wchar_t map_description[128];
	char scenario_path[256];
	char scenario_image_path[256];
	uint32_t unknown348;
	uint32_t unknown34C;
	uint16_t unknown34E;
	uint8_t game_type[14];
};
static_assert(sizeof(s_levels) == 0x360, "s_levels wrong size");

struct s_campaigns_data
{
	uint8_t unknown0[2];
	uint16_t flags;
	uint32_t campaign_id;
	wchar_t unknown8[64];
	wchar_t unknown88[128];
	uint32_t unknown188[64];
};

struct s_levels_unknown
{
	int *campaigns;
	int *campaign_levels; // s_levels
	int *campaign_insertions;
	int *multiplayer_levels; // s_levels
	struct s_levels_unknown_offset_10_of_size_360
	{
		uint8_t unknown0[2];
		uint16_t maybe_campaign_id;
		uint32_t map_id;
		uint8_t unknown8[320];
		char scenario_path[256];
		uint8_t unknown258[280];
	} unknown10;
	static_assert(sizeof(s_levels_unknown_offset_10_of_size_360) == 0x360, "s_levels_unknown_offset_10 wrong size");
	uint32_t unknown370;
	uint8_t unknown374[1698];
	uint8_t unknownA16;
	uint8_t unknownA17;
	uint8_t unknownA18[4];
};
static_assert(sizeof(s_levels_unknown) == 0xA1C, "s_levels_unknown wrong size");

struct s_game_state_header
{
	uint32_t *Sessions[3];
	uint8_t unknownC[252];
	char build_version[32];
	uint32_t unknown108;
	uint8_t unknown10C[4];
	s_game_options game_options;
	uint8_t scenario_game_state[24];
	uint8_t unknown24C90[64];
};

struct s_runtime_state_allocation
{
	bool *initialized;
	bool *release_memory;
	void **data;
	uint32_t *datum_size;
	uint32_t *size;
	bool *valid;
};

struct s_file_reference
{
	uint32_t header_type;
	uint16_t flags;
	int16_t unknown6;
	char path[256];
	HANDLE file_handle;
	uint32_t file_pointer;

	s_file_reference* __cdecl initialize_header(uint16_t a2)
	{
		memset(this, 0, 0x110u);
		header_type = 'filo';
		unknown6 = a2;

		return this;
	}
	s_file_reference* __cdecl initialize(uint16_t a2)
	{
		initialize_header(a2);
		file_handle = (HANDLE)-1;

		return this;
	}
	bool close()
	{
		bool result;
		if (CloseHandle(file_handle))
		{
			file_handle = (HANDLE)-1;
			file_pointer = 0;
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
		if (ReadFile(file_handle, lpBuffer, v6, &nNumberOfBytesToRead, 0))
		{
			if (nNumberOfBytesToRead == v4)
				result = true;
			else
				SetLastError(0x26u);
		}
		file_pointer += nNumberOfBytesToRead;
		if (!result)
			sub_5294F0("file_read", this, 0, a3);

		return result;
	}
	bool set_position(LONG lDistanceToMove, char a3, void(__cdecl* sub_5294F0)(const char*, s_file_reference*, s_file_reference*, char))
	{
		if (file_pointer == lDistanceToMove)
			return true;
		void* v4 = file_handle;
		LONG DistanceToMoveHigh = 0;
		auto v5 = SetFilePointer(v4, lDistanceToMove, &DistanceToMoveHigh, 0);
		bool file_pointer_is_valid = v5 != -1;
		file_pointer = v5;
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
		if (WriteFile(file_handle, lpBuffer, v5, &nNumberOfBytesToWrite, 0))
		{
			result = 0;
			if (nNumberOfBytesToWrite == v3)
				result = true;
		}
		file_pointer += nNumberOfBytesToWrite;
		if (!result)
			sub_5294F0("file_write", this, 0, 0);
		return result;
	}
	int __cdecl get_eof(void(__cdecl* sub_5294F0)(const char*, s_file_reference*, s_file_reference*, char))
	{
		DWORD result = GetFileSize(file_handle, 0);
		if (!result)
			sub_5294F0("file_get_eof", this, 0, 0);
		return result;
	}

	void Print(const char* calling_function)
	{
		printf_s("type: %s, flags: %d, unk6: %d, handle: 0x%p, pointer: 0x%08X, path: %s, %s\n", (header_type == 'filo' ? "'filo'" : "'????'"), flags, unknown6, file_handle, file_pointer, path, calling_function);
	}
};
auto global_tag_cache_filo = GetStructure<s_file_reference>(0x22AE3A8);

struct s_map_data
{
	int32_t header_signature;
	int32_t version;
	int32_t cache_size;
	uint8_t unknownC[16];
	const char path[256];
	uint8_t build_version[32];
	int16_t scenario_type;
	uint8_t unknown13E[4];
	uint8_t unknown142;
	uint8_t unknown143;
	struct _FILETIME file_time;
	uint8_t unknown164[28];
	uint8_t unknown180;
	uint8_t unknown181;
	uint8_t unknown182;
	uint8_t unknown183;
	FILETIME unknown184[6];
	uint8_t unknown1B4[8];
	const char map_name[128];
	uint8_t unknown224[164];
	int32_t map_minor_version;
	uint8_t unknown2CC[84];
	uint8_t content_header[20];
	const char description[256];
	uint8_t unknown434[4];
	int32_t unknown438;
	uint8_t unknown43C[40];
	uint8_t unknown464[9000];
	uint32_t unknown278C[17][45];
	uint32_t unknown3380;
	uint32_t unknown3384;
	uint32_t unknown3388;
	int32_t footer_signature;
};
auto map_data = GetStructure<s_map_data>(0x22AB018);

struct s_unit_action
{
	e_unit_action Index;
	unsigned char Unknown4[0x44];
};

struct s_content_catalogue
{
	uint32_t storage_device_id;
	int *data;
	uint8_t unknown8[8];
	struct s_size_240
	{
		uint8_t unknown0[576];
	} unknown10;
	uint8_t unknown250[6];
	uint16_t unknown256;
	uint8_t unknown258[12];
	uint32_t unknown264;
	uint8_t unknown268[14];
	uint16_t unknown276;
	uint8_t unknown278[40];
	uint32_t unknown2A0;
	volatile LONG *unknown2A4;
	uint32_t long_flags2A8;
	uint8_t unknown2AC[4];
};

struct s_storage_device
{
	s_content_catalogue *content_catalogue_ptr;
	uint8_t unknown4[44];
};

#pragma pack(push, 1)
struct s_player_profile_offset0_offset8
{
	uint8_t unknown0[12];
	uint32_t user_index;
	uint8_t unknownC[492];
	uint32_t camera_inversion;
	uint32_t camera_panning;
	uint32_t camera_look_sensitivity;
	uint32_t camera_speed;
	uint32_t camera_thrust;
	uint32_t campaign_difficulty_level;
	uint8_t unknown214[4];
	uint8_t unknown218[2][32];
	uint8_t unknown258[16];
	uint32_t user_aquired_primary_skulls_dword_flags;
	uint32_t user_aquired_secondary_skulls_dword_flags;
	uint8_t unknown270[560];
	uint8_t unknown4A0[1616];
	uint8_t unknownAF0[20];
	uint32_t unknownB04;
	uint32_t unknownB08;
	uint16_t unknownB0A;
	uint16_t unknownB0C;
};

struct s_player_profile_offset0
{
	uint8_t Flags;
	uint8_t Unknown1;
	uint16_t LocalPlayerIndex;
	uint8_t Unknown4[4];
	s_player_profile_offset0_offset8 *Unknown8;
	uint8_t UnknownC[1286];
};

struct s_player_profile
{
	s_player_profile_offset0 unkown0;
	uint8_t unkown512[3822];
	wchar_t name[16];
	uint8_t unkown544[16];
	uint32_t achievements[2];
	uint8_t unkown55C[16];
};
#pragma pack(pop)

#pragma pack(push, 1)
struct s_overlapped_task_vftable
{
	int(__cdecl *vftable0)(void *, char);
	e_session_overlapped_task_type(__cdecl *type)(uint32_t *, char);
	void(__cdecl *vftable2)(uint32_t);
	void(__cdecl *vftable3)(uint32_t);
	void(__cdecl *vftable4)(uint32_t *, uint32_t);
	void(__cdecl *vftable5)(uint32_t *, uint32_t, uint32_t, uint32_t);
	void(__cdecl *vftable6)(uint32_t *);
	void(__cdecl *vftable7)(uint16_t *);
	void(__cdecl *vftable8)(uint32_t, uint32_t, uint32_t);
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
	uint32_t *Handle;
	uint32_t Unknown4C;
	uint64_t XUid[32];
};
struct c_managed_session
{
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
};
#pragma pack(pop)
struct s_game_state_definition
{
	void *initialize;
	void *dispose;
	void *initialize_for_new_map;
	void *dispose_from_old_map;
	void *prepare_to_switch_structure_bsp;
	void *reconnect_to_structure_bsp;
	void *disconnect_from_structure_bsp;
	void *switch_structure_bsp;
	void *unknown9;
	void *unknown10;
	void *initialize_for_new_structure_bsp;
	void *dispose_from_old_non_bsp_zone_set;

	size_t GetArrayStartAddress(bool base = false)
	{
		return GetAddress((void *)0x1655950, base);
	}

	size_t GetInitialize(bool base = false)
	{
		return GetAddress(initialize, base);
	}
	size_t GetDispose(bool base = false)
	{
		return GetAddress(dispose, base);
	}
	size_t GetInitializeForNewMap(bool base = false)
	{
		return GetAddress(initialize_for_new_map, base);
	}
	size_t GetDisposeFromOldMap(bool base = false)
	{
		return GetAddress(dispose_from_old_map, base);
	}

	size_t GetPrepareToSwitchStructureBsp(bool base = false)
	{
		return GetAddress(prepare_to_switch_structure_bsp, base);
	}
	size_t GetReconnectToStructureBsp(bool base = false)
	{
		return GetAddress(reconnect_to_structure_bsp, base);
	}
	size_t GetDisconnectFromStructureBsp(bool base = false)
	{
		return GetAddress(disconnect_from_structure_bsp, base);
	}
	size_t GetSwitchStructureBsp(bool base = false)
	{
		return GetAddress(switch_structure_bsp, base);
	}

	size_t GetUnknown9(bool base = false)
	{
		return GetAddress(unknown9, base);
	}
	size_t GetUnknown10(bool base = false)
	{
		return GetAddress(unknown10, base);
	}
	size_t GetInitializeForNewStructureBsp(bool base = false)
	{
		return GetAddress(initialize_for_new_structure_bsp, base);
	}
	size_t GetDisposeFromOldnonBspZoneSet(bool base = false)
	{
		return GetAddress(dispose_from_old_non_bsp_zone_set, base);
	}
};

struct s_initial_network_values
{
	int unknown0;
	int unknown4;
	int unknown8;
	float unknownC;
	int unknown10;
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
	int disband_timeout;
	int unknown24C;
	int unknown250;
	int unknown254;
	int unknown258;
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
	int grief_timer_timeout;
	int unknown2A4;
	int unknown2A8;
	__int8 unknown2AC;
	int unknown2B0;
	int unknown2B4;
	int simulation_abort_as_host_timeout;
	int simulation_abort_as_peer_timeout;
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
	int unknown370;
	float unknown374;
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
	int lobby_coop_max_player_count;
	int lobby_mapeditor_max_player_count;
	int unknown3CC;
	int machine_file_refresh_timeout;
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
	float unknownA18;
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
	int managed_session_process_pending_timeout;
	int unknownE68;
	int idle_peer_joining_timeout;
	int peer_join_timed_out;
	int join_queue_max_wait_time;
	int unknownE78;
	int unknownE7C;
	int idle_peer_join_abort_timeout;
	int unknownE84;
	int idle_peer_leaving_timeout;
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
	int connection_initiation_retry_count;
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
	int lobby_film_max_player_count;
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
	int network_mode_default;
	int offline_max_player_count;
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
	int determinism_version;
	int unknown16C0;

	void SetMaxOfflinePlayerCount(int player_count)
	{
		offline_max_player_count = player_count;
	}
	void SetMaxCoopPlayerCount(int player_count)
	{
		lobby_coop_max_player_count = player_count;
	}
	void SetMaxForgePlayerCount(int player_count)
	{
		lobby_mapeditor_max_player_count = player_count;
	}
	void SetMaxTheaterPlayerCount(int player_count)
	{
		lobby_film_max_player_count = player_count;
	}
};
auto initial_network_values = GetStructure<s_initial_network_values>(0x19A62C0);

int32_t achievement_string_ids[] {
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

	const char *GetName()
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

	const char *GetDescription()
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

	const char *GetImageName()
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


	const char *GetInsertionPointName(e_insertion_point insertion_point)
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

	const char *GetInsertionPointDescription(e_insertion_point insertion_point)
	{
		if (value == _mainmenu)
			return "";

		std::vector<const char *> names;

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

	const char *GetName()
	{
		const char *names[] {
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

	const char *GetDescription()
	{
		const char *description[] {
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
			return ((1 << (index & 31)) & GetStructure<s_player_profile>(0x524EC48, local_user_index)->achievements[index >> 5]) != 0;
		return false;
	}

	bool __cdecl get_if_valid(int local_user_index, int index)
	{
		return check_is_valid(local_user_index, index) || (1 << (index & 31)) & *GetStructure<int>(0x584BA20, (index >> 5) + 2 * local_user_index);
	}

	signed int grant(int local_user_index, int index)
	{
		signed int result = ((get_if_valid(local_user_index, index) && true) ? 6 : -1);
		if (result == -1)
		{
			result = 1 << (index & 31);
			*GetStructure<int>(0x584BA20, (index >> 5) + 2 * local_user_index) |= result;
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

auto g_default_maps_path = "maps\\";
std::string g_maps_path = g_default_maps_path;

struct s_cache_file_path
{
	std::string filename;
	size_t offset;
	std::string file_path;

	s_cache_file_path(size_t offset_, std::string filename_)
	{
		filename = filename_;
		file_path = g_maps_path + filename;
		offset = offset_;
	}
	s_cache_file_path *Update(std::string mapname)
	{
		file_path = g_maps_path + mapname + "\\" + filename;
		return this;
	}
	std::string Read()
	{
		return Pointer::Base(offset).Read<char*>();
	}
	void Write(bool shouldWrite)
	{
		if (shouldWrite)
			Pointer::Base(offset).Write(file_path.c_str());
	}
	void Print()
	{
		printf_s("%s\n", file_path.c_str());
	}
};

s_cache_file_path g_string_ids = s_cache_file_path(0x149CFEC, "string_ids.dat");
s_cache_file_path g_tags = s_cache_file_path(0x149CFF0, "tags.dat");
s_cache_file_path g_tag_list = s_cache_file_path(0x149CFF4, "tag_list.csv");
s_cache_file_path g_resources = s_cache_file_path(0x149CFF8, "resources.dat");
s_cache_file_path g_textures = s_cache_file_path(0x149CFFC, "textures.dat");
s_cache_file_path g_textures_b = s_cache_file_path(0x149D000, "textures_b.dat");
s_cache_file_path g_audio = s_cache_file_path(0x149D004, "audio.dat");
s_cache_file_path g_video = s_cache_file_path(0x149D008, "video.dat");

struct s_cache_path
{
	void Update(bool new_cache_style = false)
	{
		g_string_ids.Update(map_data->map_name)->Write(new_cache_style);
		g_tags.Update(map_data->map_name)->Write(new_cache_style);
		g_tag_list.Update(map_data->map_name)->Write(new_cache_style);
		g_resources.Update(map_data->map_name)->Write(new_cache_style);
		g_textures.Update(map_data->map_name)->Write(new_cache_style);
		g_textures_b.Update(map_data->map_name)->Write(new_cache_style);
		g_audio.Update(map_data->map_name)->Write(new_cache_style);
		g_video.Update(map_data->map_name)->Write(new_cache_style);
	}
	void Print()
	{
		g_string_ids.Print();
		g_tag_list.Print();
		g_resources.Print();
		g_textures.Print();
		g_textures_b.Print();
		g_audio.Print();
		g_video.Print();
		g_tags.Print();
	}
} cache_path;

template<typename T>
struct point2d
{
	T x, y;
};

template<typename T>
struct point3d
{
	T x, y, z;
};

template<typename T>
struct point4d
{
	T x, y, z, w;
};

template<typename T>
struct vector2d
{
	T i, j;
};

template<typename T>
struct vector3d
{
	T i, j, k;
};

template<typename T>
struct vector4d
{
	T i, j, k, w;
};

struct s_field_of_view
{
	float radians;

	float Get()
	{
		return (float)(radians / 0.0174533);
	}
};

struct s_camera_definition
{
	uint32_t state_flags;
	vector3d<float> position;
	vector3d<float> position_shift;
	float look;
	float look_shift;
	float depth;
	s_field_of_view field_of_view;
	vector3d<float> forward;
	vector3d<float> up;
	vector3d<float> direction;
	uint8_t unknown50[56];
	vector3d<float> center; // unsure
	float unknown94;
	uint32_t root_object_handle;
	uint8_t unknown9C[28];
	byte byte_flagsB8;
	uint8_t unknownB9[3];
	uint8_t unknownBC;
	uint8_t unknownBD[19];
	float zoom_transition_time;
	uint8_t unknownD4[4];
	uint32_t dword_flagsD8;
	uint8_t unknownDC[16];

	s_camera_definition *Print(bool position_and_shift, bool look_and_depth_and_fov, bool forward_and_up_and_direction, bool center_and_zoom_transition_time)
	{
		if (direction.i != 0.0f || direction.j != 0.0f || direction.k != 0.0f)
		{
			if (position_and_shift)
				printf_s("pos: %f %f %f, pos_shift: %f %f %f\n", position.i, position.j, position.k, position_shift.i, position_shift.j, position_shift.k);
			if (look_and_depth_and_fov)
				printf_s("look: %f, look_shift: %f, depth: %f, fov: %f\n", look, look_shift, depth, field_of_view.Get());
			if (forward_and_up_and_direction)
				printf_s("forward: %f %f %f, up: %f %f %f, direction: %f %f %f\n", forward.i, forward.j, forward.k, up.i, up.j, up.k, direction.i, direction.j, direction.k);
			if (center_and_zoom_transition_time)
				printf_s("center: %f %f %f, zoom_transition_time: %f\n", center.i, center.j, center.k, zoom_transition_time);
		}
		return this;
	}
};
_STATIC_ASSERT(sizeof(s_camera_definition) == 0xEC);

const auto g_tag_index_table_ptr = (uint32_t**)0x22AAFFC;
const auto g_tag_table_ptr = (uint8_t***)0x22AAFF8;
const auto g_max_tag_count_ptr = (uint32_t*)0x22AB008;
uint16_t last_tag = 0xFFFF;
uint16_t globals_tag = 0xFFFF;

struct s_join_data
{
	char a1;
	int a2;
	XnkAddr *a3, *a4, *a5;
	bool succeeded;

	void Print()
	{
		printf_s("%s | %d | %s | %s | %s\n", a1 ? "true" : "false", a2, a3->String(), a4->String(), a5->String());
	}

	bool Join(bool use_network_join_to_remote_squad = false)
	{
		if (use_network_join_to_remote_squad)
			succeeded = ((char(__cdecl *)(char, char, char, int, XnkAddr *, XnkAddr *, XnkAddr *))0x47ECF0)(((char(__cdecl *)())0x455320)() == false, a1, true, a2, a3, a5, a4);
		else
			succeeded = ((char(__cdecl *)(char, int, XnkAddr *, XnkAddr *, XnkAddr *))0xA7E3C0)(a1, a2, a3, a4, a5);

		Print();

		return succeeded;
	}
};

struct s_session_membership
{
	uint8_t membership[0x1A3F20];
};
_STATIC_ASSERT(sizeof(s_session_membership) == 0x1A3F20);
struct s_session_parameters
{
	uint8_t parameters[0xB7928];

	void *GetRequestedJoinData()
	{
		return (void *)(parameters + 0xB5880);
	}
};
_STATIC_ASSERT(sizeof(s_session_parameters) == 0xB7928);
struct s_session
{
	uint8_t session[0x25BC40];

	s_session_membership *GetMembership()
	{
		return (s_session_membership *)(session + 0x20);
	}
	s_session_parameters *GetParameters()
	{
		return (s_session_parameters *)(session + 0x1A3F40);
	}
	uint32_t GetType()
	{
		return *(uint32_t *)(session + 0x25B870);
	}
	uint32_t GetAddressIndex()
	{
		return *(uint32_t *)(session + 0x25BBF0);
	}
};
_STATIC_ASSERT(sizeof(s_session) == 0x25BC40);
auto g_squad_session = GetStructure<s_session>(0x19AB848);

struct s_remote_join_data
{
	uint8_t data[0x58];

	void SetJoinData(char a1, uint32_t sign_in_state, XnkAddr *a5, XnkAddr *a6, XnkAddr *a7)
	{
		*(uint32_t *)(data + 0x10) = ((uint32_t(__cdecl *)())0x431010)(); // generate_random_seed;
		*(uint32_t *)(data + 0x10) = 1;

		*(XnkAddr *)(data + 0x1C) = *a5;
		*(XnkAddr *)(data + 0x2C) = *a6;
		*(XnkAddr *)(data + 0x3C) = *a7;

		*(uint32_t *)(data + 0x4C) = sign_in_state;
		*(uint8_t *)(data + 0x54) = a1;
	}
};
_STATIC_ASSERT(sizeof(s_remote_join_data) == 0x58);
auto g_remote_join_data = GetStructure<s_remote_join_data>(0x2240B98);