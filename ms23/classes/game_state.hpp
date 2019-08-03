#pragma once
#include <Utils.hpp>

#include "../memory/local_types.hpp"

#include "filo.hpp"

static const auto game_state_buffer_handle_read = (int(*)())0x50F280;

bool __cdecl file_read_from_path(const wchar_t *path, DWORD size, LPVOID buffer)
{
	s_file_reference file;
	file_reference_create_from_path(&file, path, false);

	int file_error;
	if (!file_open(&file, 1, &file_error))
	{
		// TODO: log file error
		return false;
	}

	auto result = file_read(&file, size, false, buffer);

	file_close(&file);

	return result;
}

bool __cdecl file_write_to_path(const wchar_t *path, DWORD size, LPVOID buffer)
{
	s_file_reference file;
	file_reference_create_from_path(&file, path, false);

	file_create_parent_directories_if_not_present(&file);

	if (!file_exists(&file))
		file_create(&file);

	int file_error;
	if (!file_open(&file, 2, &file_error))
	{
		// TODO: log file error
		return false;
	}

	auto result = file_write(&file, size, buffer);
	file_close(&file);

	return result;
}


bool __cdecl game_state_read_file_from_storage_hook(int a1, int a2)
{
	auto result = false;

	if (*g_runtime_state_allocation->IsInitialized)
	{
		((int(__cdecl *)(int))0x58A4B0)(a2);

		result = file_read_from_path((g_saves_path + L"gamestate.hdr").c_str(), *g_runtime_state_allocation->Size, *g_runtime_state_allocation->Data);

		game_state_buffer_handle_read();
		((int(__cdecl *)(char))0x58A5F0)(a2);
	}

	return result;
}

bool __cdecl read_campaign_save_file_blocking_hook(int, LPVOID buffer, DWORD size)
{
	return file_read_from_path((g_saves_path + L"mmiof.bmf").c_str(), size, buffer);
}

bool __cdecl game_state_read_header_from_persistent_storage_blocking_hook(int local_user_index, void *buffer, DWORD size)
{
	return file_read_from_path((g_saves_path + L"gamestate.hdr").c_str(), size, buffer);
}

void game_state_write_file_to_storage_hook()
{
	auto result = false;

	if (*g_runtime_state_allocation->IsInitialized)
		result = file_write_to_path((g_saves_path + L"gamestate.hdr").c_str(), *g_runtime_state_allocation->Size, *g_runtime_state_allocation->Data);

	*g_runtime_state_allocation->IsValid = result;
}

int __cdecl game_state_write_file_to_storage_blocking_hook(LPVOID buffer1, DWORD size1, LPVOID buffer2, DWORD size2)
{
	auto result = true;

	if (result)
		result = file_write_to_path((g_saves_path + L"gamestate.hdr").c_str(), size1, buffer1);

	if (result)
		result = file_write_to_path((g_saves_path + L"mmiof.bmf").c_str(), size2, buffer2);

	return 0;
}

bool __cdecl hash_verification_hook(int a1, int a2, bool a3, int32_t *a4, int a5)
{
	return true;
}

bool __cdecl saved_games__c_storage_device__content_item_not_found_hook(int)
{
	s_file_reference file;
	file_reference_create_from_path(&file, (g_saves_path + L"mmiof.bmf").c_str(), false);
	return file_exists(&file);
}


inline void SubmitGameStateHooks(const char *name)
{
	if (ConfigManager.GetBool("Hooks", name))
	{

		HookManager.Submit({ 0x0065DB10 }, &game_state_read_file_from_storage_hook, "game_state_read_file_from_storage");
		HookManager.Submit({ 0x005265E0 }, &read_campaign_save_file_blocking_hook, "read_campaign_save_file_blocking");
		HookManager.Submit({ 0x005266E0 }, &game_state_read_header_from_persistent_storage_blocking_hook, "game_state_write_file_to_storage");
		HookManager.Submit({ 0x005270F0 }, &game_state_write_file_to_storage_blocking_hook, "game_state_write_file_to_storage_blocking");
		HookManager.Submit({ 0x0065DBE0 }, &game_state_write_file_to_storage_hook, "game_state_write_file_to_storage");
		HookManager.Submit({ 0x00509020 }, &hash_verification_hook, "hash_verification");
		HookManager.Submit({ 0x005254A0 }, &saved_games__c_storage_device__content_item_not_found_hook, "saved_games::c_storage_device::content_item_not_exists");
	}
}

void SubmitGameStatePatches(const char *name)
{
	if (ConfigManager.GetBool("Patches", name))
	{
	}
}