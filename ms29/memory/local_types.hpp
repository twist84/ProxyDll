#pragma once
#include <Windows.h>
#include <psapi.h>
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
std::string GetModuleName()
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

void* GetModuleAddress(const DWORD offset)
{
	static void* base_address = nullptr;

	if (base_address == nullptr)
	{
		MODULEINFO module_info = { 0 };

		auto result = GetModuleInformation(GetCurrentProcess(), GetModuleHandle(nullptr), &module_info, sizeof(module_info));

		if (!result)
			return nullptr;

		base_address = module_info.lpBaseOfDll;
	}

	return (char*)base_address + offset;
}

void UnprotectModuleMemory()
{
	MEMORY_BASIC_INFORMATION MemInfo;

	printf_s("unprotecting module memory...\n");
	for (auto offset = 0; VirtualQuery(GetModuleAddress(offset), &MemInfo, sizeof(MEMORY_BASIC_INFORMATION));)
	{
		printf_s("module region 0x%X\n", offset);
		offset += MemInfo.RegionSize;

		if (MemInfo.Protect == PAGE_EXECUTE_READ)
			VirtualProtect(MemInfo.BaseAddress, MemInfo.RegionSize, PAGE_EXECUTE_READWRITE, &MemInfo.Protect);
	}
	printf_s("module memory unprotected...\n");
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
	enum e : int
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

	e_game_language(int language)
	{
		value = (e)language;
	}

	e_game_language(LANGID id)
	{
		switch (id)
		{
		case LANG_CHINESE:
			value = e_game_language::_chinese_simplified;
			break;
		case LANG_GERMAN:
			value = e_game_language::_german;
			break;
		case LANG_SPANISH:
			value = e_game_language::_spanish;
			break;
		case LANG_FRENCH:
			value = e_game_language::_french;
			break;
		case LANG_ITALIAN:
			value = e_game_language::_italian;
			break;
		case LANG_JAPANESE:
			value = e_game_language::_japanese;
			break;
		case LANG_KOREAN:
			value = e_game_language::_korean;
			break;
		case LANG_PORTUGUESE:
			value = e_game_language::_portuguese;
			break;
		case LANG_RUSSIAN:
			value = e_game_language::_russian;
			break;
		default:
			value = e_game_language::_english;
			break;
		}
	}

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
auto g_language = -1;

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

//struct s_unit_action_info
//{
//	const char *Name;
//	unsigned short Unknown4;
//	unsigned short Unknown6;
//};
//struct e_unit_action
//{
//	enum : int
//	{
//		_death_ping = 0,
//		_custom_animation,
//		_stop_custom_animation,
//		_sync_container,
//		_assassinate,
//		_get_infected,
//		_hostile_morph,
//		_resurrect,
//		_hard_ping,
//		_ping,
//		_morph,
//		_morph_arrival,
//		_infect,
//		_posture,
//		_posture_exit,
//		_vehicle_exit,
//		_vehicle_exit_and_detach,
//		_vehicle_ejection,
//		_vehicle_board,
//		_vehicle_enter,
//		_open,
//		_close,
//		_vehicle_exit_immediate,
//		_vehicle_flip,
//		_climb_attach,
//		_climb_detach,
//		_wall_lean,
//		_wall_leanopen,
//		_token,
//		_take_off,
//		_perch,
//		_perch_jump,
//		_land,
//		_jump,
//		_leap_anticipation,
//		_leap,
//		_leap_recovery,
//		_emit_ai,
//		_berserk,
//		_flurry,
//		_deploy_turret,
//		_smash,
//		_vault,
//		_hoist,
//		_ai_impulse,
//		_melee_ai,
//		_weapon_pickup,
//		_weapon_trade,
//		_primary_weapon_drop,
//		_secondary_weapon_drop,
//		_surge,
//		_phase,
//		_stow,
//		_draw,
//		_infection_spew,
//		_kamikaze,
//		_primary_weapon_switch,
//		_secondary_weapon_switch,
//		_grenade,
//		_equipment,
//		_equipment_animation,
//		_equipment_pickup,
//		_equipment_drop,
//		_melee_player,
//		_primary_weapon_primary_reload,
//		_primary_weapon_secondary_reload,
//		_secondary_weapon_primary_reload,
//		_secondary_weapon_secondary_reload,
//		_soft_ping,
//		_primary_weapon_primary_recoil,
//		_primary_weapon_secondary_recoil,
//		_primary_weapon_primary_chamber,
//		_primary_weapon_secondary_chamber,
//		_primary_weapon_primary_charged,
//		_primary_weapon_secondary_charged,
//		_secondary_weapon_primary_recoil,
//		_secondary_weapon_secondary_recoil,
//		_secondary_weapon_primary_chamber,
//		_secondary_weapon_secondary_chamber,
//		_secondary_weapon_primary_charged,
//		_secondary_weapon_secondary_charged,
//		_primary_weapon_overheat_enter,
//		_primary_weapon_overheat_loop,
//		_primary_weapon_overheat_exit,
//		_secondary_weapon_overheat_enter,
//		_secondary_weapon_overheat_loop,
//		_secondary_weapon_overheat_exit,
//
//		k_number_of_unit_actions
//	} value;
//
//	const char *GetName()
//	{
//		return GetStructure<s_unit_action_info>(0x1947A58, value)->Name; // 0x12FCA90 in ms30
//	}
//};

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
		char DstBuf[32];
		int SizeInBytes = snprintf(DstBuf, 0, "%dx%d", width, height);
		DstBuf[SizeInBytes - 1] = '\0';
		return DstBuf;
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
	}
	void set(s_screen_resolution *a1)
	{
		if (a1->width == width && a1->height == height)
			return;
		if (locked)
		{
			printf_s("Unable to set %s: locked\n", name);
			return;
		}
		s_screen_resolution value = { width, height };
		auto prev = value;
		value.width = a1->width;
		value.height = a1->height;
		printf_s("Set %s: %s->%s\n", name, prev.ToString(), value.ToString());
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
	}
	void toggle_lock()
	{
		locked = !locked;
	}
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
	uint16_t unknown6;
	char path[256];
	HANDLE file_handle;
	uint32_t file_pointer;
};
auto global_tag_cache_filo = GetStructure<s_file_reference>(0x42E1088);

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

	//size_t GetArrayStartAddress(bool base = false)
	//{
	//	return GetAddress((void *)0x1655950, base);
	//}

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

struct s_cache_path
{
	const char *string_ids;
	const char *tags;
	const char *tag_list;
	const char *resources;
	const char *textures;
	const char *textures_b;
	const char *audio;
	const char *video; // resources_b
	const char *extension;
};
//auto cache_path = GetStructure<s_cache_path>(0x189CFEC);

struct {
	char data[256];
} current_cache_path;

auto g_default_maps_path = "maps\\";
auto g_maps_path = g_default_maps_path;

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
};
_STATIC_ASSERT(sizeof(s_camera_definition) == 0xEC);

//const auto g_tag_index_table_ptr = (uint32_t**)0x22AAFFC;
//const auto g_tag_table_ptr = (uint8_t***)0x22AAFF8;
//const auto g_max_tag_count_ptr = (uint32_t*)0x22AB008;
//uint16_t last_tag = 0xFFFF;
//uint16_t globals_tag = 0xFFFF;