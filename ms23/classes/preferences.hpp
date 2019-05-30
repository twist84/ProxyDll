#pragma once
#include <iostream>

#include <Utils.hpp>
#include "../memory/local_types.hpp"

#include "filo.hpp"
#include "renderer.hpp"

#include <d3d9.h>

struct
{
	gamemode game_mode = { "Save Data" };
	lobby lobby_data = { "Save Data (Lobby Specific)" };

	stringid lobbytype_string_id = { 0x341, "LobbyType StringId" };
	//uint32 last_mapid_and_campaignid;
	//uint32 last_network_mode;

	//uint32 minor_version;
	//============================ CONFIG ============================
	//uint32 display_adapter;
	toggle hide_watermark = { e_toggle_option::_off, "Hide Watermark", true };
	game_language language = { e_game_language::_english, "Game Language" };
	toggle display_subtitles = { e_toggle_option::_on, "Display Subtitles" };

	//=========================== SETTINGS ===========================
	//=========================== GAMEPLAY ===========================
	toggle hud_shake = { e_toggle_option::_off, "Hud Shake" };
	player_marker player_marker = { e_player_marker_option::_default_colors, "Player Marker Colors" };
	uint32 camera_fov = { 110, "Camera Field-of-View" };

	//=========================== CONTROLS ===========================
	control_method control_method = { e_control_method_option::_keyboard_and_mouse, "Control Method" };
	//uint32 bindings;
	uint32 mouse_sensitivity_vertical = { 25, "Mouse Sensitivity: Vertical" };
	uint32 mouse_sensitivity_horizontal = { 25, "Mouse Sensitivity: Horizontal" };

	uint32 mouse_sensitivity_vehicle_vertical = { 25, "Mouse Sensitivity: Vehicle Vertical" };
	uint32 mouse_sensitivity_vehicle_horizontal = { 25, "Mouse Sensitivity: Vehicle Horizontal" };

	uint32 mouse_acceleration = { 0, "Mouse Acceleration" };
	toggle mouse_filter = { e_toggle_option::_off, "Mouse Filter" };
	toggle invert_mouse = { e_toggle_option::_off, "Invert Mouse" };
	toggle toggle_crouch = { e_toggle_option::_on, "Toggle Crouch" };

	//============================= VIDEO ============================
	//uint32 screen_resolution_list;
	screen_resolution screen_resolution = { 1920, 1080, "Screen Resolution" };

	quality texture_resolution = { e_quality_option::_high, "Texture Resolution (Requires Restart)" };
	quality texture_filtering_quality = { e_quality_option::_high, "Texture Filtering Quality" };
	quality lighting_quality = { e_quality_option::_high, "Lighting Quality" };
	quality effects_quality = { e_quality_option::_high, "Effects Quality" };
	quality shadow_quality = { e_quality_option::_high, "Shadow Quality" };
	quality details_quality = { e_quality_option::_high, "Details Quality" };
	quality postprocessing_quality = { e_quality_option::_high, "Post-Processing Quality" };
	toggle motion_blur = { e_toggle_option::_off, "Motion Blur", true };

	uint32 brightness = { 50, "Brightness" };
	uint32 contrast = { 50, "Contrast" };
	toggle antialiasing = { e_toggle_option::_on, "Antialiasing", true };
	toggle fullscreen = { e_toggle_option::_on, "Fullscreen" };
	toggle vsync = { e_toggle_option::_on, "VSync", true };

	//============================= AUDIO ============================
	uint32 master_volume = { 60, "Master Volume" };
	uint32 music_volume = { 20, "Music Volume" };
	uint32 sfx_volume = { 80, "Sound Effects Volume" };
	//uint32 voice_volume;
	//uint32 voice_chat_volume;
	//uint32 voice_chat_control;
} preferences;

uint32_t preferences_get_lobbytype_string_id()
{
	return preferences.lobbytype_string_id.get();
}

void preferences_set_lobbytype_string_id(uint32_t a1)
{
	preferences.lobbytype_string_id.set(a1);
}

e_toggle_option preferences_get_antialiasing()
{
	return preferences.antialiasing.get();
}

void preferences_set_antialiasing(e_toggle_option a1)
{
	preferences.antialiasing.set(a1);
}

e_toggle_option preferences_get_hud_shake()
{
	return preferences.hud_shake.get();
}

void preferences_set_hud_shake(e_toggle_option a1)
{
	preferences.hud_shake.set(a1);
}

