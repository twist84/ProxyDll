#pragma once
#include <iostream>

#include "../utils/Utils.hpp"

#include "../memory/local_types.hpp"

static auto sub_4EC4C0 = (wchar_t(__thiscall*)(wchar_t *Src, const char *file_path))(0x4EC4C0);
static auto sub_528410 = (int(__cdecl *)(s_file_reference *filo, const char *file_path))(0x528410);
static auto sub_5288B0 = (s_file_reference *(__cdecl *)(s_file_reference *filo, wchar_t *Src))(0x5288B0);
static auto sub_5294F0 = (void(__cdecl *)(const char *ArgList, s_file_reference *a2, s_file_reference *a3, char a4))(0x5294F0);


s_file_reference *__cdecl file_reference_initialize_header_hook(s_file_reference *filo, uint16_t a2)
{
	memset(filo, 0, 0x110u);
	filo->header_type = 'filo';
	filo->unknown6 = a2;

	return filo;
}
s_file_reference *__cdecl file_reference_initialize_hook(s_file_reference *filo, uint16_t a2)
{
	file_reference_initialize_header_hook(filo, a2);
	filo->file_handle = (HANDLE)-1;

	return filo;
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
		sub_4EC4C0(Src, file_path);
		sub_5288B0(filo, Src);
	}

	//printf_s("filo_create: %s\n", filo->path);
	return filo;
}

char __cdecl file_read_hook(s_file_reference *filo, DWORD nNumberOfBytesToRead, char a3, LPVOID lpBuffer)
{
	DWORD v4 = nNumberOfBytesToRead;
	if (!nNumberOfBytesToRead)
		return true;
	DWORD v6 = nNumberOfBytesToRead;
	nNumberOfBytesToRead = 0;
	char result = false;
	if (ReadFile(filo->file_handle, lpBuffer, v6, &nNumberOfBytesToRead, 0))
	{
		if (nNumberOfBytesToRead == v4)
			result = true;
		else
			SetLastError(0x26u);
	}
	filo->file_pointer += nNumberOfBytesToRead;
	if (!result)
		sub_5294F0("file_read", filo, 0, a3);

	//printf_s("file_read: %s\n", filo->path);
	return result;
}

char __cdecl file_close_hook(s_file_reference *filo)
{
	//printf_s("file_close: %s\n", filo->path);
	bool result;
	if (CloseHandle(filo->file_handle))
	{
		filo->file_handle = (HANDLE)-1;
		filo->file_pointer = 0;
		result = true;
	}
	else
	{
		SetLastError(0);
		result = false;
	}
	return result;
}

bool __cdecl file_set_position_hook(s_file_reference *filo, LONG lDistanceToMove, char a3)
{
	if (filo->file_pointer == lDistanceToMove)
		return 1;
	void *file_handle = filo->file_handle;
	LONG DistanceToMoveHigh = 0;
	uint32_t file_pointer = SetFilePointer(file_handle, lDistanceToMove, &DistanceToMoveHigh, 0);
	bool file_pointer_is_valid = file_pointer != -1;
	filo->file_pointer = file_pointer;
	if (file_pointer == -1)
		sub_5294F0("file_set_position", filo, 0, a3);

	//printf_s("file_set_position: %s\n", filo->path);
	return file_pointer_is_valid;
}

static const auto file_create_parent_directories_if_not_present = (bool(__cdecl *)(s_file_reference *))0x527FF0;
static const auto file_reference_create_from_path = (s_file_reference *(__cdecl *)(s_file_reference *, const wchar_t *, bool))0x5285B0;
static const auto file_close = (bool(__cdecl *)(s_file_reference *))0x528B60;
static const auto file_create = (bool(__cdecl *)(s_file_reference *))0x528FB0;
static const auto file_exists = (bool(__cdecl *)(s_file_reference *))0x5295F0;
static const auto file_open = (bool(__cdecl *)(s_file_reference *, int, int *))0x52A220;
static const auto file_read = (bool(__cdecl *)(s_file_reference *, int, char, LPVOID))0x52A7E0;
static const auto file_write = (bool(__cdecl *)(s_file_reference *, int, LPCVOID))0x52B250;

inline void AddFiloHooks(const char *name)
{
	if (ConfigManager.GetBool("Hooks", name))
	{
		AddHook({ 0x12A5F0 }, &file_get_folder_path_hook, "file_get_folder_path");

		AddHook({ 0x128500 }, &file_reference_initialize_header_hook, "file_reference_initialize_header");
		AddHook({ 0x12A9A0 }, &file_reference_initialize_hook, "file_reference_initialize");

		AddHook({ 0x128550 }, &filo_create_hook, "filo_create");
		AddHook({ 0x12A7E0 }, &file_read_hook, "file_read");
		AddHook({ 0x128B60 }, &file_close_hook, "file_close");
		AddHook({ 0x12B060 }, &file_set_position_hook, "file_set_position");
	}
}

inline void AddFiloPatches(const char *name)
{
	if (ConfigManager.GetBool("Patches", name))
	{

	}
}