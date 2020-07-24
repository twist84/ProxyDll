#pragma once
#include <iostream>

#include <Utils.hpp>
#include "../memory/local_types.hpp"

#include "filo.hpp"
#include "renderer.hpp"

#include <d3d9.h>

struct
{
	s_save_data_all SaveDataAll = { "Save Data (All)" };
	s_save_data SaveData = { "Save Data" };

	stringid LobbyType = { 0x341, "LobbyType StringId" };
	//uint32 LastMapidAndCampaignid;
	//uint32 LastNetworkMode;

	//uint32 MinorVersion;
	//============================ CONFIG ============================
	//uint32 DisplayAdapter;
	toggle HideWatermark = { e_toggle_option::_off, "Hide Watermark", true };
	game_language Language = { e_game_language::_english, "Game Language" };
	toggle DisplaySubtitles = { e_toggle_option::_on, "Display Subtitles" };

	//=========================== SETTINGS ===========================
	//=========================== GAMEPLAY ===========================
	toggle HudShake = { e_toggle_option::_off, "Hud Shake" };
	player_marker PlayerMarker = { e_player_marker_option::_default_colors, "Player Marker Colors" };
	uint32 CameraFov = { 110, "Camera Field-of-View" };

	//=========================== CONTROLS ===========================
	control_method ControlMethod = { e_control_method_option::_keyboard_and_mouse, "Control Method" };
	//uint32 Bindings;
	uint32 MouseSensitivityVertical = { 25, "Mouse Sensitivity: Vertical" };
	uint32 MouseSensitivityHorizontal = { 25, "Mouse Sensitivity: Horizontal" };

	uint32 MouseSensitivityVehicleVertical = { 25, "Mouse Sensitivity: Vehicle Vertical" };
	uint32 MouseSensitivityVehicleHorizontal = { 25, "Mouse Sensitivity: Vehicle Horizontal" };

	uint32 MouseAcceleration = { 0, "Mouse Acceleration" };
	toggle MouseFilter = { e_toggle_option::_off, "Mouse Filter" };
	toggle MouseInverted = { e_toggle_option::_off, "Mouse Inverted" };
	toggle ToggleCouch = { e_toggle_option::_on, "Toggle Crouch" };

	//============================= VIDEO ============================
	//uint32 ScreenResolutionList;
	screen_resolution ScreenResolution = { 1920, 1080, "Screen Resolution" };

	quality TextureResolution = { e_quality_option::_high, "Texture Resolution (Requires Restart)" };
	quality TextureFilteringQuality = { e_quality_option::_high, "Texture Filtering Quality" };
	quality LightingQuality = { e_quality_option::_high, "Lighting Quality" };
	quality EffectsQuality = { e_quality_option::_high, "Effects Quality" };
	quality ShadowQuality = { e_quality_option::_high, "Shadow Quality" };
	quality DetailsQuality = { e_quality_option::_high, "Details Quality" };
	quality PostProcessingQuality = { e_quality_option::_high, "Post-Processing Quality" };
	toggle MotionBlur = { e_toggle_option::_off, "Motion Blur", true };

	uint32 Brightness = { 50, "Brightness" };
	uint32 Contrast = { 50, "Contrast" };
	toggle AntiAliasing = { e_toggle_option::_on, "AntiAliasing", true };
	toggle Fullscreen = { e_toggle_option::_on, "Fullscreen" };
	toggle VSync = { e_toggle_option::_on, "VSync", true };

	//============================= AUDIO ============================
	uint32 MasterVolume = { 60, "Master Volume" };
	uint32 MusicVolume = { 20, "Music Volume" };
	uint32 SfxVolume = { 80, "Sound Effects Volume" };
	//uint32 VoiceVolume;
	//uint32 VoiceChatVolume;
	//uint32 VoiceChatControl;
} preferences;

uint32_t preferences_get_lobbytype_string_id()
{
	return preferences.LobbyType.get();
}

void preferences_set_lobbytype_string_id(uint32_t a1)
{
	preferences.LobbyType.set(a1);
}

e_toggle_option preferences_get_antialiasing()
{
	return preferences.AntiAliasing.get();
}

void preferences_set_antialiasing(e_toggle_option a1)
{
	preferences.AntiAliasing.set(a1);
}

e_toggle_option preferences_get_hud_shake()
{
	return preferences.HudShake.get();
}

void preferences_set_hud_shake(e_toggle_option a1)
{
	preferences.HudShake.set(a1);
}