void preferences_get_screen_resolution(int *a1, int *a2)
{
	return preferences.screen_resolution.get(a1, a2);
}

void preferences_set_screen_resolution(int a1, int a2)
{
	preferences.screen_resolution.set(a1, a2);
	preferences.screen_resolution.width = a1;
	preferences.screen_resolution.height = a2;
}

void __cdecl display_preferences_update_back_buffer_hook(int adapter, int BackBufferWidth, int BackBufferHeight, e_toggle_option Fullscreen)
{
	if (preferences.screen_resolution.locked)
		return;

	preferences.screen_resolution.set(BackBufferWidth, BackBufferHeight);
	preferences.screen_resolution.width = BackBufferWidth;
	preferences.screen_resolution.height = BackBufferHeight;
	if (adapter == g_adapter)
	{
		memcpy(g_NewDisplayPreferences, g_DisplayPreferences, sizeof(D3DPRESENT_PARAMETERS));
		g_NewDisplayPreferences->BackBufferWidth = BackBufferWidth;
		g_NewDisplayPreferences->BackBufferHeight = BackBufferHeight;

		if (!StandardRendering.val)
			g_NewDisplayPreferences->Windowed = !Fullscreen.value; // != 2;

		preferences.fullscreen.set(Fullscreen);
		*(uint8_t *)0x50DD9D1 = 1;
	}
}

s_saved_game_data *preferences_get_gamemode_data()
{
	file_read_from_path(save_data[6].Path, save_data[6].Size, save_data[6].Buffer);
	return preferences.game_mode.get();
}

void preferences_set_gamemode_data(s_saved_game_data *a1)
{
	preferences.game_mode.set(a1);
	file_write_to_path(save_data[6].Path, save_data[6].Size, save_data[6].Buffer);
}

void preferences_set_lobby_data(s_lobby_data *a1)
{
	preferences.lobby_data.set(a1);
	file_write_to_path(save_data[6].Path, save_data[6].Size, save_data[6].Buffer);
	file_write_to_path(save_data[a1->LobbyType.value].Path, save_data[a1->LobbyType.value].Size, save_data[a1->LobbyType.value].Buffer);
}

e_game_language preferences_get_language()
{
	return preferences.language.get();
}

void preferences_set_language(e_game_language a1)
{
	preferences.language.set(a1);
}

e_toggle_option preferences_get_vsync()
{
	return preferences.vsync.get();
}

void preferences_set_vsync(e_toggle_option a1)
{
	preferences.vsync.set(a1);
}

e_toggle_option preferences_get_hide_watermark()
{
	return preferences.hide_watermark.get();
}

void preferences_set_hide_watermark(e_toggle_option a1)
{
	preferences.hide_watermark.set(a1);
}

e_quality_option preferences_get_lighting_quality()
{
	return preferences.lighting_quality.get();
}

void preferences_set_lighting_quality(e_quality_option a1)
{
	preferences.lighting_quality.set(a1);
}

uint32_t preferences_get_master_volume()
{
	return preferences.master_volume.get();
}

void preferences_set_master_volume(uint32_t a1)
{
	preferences.master_volume.set(a1);
}

e_toggle_option preferences_get_motion_blur()
{
	return preferences.motion_blur.get();
}

void preferences_set_motion_blur(e_toggle_option a1)
{
	preferences.motion_blur.set(a1);
}

uint32_t preferences_get_mouse_acceleration()
{
	return preferences.mouse_acceleration.get();
}

void preferences_set_mouse_acceleration(uint32_t a1)
{
	preferences.mouse_acceleration.set(a1);
}

e_toggle_option preferences_get_mouse_filter()
{
	return preferences.mouse_filter.get();
}

void preferences_set_mouse_filter(e_toggle_option a1)
{
	preferences.mouse_filter.set(a1);
}

e_toggle_option preferences_get_invert_mouse()
{
	return preferences.invert_mouse.get();
}

void preferences_set_invert_mouse(e_toggle_option a1)
{
	preferences.invert_mouse.set(a1);
}

uint32_t preferences_get_mouse_sensitivity_horizontal()
{
	return preferences.mouse_sensitivity_horizontal.get();
}

void preferences_set_mouse_sensitivity_horizontal(uint32_t a1)
{
	preferences.mouse_sensitivity_horizontal.set(a1);
}
uint32_t preferences_get_mouse_sensitivity_vehicle_horizontal()
{
	return preferences.mouse_sensitivity_vehicle_horizontal.get();
}

