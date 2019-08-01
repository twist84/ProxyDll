#pragma once

#include <Utils.hpp>

#include "../memory/tag_groups.hpp"
#include "../memory/local_types.hpp"
#include "filo.hpp"

namespace cache
{
	namespace cache_files_windows
	{
		char read(int a2, LONG tag_offset, DWORD size, LPVOID buffer);
		char *get_build(); // called on draw_watermark
		s_cache_file_header *get();
		char load_root_tag(uint32_t tag_index);
		char open_tags();
		char setup();
		char read_tag(LONG tag_offset, DWORD size, LPVOID buffer);
		char initialize(char *scenario_path, s_cache_file_header *cache_file_header);

		static auto dispose_from_old_map = (void *(__cdecl *)(LONG cache_file_shared_type))(0x5AB630);
		static auto initialize_for_new_map = (char(__cdecl *)(int cache_file_index, char *scenario_path))(0x5ABAD0);
		static auto get_source_file_cache_file_index = (int(__cdecl *)(char *scenario_path))(0x5ABE90);
	}
}

inline void SubmitCacheFilesHooks(const char *name)
{
	if (ConfigManager.GetBool("Hooks", name))
	{
		//HookManager.Submit({ 0x1016D0 }, &cache::cache_files_windows::read, "cache::cache_files_windows::read");
		HookManager.Submit({ 0x101940 }, &cache::cache_files_windows::get_build, "cache::cache_files_windows::get_build");
		HookManager.Submit({ 0x102F16 }, &cache::cache_files_windows::load_root_tag, "load_root_tag", HookFlags::IsCall);
		HookManager.Submit({ 0x1028C0 }, &cache::cache_files_windows::open_tags, "cache::cache_files_windows::open_tags");
		HookManager.Submit({ 0x102E9B }, &cache::cache_files_windows::setup, "cache::cache_files_windows::setup", HookFlags::IsCall);
		//HookManager.Submit({ 0x102C90 }, &cache::cache_files_windows::read_tag, "cache::cache_files_windows::read_tag");
		HookManager.Submit({ 0x102E1E }, &cache::cache_files_windows::initialize, "cache::cache_files_windows::initialize", HookFlags::IsCall);
	}
}

void cache_read_patch()
{
	if (ConfigManager.GetBool("Maps", "UseNewCacheStyle"))
	{
		// patches (g_cache_file_header.ExternalDependencies & 2) to true
		Patch(0x1027C7, { 0xEB }).Apply();
		Patch(0x102C9A, { 0xEB }).Apply();
		//Patch::NopFill(0x102B54, 6);
		//Patch::NopFill(0x102907, 2);
		//Patch::NopFill(0x102F27, 2);
	}
}

inline void SubmitCacheFilesPatches(const char *name)
{
	if (ConfigManager.GetBool("Patches", name))
	{
		PatchManager.Submit(&cache_read_patch, "cache_read_patch");
	}
}

namespace cache
{
	//	0x5016D0, cache::cache_files_windows::read
	//	0x501940, cache::cache_files_windows::get_build

	//	0x501950, cache::cache_files_windows::validate
	//	0x501BF0, cache::cache_files_windows::calculate_load_percentage

	//	0x501F90, cache::cache_files_windows::get

	//	0x502500, cache::cache_files_windows::partitions

	//	0x502780, cache::cache_files_windows::load_root_tag
	//	0x5028C0, cache::cache_files_windows::open_tags
	//	0x502B40, cache::cache_files_windows::setup
	//	00502C90, cache::cache_files_windows::read_tag

	//	0x502CE0, cache::cache_files_windows::dispose_internal
	//	0x503200, cache::cache_files_windows::dispose
	//	0x5A97C0, cache::cache_files_windows::do_work_internal
	//	0x5AA0C0, cache::cache_files_windows::get_handle
	//	0x5AA1D0, cache::cache_files_windows::get_io_completion_port_completion_key
	//	0x5AA420, cache::cache_files_windows::get_handle2
	//	0x5AA560, cache::cache_files_windows::get_interop_debug_section_size
	//	0x5AA660, cache::cache_files_windows::has_valid_cache_file_index

	//	0x5AA7C0, cache::cache_files_windows::initialize

	//	0x5AA910, cache::cache_files_windows::get_guid
	//	0x5AAB20, cache::cache_files_windows::do_work
	//	0x5AAD30, cache::cache_files_windows::copy_map
	//	0x5AAE70, cache::cache_files_windows::copy_stop
	//	0x5AAFD0, cache::cache_files_windows::individual_map_progress
	//	0x5AB0E0, cache::cache_files_windows::get_file_status
	//	0x5AB190, cache::cache_files_windows::get_load_action
	//	0x5AB2B0, cache::cache_files_windows::get_individual_map_size
	//	0x5AB320, cache::cache_files_windows::get_file_length
	//	0x5AB630, cache::cache_files_windows::dispose_from_old_map
	//	0x5AB6F0, cache::cache_files_windows::campare_filetime
	//	0x5ABAD0, cache::cache_files_windows::initialize_for_new_map
	//	0x5ABBD0, cache::cache_files_windows::validation
	//	0x5ABE90, cache::cache_files_windows::get_source_file_cache_file_index
	//	0x5AC420, cache::cache_files_windows::campare

