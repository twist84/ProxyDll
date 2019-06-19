#pragma once
#include <iostream>

#include <Utils.hpp>

#include "../memory/local_types.hpp"

#include "print.hpp"

uint32_t *__fastcall UI_Widget_FindChild(uint32_t *thisptr, int a1, string_id a2)
{
	//print_vftable(thisptr, a2, true);
	return ((uint32_t *(__thiscall *)(uint32_t *, int, string_id))0xAB8B00)(thisptr, a1, a2);
}

uint32_t *__fastcall UI_Widget_FindChildText_hook(uint32_t *thisptr, void *unused, string_id a2)
{
	auto result = UI_Widget_FindChild(thisptr, 0, a2);
	//print_vftable(result);
	return result;
}

uint32_t *__fastcall UI_Widget_FindChildBitmap_hook(uint32_t *thisptr, void *unused, string_id a2)
{
	return UI_Widget_FindChild(thisptr, 1, a2);
}

uint32_t *__fastcall UI_Widget_FindChildField2_hook(uint32_t *thisptr, void *unused, string_id a2)
{
	return UI_Widget_FindChild(thisptr, 2, a2);
}

uint32_t *__fastcall UI_Widget_FindChildField3_hook(uint32_t *thisptr, void *unused, string_id a2)
{
	return UI_Widget_FindChild(thisptr, 3, a2);
}

uint32_t *__fastcall UI_Widget_FindChildField5_hook(uint32_t *thisptr, void *unused, string_id a2)
{
	return UI_Widget_FindChild(thisptr, 5, a2);
}

uint32_t *__fastcall UI_Widget_FindChildData_hook(uint32_t *thisptr, void *unused, string_id a2)
{
	return UI_Widget_FindChild(thisptr, 7, a2);
}

int __fastcall UI_ScreenWidget_Close_hook(uint32_t *thisptr, void*, int a2)
{
	//print_vftable(thisptr);
	return (*(int(__stdcall **)(int, signed int))(*(uint32_t *)thisptr + 0xD0))(a2, 1);
}

uint32_t *__fastcall sub_AB9360_hook(uint32_t *thisptr)
{
	//print_vftable(thisptr);
	return ((uint32_t *(__thiscall *)(uint32_t *))0xAB9360)(thisptr);
}

void __fastcall c_user_interface_text__sub_ABCF40_hook(uint32_t *thisptr)
{
	//print_vftable(thisptr);
	*thisptr = *(uint32_t *)0x169CAC8;
}

char __fastcall c_gui_widget__vftable24_hook(uint32_t *thisptr, int a2)
{
	//printf_s("c_gui_widget::vftable24 called\n");
	return ((char(__thiscall *)(uint32_t *, int))0xABB070)(thisptr, a2);
}

uint32_t *__cdecl UI_Alloc_hook(uint32_t size_allocation)
{
	auto result = ((uint32_t *(__cdecl *)(uint32_t, uint32_t, uint32_t))0xAB4EF0)(size_allocation, 0, 0);

	//printf_s("UI_Alloc: size allocation = 0x%X\n", size_allocation);
	//print_vftable(result);
	return result;
}

uint32_t *__fastcall interface__gui_screens__start_menu__panes__game_multiplayer_hook(uint32_t *ui_alloc_result, string_id stringid)
{
	//auto result = ((uint32_t *(__thiscall *)(uint32_t *, string_id))0xAE9080)(ui_alloc_result, stringid);
	printf_s("%s -> %s\n", stringid.GetName(), (*(string_id *)0x10085).GetName());

	auto ui_alloc = UI_Alloc_hook(0x2168);
	return ((uint32_t *(__thiscall *)(uint32_t *, string_id))0xAE86E0)(ui_alloc, *(string_id *)0x10085);
}

auto c_magic_string_game_tag__current = ((char(__cdecl *)(int a1, int arg4, wchar_t *DstBuf, int size_in_bytes))0xB0CDB0);