void preferences_get_screen_resolution(int *a1, int *a2)
{
	return preferences.ScreenResolution.get(a1, a2);
}

void preferences_set_screen_resolution(int a1, int a2)
{
	preferences.ScreenResolution.set(a1, a2);
	preferences.ScreenResolution.width = a1;
	preferences.ScreenResolution.height = a2;
}

void __cdecl display_preferences_update_back_buffer_hook(int adapter, int BackBufferWidth, int BackBufferHeight, e_toggle_option Fullscreen)
{
	if (preferences.ScreenResolution.locked)
		return;

	preferences.ScreenResolution.set(BackBufferWidth, BackBufferHeight);
	preferences.ScreenResolution.width = BackBufferWidth;
	preferences.ScreenResolution.height = BackBufferHeight;
	if (adapter == g_adapter)
	{
		memcpy(&g_DisplayPreferencesNew, &g_DisplayPreferences, sizeof(D3DPRESENT_PARAMETERS));
		g_DisplayPreferencesNew.BackBufferWidth = BackBufferWidth;
		g_DisplayPreferencesNew.BackBufferHeight = BackBufferHeight;

		if (!StandardRendering.val)
			g_DisplayPreferencesNew.Windowed = !Fullscreen.value; // != 2;

		preferences.Fullscreen.set(Fullscreen);
		SetMemory<0x50DD9D1, uint8_t>(1);
	}
}

s_saved_game_data *preferences_get_all_save_data()
{
	file_read_from_path(save_data_data_array[6].Path, save_data_data_array[6].Size, save_data_data_array[6].Buffer);
	return preferences.SaveDataAll.get();
}

void preferences_set_all_save_data(s_saved_game_data *a1)
{
	preferences.SaveDataAll.set(a1);
	file_write_to_path(save_data_data_array[6].Path, save_data_data_array[6].Size, save_data_data_array[6].Buffer);
}

void preferences_set_save_data(s_lobby_data *a1)
{
	preferences.SaveData.set(a1);
	file_write_to_path(save_data_data_array[a1->LobbyType.value].Path, save_data_data_array[a1->LobbyType.value].Size, save_data_data_array[a1->LobbyType.value].Buffer);
}

e_game_language preferences_get_language()
{
	return preferences.Language.get();
}

void preferences_set_language(e_game_language a1)
{
	preferences.Language.set(a1);
}

e_toggle_option preferences_get_vsync()
{
	return preferences.VSync.get();
}

void preferences_set_vsync(e_toggle_option a1)
{
	preferences.VSync.set(a1);
}

e_toggle_option preferences_get_hide_watermark()
{
	return preferences.HideWatermark.get();
}

void preferences_set_hide_watermark(e_toggle_option a1)
{
	preferences.HideWatermark.set(a1);
}

e_quality_option preferences_get_lighting_quality()
{
	return preferences.LightingQuality.get();
}

void preferences_set_lighting_quality(e_quality_option a1)
{
	preferences.LightingQuality.set(a1);
}

uint32_t preferences_get_master_volume()
{
	return preferences.MasterVolume.get();
}

void preferences_set_master_volume(uint32_t a1)
{
	preferences.MasterVolume.set(a1);
}

e_toggle_option preferences_get_motion_blur()
{
	return preferences.MotionBlur.get();
}

void preferences_set_motion_blur(e_toggle_option a1)
{
	preferences.MotionBlur.set(a1);
}

uint32_t preferences_get_mouse_acceleration()
{
	return preferences.MouseAcceleration.get();
}

void preferences_set_mouse_acceleration(uint32_t a1)
{
	preferences.MouseAcceleration.set(a1);
}

e_toggle_option preferences_get_mouse_filter()
{
	return preferences.MouseFilter.get();
}

void preferences_set_mouse_filter(e_toggle_option a1)
{
	preferences.MouseFilter.set(a1);
}

e_toggle_option preferences_get_invert_mouse()
{
	return preferences.MouseInverted.get();
}

void preferences_set_invert_mouse(e_toggle_option a1)
{
	preferences.MouseInverted.set(a1);
}

uint32_t preferences_get_mouse_sensitivity_horizontal()
{
	return preferences.MouseSensitivityHorizontal.get();
}

void preferences_set_mouse_sensitivity_horizontal(uint32_t a1)
{
	preferences.MouseSensitivityHorizontal.set(a1);
}
uint32_t preferences_get_mouse_sensitivity_vehicle_horizontal()
{
	return preferences.MouseSensitivityVehicleHorizontal.get();
}