void preferences_set_mouse_sensitivity_vehicle_horizontal(uint32_t a1)
{
	preferences.mouse_sensitivity_vehicle_horizontal.set(a1);
}

uint32_t preferences_get_mouse_sensitivity_vehicle_vertical()
{
	return preferences.mouse_sensitivity_vehicle_vertical.get();
}

void preferences_set_mouse_sensitivity_vehicle_vertical(uint32_t a1)
{
	preferences.mouse_sensitivity_vehicle_vertical.set(a1);
}

uint32_t preferences_get_mouse_sensitivity_vertical()
{
	return preferences.mouse_sensitivity_vertical.get();
}

void preferences_set_mouse_sensitivity_vertical(uint32_t a1)
{
	preferences.mouse_sensitivity_vertical.set(a1);
}

uint32_t preferences_get_music_volume()
{
	return preferences.music_volume.get();
}

void preferences_set_music_volume(uint32_t a1)
{
	preferences.music_volume.set(a1);
}

e_quality_option preferences_get_postprocessing_quality()
{
	return preferences.postprocessing_quality.get();
}

void preferences_set_postprocessing_quality(e_quality_option a1)
{
	preferences.postprocessing_quality.set(a1);
}

uint32_t preferences_get_sfx_volume()
{
	return preferences.sfx_volume.get();
}

void preferences_set_sfx_volume(uint32_t a1)
{
	preferences.sfx_volume.set(a1);
}

e_quality_option preferences_get_shadow_quality()
{
	return preferences.shadow_quality.get();
}

void preferences_set_shadow_quality(e_quality_option a1)
{
	preferences.shadow_quality.set(a1);
}

e_toggle_option preferences_get_display_subtitles()
{
	return preferences.display_subtitles.get();
}
void preferences_set_display_subtitles(e_toggle_option a1)
{
	preferences.display_subtitles.set(a1);
}

e_player_marker_option preferences_get_player_marker()
{
	return preferences.player_marker.get();
}

void preferences_set_player_marker(e_player_marker_option a1)
{
	preferences.player_marker.set(a1);
}

e_quality_option preferences_get_texture_filtering_quality()
{
	return preferences.texture_filtering_quality.get();
}

void preferences_set_texture_filtering_quality(e_quality_option a1)
{
	preferences.texture_filtering_quality.set(a1);
}

e_quality_option preferences_get_texture_resolution()
{
	return preferences.texture_resolution.get();
}

void preferences_set_texture_resolution(e_quality_option a1)
{
	preferences.texture_resolution.set(a1);
}

e_toggle_option preferences_get_toggle_crouch()
{
	return preferences.toggle_crouch.get();
}

void preferences_set_toggle_crouch(e_toggle_option a1)
{
	preferences.toggle_crouch.set(a1);
}

e_quality_option preferences_get_effects_quality()
{
	return preferences.effects_quality.get();
}

void preferences_set_effects_quality(e_quality_option a1)
{
	preferences.effects_quality.set(a1);
}

e_toggle_option preferences_get_fullscreen()
{
	return preferences.fullscreen.get();
}

void preferences_set_fullscreen(e_toggle_option a1)
{
	preferences.fullscreen.set(a1);
}

e_control_method_option preferences_get_control_method()
{
	return preferences.control_method.get();
}

void preferences_set_control_method(e_control_method_option a1)
{
	preferences.control_method.set(a1);
}

e_quality_option preferences_get_details_quality()
{
	return preferences.details_quality.get();
}

void preferences_set_details_quality(e_quality_option a1)
{
	preferences.details_quality.set(a1);
}
 
uint32_t preferences_get_brightness()
{
	return preferences.brightness.get();
}

void preferences_set_brightness(uint32_t a1)
{
	preferences.brightness.set(a1);
}

uint32_t preferences_get_contrast()
{
	return preferences.contrast.get();
}

void preferences_set_contrast(uint32_t a1)
{
	preferences.contrast.set(a1);
}

