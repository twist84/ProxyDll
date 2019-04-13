#pragma once
#include <iostream>

#include "../utils/Utils.hpp"

#include "../memory/local_types.hpp"

const wchar_t *get_loading_text_hook()
{
	return (*(e_game_language *)0x129C194).GetLoadingText();
}

int __cdecl system_default_ui_language_to_game_language_hook()
{
	auto result = *(int *)0x129C194;
	//if (*(int *)0x129C194 == -1)
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

	return *(int *)0x129C194 = result;
}

const char *game_get_region_hook(e_game_language game_language, bool foreign)
{
	printf_s("game_region: %s\n", game_language.GetRegion());
	return game_language.GetRegion();
}

void draw_watermark_hook() {}

inline void AddUiHooks(const char *name)
{
	if (ConfigManager.GetBool("Hooks", name))
	{
		AddHook({ 0xC2C30 }, &get_loading_text_hook, "get_loading_text");
		AddHook({ 0xB0C00 }, &system_default_ui_language_to_game_language_hook, "system_default_ui_language_to_game_language");
		AddHook({ 0xB0CE0 }, &game_get_region_hook, "game_get_region");
	}
}

void language_patch()
{
	Patch(0x2B9231, { (uint8_t)e_game_language(g_new_system_ui_language).value }).Apply(g_use_default_system_ui_language);
	Patch(0x2B923A, { (uint8_t)e_game_language(g_new_system_ui_language).value }).Apply(g_use_default_system_ui_language);
}

inline void AddUiPatches(const char *name)
{
	if (ConfigManager.GetBool("Patches", name))
	{
		AddPatch(&language_patch, "language");
	}
}