void preferences_set_mouse_sensitivity_vehicle_horizontal(uint32_t a1)
{
	preferences.MouseSensitivityVehicleHorizontal.set(a1);
}

uint32_t preferences_get_mouse_sensitivity_vehicle_vertical()
{
	return preferences.MouseSensitivityVehicleVertical.get();
}

void preferences_set_mouse_sensitivity_vehicle_vertical(uint32_t a1)
{
	preferences.MouseSensitivityVehicleVertical.set(a1);
}

uint32_t preferences_get_mouse_sensitivity_vertical()
{
	return preferences.MouseSensitivityVertical.get();
}

void preferences_set_mouse_sensitivity_vertical(uint32_t a1)
{
	preferences.MouseSensitivityVertical.set(a1);
}

uint32_t preferences_get_music_volume()
{
	return preferences.MusicVolume.get();
}

void preferences_set_music_volume(uint32_t a1)
{
	preferences.MusicVolume.set(a1);
}

e_quality_option preferences_get_postprocessing_quality()
{
	return preferences.PostProcessingQuality.get();
}

void preferences_set_postprocessing_quality(e_quality_option a1)
{
	preferences.PostProcessingQuality.set(a1);
}

uint32_t preferences_get_sfx_volume()
{
	return preferences.SfxVolume.get();
}

void preferences_set_sfx_volume(uint32_t a1)
{
	preferences.SfxVolume.set(a1);
}

e_quality_option preferences_get_shadow_quality()
{
	return preferences.ShadowQuality.get();
}

void preferences_set_shadow_quality(e_quality_option a1)
{
	preferences.ShadowQuality.set(a1);
}

e_toggle_option preferences_get_display_subtitles()
{
	return preferences.DisplaySubtitles.get();
}
void preferences_set_display_subtitles(e_toggle_option a1)
{
	preferences.DisplaySubtitles.set(a1);
}

e_player_marker_option preferences_get_player_marker()
{
	return preferences.PlayerMarker.get();
}

void preferences_set_player_marker(e_player_marker_option a1)
{
	preferences.PlayerMarker.set(a1);
}

e_quality_option preferences_get_texture_filtering_quality()
{
	return preferences.TextureFilteringQuality.get();
}

void preferences_set_texture_filtering_quality(e_quality_option a1)
{
	preferences.TextureFilteringQuality.set(a1);
}

e_quality_option preferences_get_texture_resolution()
{
	return preferences.TextureResolution.get();
}

void preferences_set_texture_resolution(e_quality_option a1)
{
	preferences.TextureResolution.set(a1);
}

e_toggle_option preferences_get_toggle_crouch()
{
	return preferences.ToggleCouch.get();
}

void preferences_set_toggle_crouch(e_toggle_option a1)
{
	preferences.ToggleCouch.set(a1);
}

e_quality_option preferences_get_effects_quality()
{
	return preferences.EffectsQuality.get();
}

void preferences_set_effects_quality(e_quality_option a1)
{
	preferences.EffectsQuality.set(a1);
}

e_toggle_option preferences_get_fullscreen()
{
	return preferences.Fullscreen.get();
}

void preferences_set_fullscreen(e_toggle_option a1)
{
	preferences.Fullscreen.set(a1);
}

e_control_method_option preferences_get_control_method()
{
	return preferences.ControlMethod.get();
}

void preferences_set_control_method(e_control_method_option a1)
{
	preferences.ControlMethod.set(a1);
}

e_quality_option preferences_get_details_quality()
{
	return preferences.DetailsQuality.get();
}

void preferences_set_details_quality(e_quality_option a1)
{
	preferences.DetailsQuality.set(a1);
}
 
uint32_t preferences_get_brightness()
{
	return preferences.Brightness.get();
}

void preferences_set_brightness(uint32_t a1)
{
	preferences.Brightness.set(a1);
}

uint32_t preferences_get_contrast()
{
	return preferences.Contrast.get();
}

void preferences_set_contrast(uint32_t a1)
{
	preferences.Contrast.set(a1);
}