char __cdecl c_magic_string_game_tag__current_name_hook(int a1, wchar_t *DstBuf, int a3)
{
	auto result = c_magic_string_game_tag__current(a1, 0x2AA, DstBuf, a3);

	//printf_s("%ls\n", DstBuf);
	return result;
}

char __cdecl c_magic_string_game_tag__current_value_hook(int a1, wchar_t *DstBuf, int a3)
{
	auto result = c_magic_string_game_tag__current(a1, 0x111, DstBuf, a3);

	//printf_s("%ls\n", DstBuf);
	return result;
}

auto c_magic_string_game_tag_parser = ((uint32_t *(__thiscall *)(uint32_t *, uint32_t *, uint32_t, uint32_t *))0xAA64C0);
uint32_t *__fastcall c_magic_string_game_tag_parser_hook(uint32_t *thisptr, uint32_t *magic_string_game_tag, uint32_t a3, uint32_t *a4)
{
	printf_s("%ls\n", (wchar_t *)magic_string_game_tag);	
	return c_magic_string_game_tag_parser(thisptr, magic_string_game_tag, a3, a4);
}

//.text:00AD52F0 ; char __thiscall c_gui_data::vftable01::player_select_actions(c_gui_game_variant_category_datasource *this, int a2)
//.text:00B23870 ; int __thiscall c_gui_network_mode_selected_item::create_category(c_gui_game_variant_category_datasource *this, string_id network_mode_name, string_id network_mode_description, int line_pos, int a5, char a6)
//.text:00B23D70 ; char __thiscall c_gui_network_mode_category_datasource::vftable01::player_select_actions(c_gui_game_variant_category_datasource *this, int a2)

// this crashes if the vftable member is changed, even if I given member points to the exact same memory address
void __fastcall c_gui_network_mode_category_datasource_vftable01_player_select_actions_hook(void *thisptr, void *unused, uint8_t *a2)
{
	auto c_gui_network_mode_selected_item_create_category = (int(__thiscall *)(void *, int, int, int, int, char))0xB23870;

	bool xbox_live_private_enabled = false;
	if (VftableGetMember<char(__thiscall *)(void *, uint8_t *)>((DWORD_PTR*)0x169DA04, 1)(thisptr, a2))
	{
		if (xbox_live_private_enabled)
			c_gui_network_mode_selected_item_create_category(thisptr, 0x103B3, 0x103B4, 0, 5, 1);								 // network_mode_xbox_live_private, network_mode_xbox_live_private_description
		c_gui_network_mode_selected_item_create_category(thisptr, 0x103B5, 0x103B6, xbox_live_private_enabled ? 1 : 0, 5, 1);	 // network_mode_system_link,		network_mode_system_link_description
		c_gui_network_mode_selected_item_create_category(thisptr, 0x103B7, 0x103B8, xbox_live_private_enabled ? 2 : 1, 5, 0);	 // network_mode_offline,			network_mode_offline_description
	}
}

// the above hook replaces the following ED patches
/*
		// Remove Xbox Live from the network menu
		Patch::NopFill(Pointer::Base(0x723D85), 0x17);
		Pointer::Base(0x723DA1).Write<uint8_t>(0);
		Pointer::Base(0x723DB8).Write<uint8_t>(1);
*/
// I'd like the add these as a replacement hook like the above one
/*
		Patch::NopFill(Pointer::Base(0x723DFF), 0x3);
		Pointer::Base(0x723E07).Write<uint8_t>(0);
		Pointer::Base(0x723E1C).Write<uint8_t>(0);
*/

const wchar_t *get_loading_text_hook()
{
	return (*(e_game_language *)0x189DEE4).Print()->GetLoadingText();
	//return (*(e_game_language *)0x12E71B4).GetLoadingText();
}