	namespace cache_files_windows
	{
		char read(int a2, LONG tag_offset, DWORD size, LPVOID buffer)
		{
			printf_s("cache::cache_files_windows::read: [tag_offset, 0x%04X, size, 0x%04X]\n", tag_offset, size);

			//return ((char(*)(uint8_t *, int, LONG, DWORD, LPVOID))(0x5016D0))(a1, a2, tag_offset, size, buffer);
			int file_error;
			if (!file_open(global_tag_cache_filo, 1, &file_error))
				return 0;
			if (!file_set_position_hook(global_tag_cache_filo, tag_offset, 0))
				return 0;
			return file_read_hook(global_tag_cache_filo, size, 0, buffer);
		}

		char *get_build()
		{
			auto result = g_cache_file_header->Build;
			//printf_s("cache::cache_files_windows::get_build: [cache_file_header->Build, %s]\n", result);

			return result;
		}

		s_cache_file_header *get()
		{
			auto result = g_cache_file_header;
			printf_s("cache::cache_files_windows::get: [cache_file_header->ScenarioPath, %s]\n", result->ScenarioPath);

			return result;
		}

		char load_root_tag(uint32_t tag_index)
		{
			printf_s("cache::cache_files_windows::load_root_tag: [tag_index, 0x%04X]\n", tag_index);
			auto result = ((char(*)(uint32_t tag_index))0x502780)(tag_index);

			return result;
		}

		char open_tags()
		{
			cache_path.Update(ConfigManager.GetBool("Maps", "UseNewCacheStyle"));

			char result = 0;
			if (g_cache_file_header->ExternalDependencies & 2)
			{
				filo_create_hook(global_tag_cache_filo, cache_path.tags.Path.c_str(), 0);
				int file_error;
				result = file_open(global_tag_cache_filo, 1, &file_error);
			}

			cache_path.tags.Print();
			return result;
		}

		char setup()
		{
			printf_s("cache::cache_files_windows::setup: [cache_file_header->ScenarioPath, %s]\n", g_cache_file_header->ScenarioPath);
			auto result = ((char(*)())0x502B40)();

			return result;
		}

		char read_tag(LONG tag_offset, DWORD size, LPVOID buffer)
		{
			printf_s("cache::cache_files_windows::read_tag: [tag_offset, 0x%04X, size, 0x%04X]\n", tag_offset, size);
			if (!(g_cache_file_header->ExternalDependencies & 2))
				return read(2, tag_offset, size, buffer);

			int file_error;
			if (!file_open(global_tag_cache_filo, 1, &file_error))
				return 0;
			if (!file_set_position_hook(global_tag_cache_filo, tag_offset, 0))
				return 0;
			return file_read_hook(global_tag_cache_filo, size, 0, buffer);
		}

		char initialize(char *scenario_path, s_cache_file_header *cache_file_header)
		{
			if (((bool(__cdecl *)(char *))0x54C360)(scenario_path))
			{
				if (*(byte *)0x240B1E0)
				{
					auto runtime_resource_index = cache::cache_files_windows::get_source_file_cache_file_index(scenario_path);
					if (runtime_resource_index != -1)
						cache::cache_files_windows::dispose_from_old_map(runtime_resource_index);
				}
			}

			if (((bool(__cdecl *)(char *))0x54C360)(scenario_path))
				((char(__cdecl *)(char *, int a2))0x54C330)(scenario_path, 1);

			auto runtime_resource_index = cache::cache_files_windows::get_source_file_cache_file_index(scenario_path);
			if (*(byte *)0x240B1E0)
			{
				if (runtime_resource_index == -1)
				{
					runtime_resource_index = 7;

					if (!cache::cache_files_windows::initialize_for_new_map(runtime_resource_index, scenario_path))
						return 0;
				}
			}
			else if (runtime_resource_index == -1)
			{
				return 0;
			}

			auto ScenarioPath = g_cache_file->runtime_resources[runtime_resource_index].header.ScenarioPath;
			printf_s("cache::cache_files_windows::initialize: [runtime_resources[%d].header.ScenarioPath, %s]\n", runtime_resource_index, ScenarioPath);

			for (size_t i = 0; i < 15; i++)
			{
				auto SourceFile = g_cache_file->runtime_resources[i].header.SourceFile;
				printf_s("cache::cache_files_windows::initialize: [runtime_resource->cache_files[%d].header.SourceFile, %s]\n", i, SourceFile);
			}

			g_cache_file->runtime_resource_index = runtime_resource_index;
			memmove(cache_file_header, &g_cache_file->runtime_resources[runtime_resource_index].header, 0x3390u);
			return 1;
		}
	}
}