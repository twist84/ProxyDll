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

void __fastcall c_gui_network_mode_category_datasource_vftable01_hook(void *thisptr, void *unused, uint8_t *a2)
{
	auto c_gui_network_mode_selected_item_create_category = (int(__thiscall *)(void *, int, int, int, int, char))0xB23870;
	if (g_vftables.at(0x0169DA04).GetMember<char(__thiscall *)(void *, uint8_t *)>(1)(thisptr, a2))
	{
		c_gui_network_mode_selected_item_create_category(thisptr, 0x103B3, 0x103B4, 0, 5, 1);	// network_mode_xbox_live_private, description
		c_gui_network_mode_selected_item_create_category(thisptr, 0x103B5, 0x103B6, 1, 5, 1);	// network_mode_system_link, description
		c_gui_network_mode_selected_item_create_category(thisptr, 0x103B7, 0x103B8, 2, 5, 0);	// network_mode_offline, description
	}
}

void __fastcall c_gui_network_mode_subitem_selectable_item_datasource_vftable28_hook(void *thisptr, void *unused, uint8_t *a2, int a3)
{
	auto c_gui_network_mode_selected_item_create_subitem = (int(__thiscall *)(void *, int, int, int a4, int a5))0xB23970;
	if (g_vftables.at(0x0169DA04).GetMember<char(__thiscall *)(void *, uint8_t *)>(1)(thisptr, a2))
	{
		if (a3)
		{
			if (a3 == 1)
			{
				c_gui_network_mode_selected_item_create_subitem(thisptr, 0x103C1, 0x103C2, 1, 3);	// network_mode_system_link_advertise, description
				c_gui_network_mode_selected_item_create_subitem(thisptr, 0x103C3, 0x103C4, 1, 4);	// network_mode_system_link_browse, description
			}
		}
		else
		{
			c_gui_network_mode_selected_item_create_subitem(thisptr, 0x103B9, 0x103BA, 0, 0);		// network_mode_xbox_live_advertise_anyone, description
			if (!((bool(__cdecl *)())0xA84120)())
				c_gui_network_mode_selected_item_create_subitem(thisptr, 0x103BB, 0x103BC, 0, 1);	// network_mode_xbox_live_advertise_friends, description
			c_gui_network_mode_selected_item_create_subitem(thisptr, 0x103BD, 0x103BE, 0, 2);		// network_mode_xbox_live_advertise_invite_only, description
		}
	}
}

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

	return SetMemory<0x189DEE4>(result);
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

struct s_ssl_hq
{
	int chat_send_clan(wchar_t *source)
	{
		return printf_s("#clan_%S\n", source);
	}
	int chat_send_game_all(wchar_t *source)
	{
		return printf_s("#game_%S\n", source);
	}
	int chat_send_gameteam(wchar_t *source)
	{
		return printf_s("#gameteam_%S\n", source);
	}
	int chat_send_general(wchar_t *source)
	{
		return printf_s("#general_%S\n", source);
	}
	int chat_send_party(wchar_t *source)
	{
		return printf_s("#party_%S\n", source);
	}
	int chat_send_private(wchar_t *source)
	{
		return printf_s("#private_%S\n", source);
	}
} ssl_hq;

// use this as a console for commands maybe?
// TODO: figure out why the box is hidden until you open settings, probably due to ElDewrito

void __cdecl ssl_hq__chat_send_clan_hook(wchar_t *source)
{
	ssl_hq.chat_send_clan(source);
}
void __cdecl ssl_hq__chat_send_game_all_hook(wchar_t *source)
{
	ssl_hq.chat_send_game_all(source);
}
void __cdecl ssl_hq__chat_send_gameteam_hook(wchar_t *source)
{
	ssl_hq.chat_send_gameteam(source);
}
void __cdecl ssl_hq__chat_send_general_hook(wchar_t *source)
{
	ssl_hq.chat_send_general(source);
}
void __cdecl ssl_hq__chat_send_party_hook(wchar_t *source)
{
	ssl_hq.chat_send_party(source);
}
void __cdecl ssl_hq__chat_send_private_hook(wchar_t *source)
{
	ssl_hq.chat_send_private(source);
}