int __cdecl system_default_ui_language_to_game_language_hook()
{
	auto result = *(int *)0x189DEE4;
	//if (*(int *)0x12E71B4 == -1)
	//{
	switch (g_use_default_system_ui_language ? GetSystemDefaultUILanguage() : g_new_system_ui_language)
	{
	case LANG_CHINESE:
		result = e_game_language::_chinese_simplified;
		break;
	case LANG_GERMAN:
		result = e_game_language::_german;
		break;
	case LANG_SPANISH:
		result = e_game_language::_spanish;
		break;
	case LANG_FRENCH:
		result = e_game_language::_french;
		break;
	case LANG_ITALIAN:
		result = e_game_language::_italian;
		break;
	case LANG_JAPANESE:
		result = e_game_language::_japanese;
		break;
	case LANG_KOREAN:
		result = e_game_language::_korean;
		break;
	case LANG_PORTUGUESE:
		result = e_game_language::_portuguese;
		break;
	case LANG_RUSSIAN:
		result = e_game_language::_russian;
		break;
	default:
		result = e_game_language::_english;
		break;
	}
	//}

	return *(int *)0x189DEE4 = result;
	//return *(int *)0x12E71B4 = result;
}

const char *game_get_region_hook(e_game_language game_language, bool foreign)
{
	printf_s("game_region: %s\n", game_language.GetRegion());
	return game_language.GetRegion();
}

int debug_loading_type = 3;

void update_debug_loading_type()
{
	debug_loading_type = ConfigManager.GetInt("Rendering", "DebugLoadingType");
}

int __cdecl debug_print_lobby_percent_loaded_hook(float a1) // nullsub
{
	int result = 0;
	if (debug_loading_type == 8 && 100 - a1 > 0.1f)
		result = printf_s("loaded: %d\n", (int)(100 - a1));
	return result;
}
int __cdecl debug_cache_loading_callback_hook() // nullsub
{
	int result = 0;
	if (debug_loading_type == 8)
		result = printf_s("loading!\n");
	return result;
}

signed int __cdecl main_game_render_get_loading_type_hook(wchar_t *a1)
{
	/*
	main::main_render::loading_screen
		0,		exit loading render function
		2,		goto endscene
		3,		render `hf2p_loading_screen`
		8,		render 'debug_print_lobby_percent_loaded'
	main::main_render::bink
		1,		execute some bink related functions, `main::main_render::begin` calls `main::main_render::bink` with 1
		4, 5,	execute (draw_string, nullsub and content_catalogue related) functions
	*/
	return debug_loading_type;
}

std::vector<size_t> render_to_texture_offsets = { 0x3ABEF5, 0x3AC405, 0x3AC425, 0x3AC445, 0x3AC465, 0x3AC485, 0x3B4E7B, 0x3B5D0B, 0x3B5D4B, 0x3B5D6B, 0x3B5D8B, 0x3B5DAB, 0x3B5DCB, 0x3B7AE6, 0x3B7AEF, 0x3B7AF8, 0x3B7B01, 0x3B7B0A };
int __cdecl render_to_texture_hook(int a1, int a2, int a3)
{
	//0 == _biped_profile
	//1 == _biped_class_selection
	//2 == _biped_lobby_left
	//3 == _biped_lobby_right
	//4 == _biped_killer
	//5 == _biped_scoreboard

	if (a1 == 5)
		printf("scoreboard opened\n");
	return ((int(__cdecl*)(int, int, int))0x835DA0)(a1, a2, a3);
}

void __cdecl ssl_hq__chat_send_general_hook(wchar_t *source)
{
	// use this as a console for commands maybe?
	// TODO: figure out why the box is hidden until you open settings, probably due to ElDewrito

	wprintf_s(L"#general_%s\n", source);
}