inline void AddPreferencesHooks(const char *name)
{
	if (ConfigManager.GetBool("Hooks", name))
	{
		HookManager.AddHook({ 0x10B810 }, &preferences_get_lobbytype_string_id, "preferences_get_lobbytype_string_id");
		HookManager.AddHook({ 0x10DA10 }, &preferences_set_lobbytype_string_id, "preferences_set_lobbytype_string_id");
		HookManager.AddHook({ 0x10A830 }, &preferences_get_antialiasing, "preferences_get_antialiasing");
		HookManager.AddHook({ 0x10CCE0 }, &preferences_set_antialiasing, "preferences_set_antialiasing");
		HookManager.AddHook({ 0x10B350 }, &preferences_get_hud_shake, "preferences_get_hud_shake");
		HookManager.AddHook({ 0x10D6A0 }, &preferences_set_hud_shake, "preferences_set_hud_shake");
		//HookManager.AddHook({ 0x10B4D0 }, &preferences_get_screen_resolution_list, "preferences_get_screen_resolution_list");
		//HookManager.AddHook({ 0x10D850 }, &preferences_set_screen_resolution_list, "preferences_set_screen_resolution_list");
		HookManager.AddHook({ 0x10C030 }, &preferences_get_screen_resolution, "preferences_get_screen_resolution");
		HookManager.AddHook({ 0x10E1C0 }, &preferences_set_screen_resolution, "preferences_set_screen_resolution");
		HookManager.AddHook({ 0x6228D0 }, &display_preferences_update_back_buffer_hook, "display_preferences_update_back_buffer");
		HookManager.AddHook({ 0x10B560 }, &preferences_get_gamemode_data, "preferences_get_gamemode_data");
		HookManager.AddHook({ 0x10D8E0 }, &preferences_set_gamemode_data, "preferences_set_gamemode_data");
		HookManager.AddHook({ 0x10EBA0 }, &preferences_set_lobby_data, "preferences_set_lobby_data");
		//HookManager.AddHook({ 0x10B5E0 }, &preferences_get_last_mapid_and_campaignid, "preferences_get_last_mapid_and_campaignid");
		HookManager.AddHook({ 0x10B790 }, &preferences_get_language, "preferences_get_language");
		HookManager.AddHook({ 0x10D980 }, &preferences_set_language, "preferences_set_language");
		//HookManager.AddHook({ 0x10C550 }, &preferences_get_voice_chat_control, "preferences_get_voice_chat_control");
		//HookManager.AddHook({ 0x10E770 }, &preferences_set_voice_chat_control, "preferences_set_voice_chat_control");
		//HookManager.AddHook({ 0x10C5D0 }, &preferences_get_voice_chat_volume, "preferences_get_voice_chat_volume");
		//HookManager.AddHook({ 0x10E800 }, &preferences_set_voice_chat_volume, "preferences_set_voice_chat_volume");
		//HookManager.AddHook({ 0x10C650 }, &preferences_get_voice_volume, "preferences_get_voice_volume");
		//HookManager.AddHook({ 0x10E890 }, &preferences_set_voice_volume, "preferences_set_voice_volume");
		HookManager.AddHook({ 0x10C6D0 }, &preferences_get_vsync, "preferences_get_vsync");
		HookManager.AddHook({ 0x10E920 }, &preferences_set_vsync, "preferences_set_vsync");
		//HookManager.AddHook({ 0x10C750 }, &preferences_get_last_network_mode, "preferences_get_last_network_mode");
		//HookManager.AddHook({ 0x10E9B0 }, &preferences_set_last_network_mode, "preferences_set_last_network_mode");
		HookManager.AddHook({ 0x10EA40 }, &preferences_get_hide_watermark, "preferences_get_hide_watermark");
		HookManager.AddHook({ 0x10D610 }, &preferences_set_hide_watermark, "preferences_set_hide_watermark");
		HookManager.AddHook({ 0x10B890 }, &preferences_get_lighting_quality, "preferences_get_lighting_quality");
		HookManager.AddHook({ 0x10DAA0 }, &preferences_set_lighting_quality, "preferences_set_lighting_quality");
		HookManager.AddHook({ 0x10B910 }, &preferences_get_master_volume, "preferences_get_master_volume");
		HookManager.AddHook({ 0x10DB30 }, &preferences_set_master_volume, "preferences_set_master_volume");
		HookManager.AddHook({ 0x10B990 }, &preferences_get_motion_blur, "preferences_get_motion_blur");
		HookManager.AddHook({ 0x10DBC0 }, &preferences_set_motion_blur, "preferences_set_motion_blur");
		HookManager.AddHook({ 0x10BA10 }, &preferences_get_mouse_acceleration, "preferences_get_mouse_acceleration");
		HookManager.AddHook({ 0x10DC50 }, &preferences_set_mouse_acceleration, "preferences_set_mouse_acceleration");
		HookManager.AddHook({ 0x10BA90 }, &preferences_get_mouse_filter, "preferences_get_mouse_filter");
		HookManager.AddHook({ 0x10DCE0 }, &preferences_set_mouse_filter, "preferences_set_mouse_filter");
		HookManager.AddHook({ 0x10BB10 }, &preferences_get_invert_mouse, "preferences_get_invert_mouse");
		HookManager.AddHook({ 0x10DD70 }, &preferences_set_invert_mouse, "preferences_set_invert_mouse");
		HookManager.AddHook({ 0x10BB90 }, &preferences_get_mouse_sensitivity_horizontal, "preferences_get_mouse_sensitivity_horizontal");
		HookManager.AddHook({ 0x10DE00 }, &preferences_set_mouse_sensitivity_horizontal, "preferences_set_mouse_sensitivity_horizontal");
		HookManager.AddHook({ 0x10BC10 }, &preferences_get_mouse_sensitivity_vehicle_horizontal, "preferences_get_mouse_sensitivity_vehicle_horizontal");
		HookManager.AddHook({ 0x10DE90 }, &preferences_set_mouse_sensitivity_vehicle_horizontal, "preferences_set_mouse_sensitivity_vehicle_horizontal");
		HookManager.AddHook({ 0x10BC90 }, &preferences_get_mouse_sensitivity_vehicle_vertical, "preferences_get_mouse_sensitivity_vehicle_vertical");
		HookManager.AddHook({ 0x10DF20 }, &preferences_set_mouse_sensitivity_vehicle_vertical, "preferences_set_mouse_sensitivity_vehicle_vertical");
		HookManager.AddHook({ 0x10BD10 }, &preferences_get_mouse_sensitivity_vertical, "preferences_get_mouse_sensitivity_vertical");
		HookManager.AddHook({ 0x10DFB0 }, &preferences_set_mouse_sensitivity_vertical, "preferences_set_mouse_sensitivity_vertical");
		HookManager.AddHook({ 0x10BD90 }, &preferences_get_music_volume, "preferences_get_music_volume");
		HookManager.AddHook({ 0x10E040 }, &preferences_set_music_volume, "preferences_set_music_volume");
		HookManager.AddHook({ 0x10BE10 }, &preferences_get_postprocessing_quality, "preferences_get_postprocessing_quality");
		HookManager.AddHook({ 0x10E0D0 }, &preferences_set_postprocessing_quality, "preferences_set_postprocessing_quality");
		//HookManager.AddHook({ 0x10BFA0 }, &preferences_get_display_adapter, "preferences_get_display_adapter");
		//HookManager.AddHook({ 0x10E160 }, &preferences_set_display_adapter, "preferences_set_display_adapter");
		HookManager.AddHook({ 0x10C0D0 }, &preferences_get_sfx_volume, "preferences_get_sfx_volume");
		HookManager.AddHook({ 0x10E260 }, &preferences_set_sfx_volume, "preferences_set_sfx_volume");
		HookManager.AddHook({ 0x10C150 }, &preferences_get_shadow_quality, "preferences_get_shadow_quality");
		HookManager.AddHook({ 0x10E2F0 }, &preferences_set_shadow_quality, "preferences_set_shadow_quality");
		HookManager.AddHook({ 0x10C1D0 }, &preferences_get_display_subtitles, "preferences_get_display_subtitles");
		HookManager.AddHook({ 0x10E380 }, &preferences_set_display_subtitles, "preferences_set_display_subtitles");
		HookManager.AddHook({ 0x10C250 }, &preferences_get_player_marker, "preferences_get_player_marker");
		HookManager.AddHook({ 0x10E410 }, &preferences_set_player_marker, "preferences_set_player_marker");
		HookManager.AddHook({ 0x10C2D0 }, &preferences_get_texture_filtering_quality, "preferences_get_texture_filtering_quality");
		HookManager.AddHook({ 0x10E4A0 }, &preferences_set_texture_filtering_quality, "preferences_set_texture_filtering_quality");
		HookManager.AddHook({ 0x10C350 }, &preferences_get_texture_resolution, "preferences_get_texture_resolution");
		HookManager.AddHook({ 0x10E530 }, &preferences_set_texture_resolution, "preferences_set_texture_resolution");
		HookManager.AddHook({ 0x10C3D0 }, &preferences_get_toggle_crouch, "preferences_get_toggle_crouch");
		HookManager.AddHook({ 0x10E5C0 }, &preferences_set_toggle_crouch, "preferences_set_toggle_crouch");
		HookManager.AddHook({ 0x10B150 }, &preferences_get_effects_quality, "preferences_get_effects_quality");
		HookManager.AddHook({ 0x10D3D0 }, &preferences_set_effects_quality, "preferences_set_effects_quality");
		HookManager.AddHook({ 0x10B250 }, &preferences_get_fullscreen, "preferences_get_fullscreen");
		HookManager.AddHook({ 0x10D4F0 }, &preferences_set_fullscreen, "preferences_set_fullscreen");
		//HookManager.AddHook({ 0x10A9B0 }, &preferences_get_minor_version, "preferences_get_minor_version");
		//HookManager.AddHook({ 0x10CE90 }, &preferences_set_minor_version, "preferences_set_minor_version");
		//HookManager.AddHook({ 0x10AA30 }, &preferences_get_camera_fov, "preferences_get_camera_fov");
		//HookManager.AddHook({ 0x10CF20 }, &preferences_set_camera_fov, "preferences_set_camera_fov");
		HookManager.AddHook({ 0x10AAC0 }, &preferences_get_control_method, "preferences_get_control_method");
		HookManager.AddHook({ 0x10CFB0 }, &preferences_set_control_method, "preferences_set_control_method");
		//HookManager.AddHook({ 0x10AB40 }, &preferences_get_bindings, "preferences_get_bindings");
		//HookManager.AddHook({ 0x10D040 }, &preferences_set_bindings, "preferences_set_bindings");
		HookManager.AddHook({ 0x10AF50 }, &preferences_get_details_quality, "preferences_get_details_quality");
		HookManager.AddHook({ 0x10D190 }, &preferences_set_details_quality, "preferences_set_details_quality");
		HookManager.AddHook({ 0x10AFD0 }, &preferences_get_brightness, "preferences_get_brightness");
		HookManager.AddHook({ 0x10D220 }, &preferences_set_brightness, "preferences_set_brightness");
		HookManager.AddHook({ 0x10B050 }, &preferences_get_contrast, "preferences_get_contrast");
		HookManager.AddHook({ 0x10D2B0 }, &preferences_set_contrast, "preferences_set_contrast");
	}
}