inline void SubmitPreferencesHooks(const char *name)
{
	if (ConfigManager.GetBool("Hooks", name))
	{
		HookManager.Submit({ 0x0050B810 }, &preferences_get_lobbytype_string_id, "preferences_get_lobbytype_string_id");
		HookManager.Submit({ 0x0050DA10 }, &preferences_set_lobbytype_string_id, "preferences_set_lobbytype_string_id");
		HookManager.Submit({ 0x0050A830 }, &preferences_get_antialiasing, "preferences_get_antialiasing");
		HookManager.Submit({ 0x0050CCE0 }, &preferences_set_antialiasing, "preferences_set_antialiasing");
		HookManager.Submit({ 0x0050B350 }, &preferences_get_hud_shake, "preferences_get_hud_shake");
		HookManager.Submit({ 0x0050D6A0 }, &preferences_set_hud_shake, "preferences_set_hud_shake");
		//HookManager.Submit({ 0x0050B4D0 }, &preferences_get_screen_resolution_list, "preferences_get_screen_resolution_list");
		//HookManager.Submit({ 0x0050D850 }, &preferences_set_screen_resolution_list, "preferences_set_screen_resolution_list");
		HookManager.Submit({ 0x0050C030 }, &preferences_get_screen_resolution, "preferences_get_screen_resolution");
		HookManager.Submit({ 0x0050E1C0 }, &preferences_set_screen_resolution, "preferences_set_screen_resolution");
		HookManager.Submit({ 0x00A228D0 }, &display_preferences_update_back_buffer_hook, "display_preferences_update_back_buffer");
		HookManager.Submit({ 0x0050B560 }, &preferences_get_all_save_data, "preferences_get_all_save_data");
		HookManager.Submit({ 0x0050D8E0 }, &preferences_set_all_save_data, "preferences_set_all_save_data");
		HookManager.Submit({ 0x0050EBA0 }, &preferences_set_save_data, "preferences_set_save_data");
		//HookManager.Submit({ 0x0050B5E0 }, &preferences_get_last_mapid_and_campaignid, "preferences_get_last_mapid_and_campaignid");
		HookManager.Submit({ 0x0050B790 }, &preferences_get_language, "preferences_get_language");
		HookManager.Submit({ 0x0050D980 }, &preferences_set_language, "preferences_set_language");
		//HookManager.Submit({ 0x0050C550 }, &preferences_get_voice_chat_control, "preferences_get_voice_chat_control");
		//HookManager.Submit({ 0x0050E770 }, &preferences_set_voice_chat_control, "preferences_set_voice_chat_control");
		//HookManager.Submit({ 0x0050C5D0 }, &preferences_get_voice_chat_volume, "preferences_get_voice_chat_volume");
		//HookManager.Submit({ 0x0050E800 }, &preferences_set_voice_chat_volume, "preferences_set_voice_chat_volume");
		//HookManager.Submit({ 0x0050C650 }, &preferences_get_voice_volume, "preferences_get_voice_volume");
		//HookManager.Submit({ 0x0050E890 }, &preferences_set_voice_volume, "preferences_set_voice_volume");
		HookManager.Submit({ 0x0050C6D0 }, &preferences_get_vsync, "preferences_get_vsync");
		HookManager.Submit({ 0x0050E920 }, &preferences_set_vsync, "preferences_set_vsync");
		//HookManager.Submit({ 0x0050C750 }, &preferences_get_last_network_mode, "preferences_get_last_network_mode");
		//HookManager.Submit({ 0x0050E9B0 }, &preferences_set_last_network_mode, "preferences_set_last_network_mode");
		HookManager.Submit({ 0x0050EA40 }, &preferences_get_hide_watermark, "preferences_get_hide_watermark");
		HookManager.Submit({ 0x0050D610 }, &preferences_set_hide_watermark, "preferences_set_hide_watermark");
		HookManager.Submit({ 0x0050B890 }, &preferences_get_lighting_quality, "preferences_get_lighting_quality");
		HookManager.Submit({ 0x0050DAA0 }, &preferences_set_lighting_quality, "preferences_set_lighting_quality");
		HookManager.Submit({ 0x0050B910 }, &preferences_get_master_volume, "preferences_get_master_volume");
		HookManager.Submit({ 0x0050DB30 }, &preferences_set_master_volume, "preferences_set_master_volume");
		HookManager.Submit({ 0x0050B990 }, &preferences_get_motion_blur, "preferences_get_motion_blur");
		HookManager.Submit({ 0x0050DBC0 }, &preferences_set_motion_blur, "preferences_set_motion_blur");
		HookManager.Submit({ 0x0050BA10 }, &preferences_get_mouse_acceleration, "preferences_get_mouse_acceleration");
		HookManager.Submit({ 0x0050DC50 }, &preferences_set_mouse_acceleration, "preferences_set_mouse_acceleration");
		HookManager.Submit({ 0x0050BA90 }, &preferences_get_mouse_filter, "preferences_get_mouse_filter");
		HookManager.Submit({ 0x0050DCE0 }, &preferences_set_mouse_filter, "preferences_set_mouse_filter");
		HookManager.Submit({ 0x0050BB10 }, &preferences_get_invert_mouse, "preferences_get_invert_mouse");
		HookManager.Submit({ 0x0050DD70 }, &preferences_set_invert_mouse, "preferences_set_invert_mouse");
		HookManager.Submit({ 0x0050BB90 }, &preferences_get_mouse_sensitivity_horizontal, "preferences_get_mouse_sensitivity_horizontal");
		HookManager.Submit({ 0x0050DE00 }, &preferences_set_mouse_sensitivity_horizontal, "preferences_set_mouse_sensitivity_horizontal");
		HookManager.Submit({ 0x0050BC10 }, &preferences_get_mouse_sensitivity_vehicle_horizontal, "preferences_get_mouse_sensitivity_vehicle_horizontal");
		HookManager.Submit({ 0x0050DE90 }, &preferences_set_mouse_sensitivity_vehicle_horizontal, "preferences_set_mouse_sensitivity_vehicle_horizontal");
		HookManager.Submit({ 0x0050BC90 }, &preferences_get_mouse_sensitivity_vehicle_vertical, "preferences_get_mouse_sensitivity_vehicle_vertical");
		HookManager.Submit({ 0x0050DF20 }, &preferences_set_mouse_sensitivity_vehicle_vertical, "preferences_set_mouse_sensitivity_vehicle_vertical");
		HookManager.Submit({ 0x0050BD10 }, &preferences_get_mouse_sensitivity_vertical, "preferences_get_mouse_sensitivity_vertical");
		HookManager.Submit({ 0x0050DFB0 }, &preferences_set_mouse_sensitivity_vertical, "preferences_set_mouse_sensitivity_vertical");
		HookManager.Submit({ 0x0050BD90 }, &preferences_get_music_volume, "preferences_get_music_volume");
		HookManager.Submit({ 0x0050E040 }, &preferences_set_music_volume, "preferences_set_music_volume");
		HookManager.Submit({ 0x0050BE10 }, &preferences_get_postprocessing_quality, "preferences_get_postprocessing_quality");
		HookManager.Submit({ 0x0050E0D0 }, &preferences_set_postprocessing_quality, "preferences_set_postprocessing_quality");
		//HookManager.Submit({ 0x0050BFA0 }, &preferences_get_display_adapter, "preferences_get_display_adapter");
		//HookManager.Submit({ 0x0050E160 }, &preferences_set_display_adapter, "preferences_set_display_adapter");
		HookManager.Submit({ 0x0050C0D0 }, &preferences_get_sfx_volume, "preferences_get_sfx_volume");
		HookManager.Submit({ 0x0050E260 }, &preferences_set_sfx_volume, "preferences_set_sfx_volume");
		HookManager.Submit({ 0x0050C150 }, &preferences_get_shadow_quality, "preferences_get_shadow_quality");
		HookManager.Submit({ 0x0050E2F0 }, &preferences_set_shadow_quality, "preferences_set_shadow_quality");
		HookManager.Submit({ 0x0050C1D0 }, &preferences_get_display_subtitles, "preferences_get_display_subtitles");
		HookManager.Submit({ 0x0050E380 }, &preferences_set_display_subtitles, "preferences_set_display_subtitles");
		HookManager.Submit({ 0x0050C250 }, &preferences_get_player_marker, "preferences_get_player_marker");
		HookManager.Submit({ 0x0050E410 }, &preferences_set_player_marker, "preferences_set_player_marker");
		HookManager.Submit({ 0x0050C2D0 }, &preferences_get_texture_filtering_quality, "preferences_get_texture_filtering_quality");
		HookManager.Submit({ 0x0050E4A0 }, &preferences_set_texture_filtering_quality, "preferences_set_texture_filtering_quality");
		HookManager.Submit({ 0x0050C350 }, &preferences_get_texture_resolution, "preferences_get_texture_resolution");
		HookManager.Submit({ 0x0050E530 }, &preferences_set_texture_resolution, "preferences_set_texture_resolution");
		HookManager.Submit({ 0x0050C3D0 }, &preferences_get_toggle_crouch, "preferences_get_toggle_crouch");
		HookManager.Submit({ 0x0050E5C0 }, &preferences_set_toggle_crouch, "preferences_set_toggle_crouch");
		HookManager.Submit({ 0x0050B150 }, &preferences_get_effects_quality, "preferences_get_effects_quality");
		HookManager.Submit({ 0x0050D3D0 }, &preferences_set_effects_quality, "preferences_set_effects_quality");
		HookManager.Submit({ 0x0050B250 }, &preferences_get_fullscreen, "preferences_get_fullscreen");
		HookManager.Submit({ 0x0050D4F0 }, &preferences_set_fullscreen, "preferences_set_fullscreen");
		//HookManager.Submit({ 0x0050A9B0 }, &preferences_get_minor_version, "preferences_get_minor_version");
		//HookManager.Submit({ 0x0050CE90 }, &preferences_set_minor_version, "preferences_set_minor_version");
		//HookManager.Submit({ 0x0050AA30 }, &preferences_get_camera_fov, "preferences_get_camera_fov");
		//HookManager.Submit({ 0x0050CF20 }, &preferences_set_camera_fov, "preferences_set_camera_fov");
		HookManager.Submit({ 0x0050AAC0 }, &preferences_get_control_method, "preferences_get_control_method");
		HookManager.Submit({ 0x0050CFB0 }, &preferences_set_control_method, "preferences_set_control_method");
		//HookManager.Submit({ 0x0050AB40 }, &preferences_get_bindings, "preferences_get_bindings");
		//HookManager.Submit({ 0x0050D040 }, &preferences_set_bindings, "preferences_set_bindings");
		HookManager.Submit({ 0x0050AF50 }, &preferences_get_details_quality, "preferences_get_details_quality");
		HookManager.Submit({ 0x0050D190 }, &preferences_set_details_quality, "preferences_set_details_quality");
		HookManager.Submit({ 0x0050AFD0 }, &preferences_get_brightness, "preferences_get_brightness");
		HookManager.Submit({ 0x0050D220 }, &preferences_set_brightness, "preferences_set_brightness");
		HookManager.Submit({ 0x0050B050 }, &preferences_get_contrast, "preferences_get_contrast");
		HookManager.Submit({ 0x0050D2B0 }, &preferences_set_contrast, "preferences_set_contrast");
	}
}