inline void SubmitUiHooks(const char *name)
{
	if (ConfigManager.GetBool("Hooks", name))
	{
		//HookManager.Submit({ 0x6B8AE0 }, &UI_Widget_FindChildText_hook, "UI_Widget_FindChildText");
		//HookManager.Submit({ 0x6B8A40 }, &UI_Widget_FindChildBitmap_hook, "UI_Widget_FindChildBitmap");
		//HookManager.Submit({ 0x6B8AC0 }, &UI_Widget_FindChildField2_hook, "UI_Widget_FindChildField2");
		//HookManager.Submit({ 0x6B8A60 }, &UI_Widget_FindChildField3_hook, "UI_Widget_FindChildField3");
		//HookManager.Submit({ 0x6B8A80 }, &UI_Widget_FindChildField5_hook, "UI_Widget_FindChildField5");
		//HookManager.Submit({ 0x6B8AA0 }, &UI_Widget_FindChildData_hook, "UI_Widget_FindChildData");

		//HookManager.Submit({ 0x6B2830 }, &UI_ScreenWidget_Close_hook, "UI_ScreenWidget_Close");

		//HookManager.Submit({ 0x6B872A }, &sub_AB9360_hook, "sub_AB9360", HookFlags::IsCall);

		//HookManager.Submit({ 0x6BCF40 }, &c_user_interface_text__sub_ABCF40_hook, "c_user_interface_text::sub_ABCF40");

		//HookManager.Submit({ 0x6C3F6F }, &c_gui_widget__vftable24_hook, "c_gui_widget::vftable24", HookFlags::IsCall);

		HookManager.Submit({ 0x6B4ED0 }, &UI_Alloc_hook, "UI_Alloc");
		HookManager.Submit({ 0x6A8F63 }, &interface__gui_screens__start_menu__panes__game_multiplayer_hook, "interface::gui_screens::start_menu::panes::game_multiplayer", HookFlags::IsCall);

		HookManager.Submit({ 0x70CEA0 }, &c_magic_string_game_tag__current_name_hook, "c_magic_string_game_tag::current_name");
		HookManager.Submit({ 0x70CEC0 }, &c_magic_string_game_tag__current_value_hook, "c_magic_string_game_tag::current_value");

		//HookManager.Submit({ 0x6E98E4 }, &c_magic_string_game_tag_parser_hook, "c_magic_string_game_tag_parser", HookFlags::IsCall);

		HookManager.Submit({ 0x12EBC0 }, &get_loading_text_hook, "get_loading_text");
		HookManager.Submit({ 0x12FC40 }, &system_default_ui_language_to_game_language_hook, "system_default_ui_language_to_game_language");
		HookManager.Submit({ 0x12FFD0 }, &game_get_region_hook, "game_get_region");
		
		HookManager.Submit({ 0x12F930 }, &main_game_render_get_loading_type_hook, "main_game_render_get_loading_type");
		HookManager.Submit({ 0x620540 }, &debug_print_lobby_percent_loaded_hook, "debug_print_lobby_percent_loaded");
		HookManager.Submit({ 0x620530 }, &debug_cache_loading_callback_hook, "debug_cache_loading_callback");

		HookManager.Submit(render_to_texture_offsets, &render_to_texture_hook, "render_to_texture", HookFlags::IsCall);

		HookManager.Submit({ 0x42ED40 }, &ssl_hq__chat_send_clan_hook, "ssl_hq::chat_send_clan");
		HookManager.Submit({ 0x42F0A0 }, &ssl_hq__chat_send_game_all_hook, "ssl_hq::chat_send_game_all");
		HookManager.Submit({ 0x42F470 }, &ssl_hq__chat_send_gameteam_hook, "ssl_hq::chat_send_gameteam");
		HookManager.Submit({ 0x42F880 }, &ssl_hq__chat_send_general_hook, "ssl_hq::chat_send_general");
		HookManager.Submit({ 0x42FBD0 }, &ssl_hq__chat_send_party_hook, "ssl_hq::chat_send_party");
		HookManager.Submit({ 0x42FFA0 }, &ssl_hq__chat_send_private_hook, "ssl_hq::chat_send_private");
	}
}

void unblock_campaign_lobby_ui_patch()
{
	Patch(0x7004DF, { 0xEB }).Apply();
}

bool c_gui_network_mode_xbl_enabled = true;
void network_menu_patch()
{
	if (c_gui_network_mode_xbl_enabled)
	{
		g_vftables.at(0x016A73B4).ReplaceMember(01, &c_gui_network_mode_category_datasource_vftable01_hook);
		g_vftables.at(0x016A742C).ReplaceMember(28, &c_gui_network_mode_subitem_selectable_item_datasource_vftable28_hook);
	}
}

inline void SubmitUiPatches(const char *name)
{
	if (ConfigManager.GetBool("Patches", name))
	{
		PatchManager.Submit(&unblock_campaign_lobby_ui_patch, "unblock_campaign_lobby_ui");
		PatchManager.Submit(&network_menu_patch, "network_menu");
	}
}