#pragma once
#include <iostream>

#include <Utils.hpp>

#include "../memory/local_types.hpp"

static auto char_string_to_wchar_string = (wchar_t(__thiscall*)(wchar_t *Src, const char *file_path))(0x4EC4C0);
static auto sub_528410 = (int(__cdecl *)(s_file_reference *filo, const char *file_path))(0x528410);
static auto file_path_add_name = (s_file_reference *(__cdecl *)(s_file_reference *filo, wchar_t *Src))(0x5288B0);
static auto sub_5294F0 = (void(__cdecl *)(const char *ArgList, s_file_reference *a2, s_file_reference *a3, char a4))(0x5294F0);

s_file_reference *__cdecl file_reference_initialize_header_hook(s_file_reference *filo, uint16_t a2)
{
	return filo->initialize_header(a2);
}
s_file_reference *__cdecl file_reference_initialize_hook(s_file_reference *filo, uint16_t a2)
{
	return filo->initialize(a2);
}

int __cdecl file_get_folder_path_hook(wchar_t *file_path)
{
	size_t file_path_len = wcslen(file_path);
	if (file_path_len > 0)
	{
		do
		{
			if (file_path[file_path_len] == '\\')
				break;
			file_path_len--;
		} while (file_path_len > '\0');
	}
	file_path_len = file_path_len;
	file_path[file_path_len] = '\0';
	return file_path_len;
}

void *__cdecl filo_create_hook(s_file_reference *filo, const char *file_path, bool a3)
{
	wchar_t Src[256];
	file_reference_initialize_hook(filo, (uint16_t)-1);
	if (a3)
	{
		sub_528410(filo, file_path);
	}
	else
	{
		char_string_to_wchar_string(Src, file_path);
		file_path_add_name(filo, Src);
	}

	filo->Print("filo_create");
	return filo;
}
char __cdecl file_read_hook(s_file_reference *filo, DWORD nNumberOfBytesToRead, char a3, LPVOID lpBuffer)
{
	return filo->Print("file_read")->read(nNumberOfBytesToRead, a3, lpBuffer, (void(__cdecl*)(const char*, s_file_reference*, s_file_reference*, char))(0x5294F0));
}
char __cdecl file_close_hook(s_file_reference *filo)
{
	return filo->Print("file_close")->close();
}
bool __cdecl file_set_position_hook(s_file_reference *filo, LONG lDistanceToMove, char a3)
{
	return filo->Print("file_set_position")->set_position(lDistanceToMove, a3, (void(__cdecl*)(const char*, s_file_reference*, s_file_reference*, char))(0x5294F0));
}
char __cdecl file_write_hook(s_file_reference *filo, DWORD nNumberOfBytesToWrite, LPCVOID lpBuffer)
{
	return filo->Print("file_write")->write(nNumberOfBytesToWrite, lpBuffer, (void(__cdecl*)(const char*, s_file_reference*, s_file_reference*, char))(0x5294F0));
}
int __cdecl filo_get_file_pointer_hook(s_file_reference *filo)
{
	return filo->Print("filo_get_file_pointer")->FilePointer;
}

int __cdecl file_get_eof_hook(s_file_reference *filo)
{
	return filo->Print("file_get_eof")->get_eof((void(__cdecl*)(const char*, s_file_reference *, s_file_reference *, char))(0x5294F0));
}

static const auto file_create_parent_directories_if_not_present = (bool(__cdecl *)(s_file_reference *))0x527FF0;
static const auto file_reference_create_from_path = (s_file_reference *(__cdecl *)(s_file_reference *, const wchar_t *, bool))0x5285B0;
static const auto file_close = (bool(__cdecl *)(s_file_reference *))0x528B60;
static const auto file_create = (bool(__cdecl *)(s_file_reference *))0x528FB0;
static const auto file_exists = (bool(__cdecl *)(s_file_reference *))0x5295F0;
static const auto file_open = (bool(__cdecl *)(s_file_reference *, int, int *))0x52A220;
static const auto file_read = (bool(__cdecl *)(s_file_reference *, int, char, LPVOID))0x52A7E0;
static const auto file_write = (bool(__cdecl *)(s_file_reference *, int, LPCVOID))0x52B250;

inline void SubmitFiloHooks(const char *name)
{
	if (ConfigManager.GetBool("Hooks", name))
	{
		HookManager.Submit({ 0x12A5F0 }, &file_get_folder_path_hook, "file_get_folder_path");

		HookManager.Submit({ 0x128500 }, &file_reference_initialize_header_hook, "file_reference_initialize_header");
		HookManager.Submit({ 0x12A9A0 }, &file_reference_initialize_hook, "file_reference_initialize");

		HookManager.Submit({ 0x128550 }, &filo_create_hook, "filo_create");
		HookManager.Submit({ 0x12A7E0 }, &file_read_hook, "file_read");
		HookManager.Submit({ 0x128B60 }, &file_close_hook, "file_close");
		HookManager.Submit({ 0x1298C0 }, &file_get_eof_hook, "file_get_eof");
		HookManager.Submit({ 0x129AF0 }, &filo_get_file_pointer_hook, "filo_get_file_pointer");
		HookManager.Submit({ 0x12B060 }, &file_set_position_hook, "file_set_position");
		HookManager.Submit({ 0x12B250 }, &file_write_hook, "file_write");
	}
}

inline void SubmitFiloPatches(const char *name)
{
	if (ConfigManager.GetBool("Patches", name))
	{

	}
}