inline void AddUiHooks(const char *name)
{
	if (ConfigManager.GetBool("Hooks", name))
	{
		//HookManager.AddHook({ 0x6B8AE0 }, &UI_Widget_FindChildText_hook, "UI_Widget_FindChildText");
		//HookManager.AddHook({ 0x6B8A40 }, &UI_Widget_FindChildBitmap_hook, "UI_Widget_FindChildBitmap");
		//HookManager.AddHook({ 0x6B8AC0 }, &UI_Widget_FindChildField2_hook, "UI_Widget_FindChildField2");
		//HookManager.AddHook({ 0x6B8A60 }, &UI_Widget_FindChildField3_hook, "UI_Widget_FindChildField3");
		//HookManager.AddHook({ 0x6B8A80 }, &UI_Widget_FindChildField5_hook, "UI_Widget_FindChildField5");
		//HookManager.AddHook({ 0x6B8AA0 }, &UI_Widget_FindChildData_hook, "UI_Widget_FindChildData");

		//HookManager.AddHook({ 0x6B2830 }, &UI_ScreenWidget_Close_hook, "UI_ScreenWidget_Close");

		//HookManager.AddHook({ 0x6B872A }, &sub_AB9360_hook, "sub_AB9360", HookFlags::IsCall);

		//HookManager.AddHook({ 0x6BCF40 }, &c_user_interface_text__sub_ABCF40_hook, "c_user_interface_text::sub_ABCF40");

		//HookManager.AddHook({ 0x6C3F6F }, &c_gui_widget__vftable24_hook, "c_gui_widget::vftable24", HookFlags::IsCall);

		HookManager.AddHook({ 0x6B4ED0 }, &UI_Alloc_hook, "UI_Alloc");
		HookManager.AddHook({ 0x6A8F63 }, &interface__gui_screens__start_menu__panes__game_multiplayer_hook, "interface::gui_screens::start_menu::panes::game_multiplayer", HookFlags::IsCall);

		HookManager.AddHook({ 0x70CEA0 }, &c_magic_string_game_tag__current_name_hook, "c_magic_string_game_tag::current_name");
		HookManager.AddHook({ 0x70CEC0 }, &c_magic_string_game_tag__current_value_hook, "c_magic_string_game_tag::current_value");

		//HookManager.AddHook({ 0x6E98E4 }, &c_magic_string_game_tag_parser_hook, "c_magic_string_game_tag_parser", HookFlags::IsCall);

		//HookManager.AddVftHook(0x16A73B4, &c_gui_network_mode_category_datasource_vftable01_player_select_actions_hook, 1, "c_gui_network_mode_category_datasource::vftable::player_select_actions");

		HookManager.AddHook({ 0x12EBC0 }, &get_loading_text_hook, "get_loading_text");
		HookManager.AddHook({ 0x12FC40 }, &system_default_ui_language_to_game_language_hook, "system_default_ui_language_to_game_language");
		HookManager.AddHook({ 0x12FFD0 }, &game_get_region_hook, "game_get_region");
		
		HookManager.AddHook({ 0x12F930 }, &main_game_render_get_loading_type_hook, "main_game_render_get_loading_type");
		HookManager.AddHook({ 0x620540 }, &debug_print_lobby_percent_loaded_hook, "debug_print_lobby_percent_loaded");
		HookManager.AddHook({ 0x620530 }, &debug_cache_loading_callback_hook, "debug_cache_loading_callback");

		HookManager.AddHook(render_to_texture_offsets, &render_to_texture_hook, "render_to_texture", HookFlags::IsCall);

		HookManager.AddHook({ 0x42F880 }, &ssl_hq__chat_send_general_hook, "ssl_hq::chat_send_general");
	}
}

void unblock_campaign_lobby_ui_patch()
{
	Patch(0x7004DF, { 0xEB }).Apply();
}

inline void AddUiPatches(const char *name)
{
	if (ConfigManager.GetBool("Patches", name))
	{
		PatchManager.AddPatch(&unblock_campaign_lobby_ui_patch, "unblock_campaign_lobby_ui");
	}
}