void DisableSaberReflections()
{
	*(bool *)0x1917D62 = false;
}

inline void AddPreferencesPatches(const char *name)
{
	if (ConfigManager.GetBool("Patches", name))
	{
		PatchManager.AddPatch(&DisableSaberReflections, "DisableSaberReflections");
	}
}

void AllQualitySettingsToggleLock()
{
	preferences.texture_resolution.toggle_lock();
	preferences.texture_filtering_quality.toggle_lock();
	preferences.lighting_quality.toggle_lock();
	preferences.effects_quality.toggle_lock();
	preferences.shadow_quality.toggle_lock();
	preferences.details_quality.toggle_lock();
}

void SetAllQualitySettingsLow()
{
	AllQualitySettingsToggleLock();
	preferences.texture_resolution.set({ e_quality_option::_low });
	preferences.texture_filtering_quality.set({ e_quality_option::_low });
	preferences.lighting_quality.set({ e_quality_option::_low });
	preferences.effects_quality.set({ e_quality_option::_low });
	preferences.shadow_quality.set({ e_quality_option::_low });
	preferences.details_quality.set({ e_quality_option::_low });
	AllQualitySettingsToggleLock();
}

void SetAllQualitySettingsMedium()
{
	AllQualitySettingsToggleLock();
	preferences.texture_resolution.set({ e_quality_option::_medium });
	preferences.texture_filtering_quality.set({ e_quality_option::_medium });
	preferences.lighting_quality.set({ e_quality_option::_medium });
	preferences.effects_quality.set({ e_quality_option::_medium });
	preferences.shadow_quality.set({ e_quality_option::_medium });
	preferences.details_quality.set({ e_quality_option::_medium });
	AllQualitySettingsToggleLock();
}

void SetAllQualitySettingsHigh()
{
	AllQualitySettingsToggleLock();
	preferences.texture_resolution.set({ e_quality_option::_high });
	preferences.texture_filtering_quality.set({ e_quality_option::_high });
	preferences.lighting_quality.set({ e_quality_option::_high });
	preferences.effects_quality.set({ e_quality_option::_high });
	preferences.shadow_quality.set({ e_quality_option::_high });
	preferences.details_quality.set({ e_quality_option::_high });
	AllQualitySettingsToggleLock();
}