void DisableSaberReflections()
{
	SetMemory<0x1917D62>(false);
}

inline void SubmitPreferencesPatches(const char *name)
{
	if (ConfigManager.GetBool("Patches", name))
	{
		PatchManager.Submit(&DisableSaberReflections, "DisableSaberReflections");
	}
}

void AllQualitySettingsToggleLock()
{
	preferences.TextureResolution.toggle_lock();
	preferences.TextureFilteringQuality.toggle_lock();
	preferences.LightingQuality.toggle_lock();
	preferences.EffectsQuality.toggle_lock();
	preferences.ShadowQuality.toggle_lock();
	preferences.DetailsQuality.toggle_lock();
}

void SetAllQualitySettingsLow()
{
	AllQualitySettingsToggleLock();
	preferences.TextureResolution.set({ e_quality_option::_low });
	preferences.TextureFilteringQuality.set({ e_quality_option::_low });
	preferences.LightingQuality.set({ e_quality_option::_low });
	preferences.EffectsQuality.set({ e_quality_option::_low });
	preferences.ShadowQuality.set({ e_quality_option::_low });
	preferences.DetailsQuality.set({ e_quality_option::_low });
	AllQualitySettingsToggleLock();
}

void SetAllQualitySettingsMedium()
{
	AllQualitySettingsToggleLock();
	preferences.TextureResolution.set({ e_quality_option::_medium });
	preferences.TextureFilteringQuality.set({ e_quality_option::_medium });
	preferences.LightingQuality.set({ e_quality_option::_medium });
	preferences.EffectsQuality.set({ e_quality_option::_medium });
	preferences.ShadowQuality.set({ e_quality_option::_medium });
	preferences.DetailsQuality.set({ e_quality_option::_medium });
	AllQualitySettingsToggleLock();
}

void SetAllQualitySettingsHigh()
{
	AllQualitySettingsToggleLock();
	preferences.TextureResolution.set({ e_quality_option::_high });
	preferences.TextureFilteringQuality.set({ e_quality_option::_high });
	preferences.LightingQuality.set({ e_quality_option::_high });
	preferences.EffectsQuality.set({ e_quality_option::_high });
	preferences.ShadowQuality.set({ e_quality_option::_high });
	preferences.DetailsQuality.set({ e_quality_option::_high });
	AllQualitySettingsToggleLock();
}