#pragma once

#include <Utils.hpp>

#include "../memory/tag_groups.hpp"
#include "../memory/local_types.hpp"
#include "filo.hpp"
#include "print.hpp"
#include "tags.hpp"

namespace cache
{
	namespace cache_files_windows
	{
		bool load(int campaign_id, int map_id, char *scenario_path);
		bool read(int unused, LONG tag_offset, DWORD size, LPVOID buffer);
		char *get_build();
		static auto verify_header = (bool(__cdecl *)(s_cache_file_header *cache_file_header))(0x501950);
		static auto calculate_load_percentage = (double(__cdecl *)(int, char *scenario_path))(0x501BF0);
		s_cache_file_header *get_header();
		int32_t *get_rsa();
		const char *map_path();
		static auto sub_501FD0 = (int(__cdecl *)())(0x501FD0);
		static auto hash_validate = (bool(__cdecl *)(s_cache_file_header *cache_file_header))(0x502210);
		static auto sub_502300 = (int(__cdecl *)(int, int))(0x502300);
		static auto partitions = (uint32_t(__thiscall *)(uint32_t *))(0x502500);
		char load_tag(uint32_t tag_index);
		bool open_tags(char *scenario_path);
		bool setup();
		bool read_blocking(LONG tag_offset, DWORD size, LPVOID buffer);
		static auto reset_tags = (uint32_t(__cdecl *)())(0x502CE0);
		bool load_tags(char *scenario_path);
		static auto fixup = (bool(__cdecl *)())(0x5031A0);
		static auto release = (void *(__cdecl *)())(0x503200);
		static auto dispose = (int(__cdecl *)())(0x503300);
		static auto initialize = (struct data_array *(__thiscall *)(class c_cache_file_tag_runtime_resource *, int))(0x503340);
		static auto sub_503470 = (void(__thiscall *)(void *, void *, int))(0x503470);
		static auto map_full_path = (bool(__cdecl *)(char *))(0x54C360);
		static auto do_work_internal = (bool(__cdecl *)())(0x5A97C0);
		static auto close = (bool(__cdecl *)())(0x5A9730);
		static auto get_resource_runtime_file_handle = (bool(__cdecl *)(int, LPVOID *))(0x5AA060);
		static auto get_resource_runtime_file_handle_from_scenario_path = (bool(__cdecl *)(char *, LPVOID *))(0x5AA0C0);
		static auto get_resource_runtime_indirect_file_handle_from_scenario_path = (bool(__cdecl *)(char *, LPVOID *))(0x5AA1D0);
		static auto get_cache_file_handle = (bool(__cdecl *)(LPVOID *))(0x5AA260);
		static auto get_cache_file_handle2 = (bool(__cdecl *)(LPVOID *))(0x5AA300);
		static auto get_interop_debug_section_size = (bool(__cdecl *)(int *))(0x5AA330);
		static auto get_resource_runtime_file_handle2 = (bool(__cdecl *)(int, LPVOID *))(0x5AA3C0);
		static auto get_resource_runtime_file_handle2_from_scenario_path = (bool(__cdecl *)(int, LPVOID *))(0x5AA420);
		static auto get_interop_debug_section_size_from_scenario_path = (bool(__cdecl *)(char *, int *))(0x5AA560);
		static auto has_valid_cache_file_index = (bool(__cdecl *)(char *))(0x5AA660);
		bool open_runtimes(char *scenario_path, s_cache_file_header *cache_file_header);
		static auto get_guid = (UUID *(__cdecl *)())(0x5AA8E0);
		static auto get_guid_from_scenario_path = (UUID *(__cdecl *)(char *))(0x5AA910);
		static auto do_work = (void(__cdecl *)())(0x5AAB20);
		static auto copy_map = (bool(__cdecl *)(char *, int))(0x5AAD30);
		static auto copy_stop = (bool(__cdecl *)(char *, int))(0x5AAE70);
		static auto individual_map_progress = (int(__cdecl *)(char *))(0x5AAFD0);
		static auto get_file_status = (int(__cdecl *)(char *))(0x5AB0E0);
		static auto get_load_action = (int(__cdecl *)(char *))(0x5AB190);
		static auto get_individual_map_size = (float(__cdecl *)(char *))(0x5AB2B0);
		static auto get_file_length = (int(__cdecl *)(char *))(0x5AB320);
		static auto initialize_data = (int(__cdecl *)())(0x5AB370);
		static auto dispose_from_old_map = (void *(__cdecl *)(int runtime_index))(0x5AB630);
		static auto dependencies_loaded = (bool(__cdecl *)(s_cache_file_header *cache_file_header, int *))(0x5AB6F0);
		static auto get_cache_path = (char *(__cdecl *)(int, char *, rsize_t))(0x5AB820);
		static auto open_runtime = (bool(__cdecl *)(int runtime_index, char *scenario_path))(0x5ABAD0);
		static auto validation = (bool(__cdecl *)(int))(0x5ABBD0);
		static auto get_runtime_count = (int(__cdecl *)(int, int))(0x5ABDF0);
		static auto get_tag_runtime_index_of_source_file = (int(__cdecl *)(char *scenario_path))(0x5ABE90);
		bool open_all_runtimes(bool *opened);
		static auto campare = (bool(__cdecl *)(int, int))(0x5AC420);
	}
}

inline void SubmitCacheFilesHooks(const char *name)
{
	if (ConfigManager.GetBool("Hooks", name))
	{
		//HookManager.Submit({ 0x004EA5E0 }, &cache::cache_files_windows::load, "cache::load");
		HookManager.Submit({ 0x004EA5EE }, &cache::cache_files_windows::load_tags, "cache::cache_files_windows::load_tags", HookFlags::IsCall);

		//HookManager.Submit({ 0x005016D0 }, &cache::cache_files_windows::read, "cache::cache_files_windows::read");
		//HookManager.Submit({ 0x00501940 }, &cache::cache_files_windows::get_build, "cache::cache_files_windows::get_build");

		//HookManager.Submit({ 0x00501F90 }, &cache::cache_files_windows::get_header, "cache::cache_files_windows::get_header");
		//HookManager.Submit({ 0x00501FA0 }, &cache::cache_files_windows::get_rsa, "cache::cache_files_windows::get_rsa");
		//HookManager.Submit({ 0x00501FC0 }, &cache::cache_files_windows::map_path, "cache::cache_files_windows::map_path");

		HookManager.Submit({ 0x005028C0 }, &cache::cache_files_windows::open_tags, "cache::cache_files_windows::open_tags");

			//HookManager.Submit({ 0x00502780 }, &cache::cache_files_windows::load_tag, "cache::cache_files_windows::load_tag");
		//HookManager.Submit({ 0x00502E9B }, &cache::cache_files_windows::setup, "cache::cache_files_windows::setup", HookFlags::IsCall);
		//HookManager.Submit({ 0x00502C90 }, &cache::cache_files_windows::read_blocking, "cache::cache_files_windows::read_blocking");
			//HookManager.Submit({ 0x00502DC0 }, &cache::cache_files_windows::load_tags, "cache::cache_files_windows::load_tags");
		
		//HookManager.Submit({ 0x00502E1E }, &cache::cache_files_windows::open_runtimes, "cache::cache_files_windows::open_runtimes", HookFlags::IsCall);
		//HookManager.Submit({ 0x00502F16 }, &cache::cache_files_windows::load_tag, "cache::cache_files_windows::load_tag", HookFlags::IsCall);

			//HookManager.Submit({ 0x005AA7C0 }, &cache::cache_files_windows::open_runtimes, "cache::cache_files_windows::open_runtimes");
		HookManager.Submit({ 0x005ABF00 }, &cache::cache_files_windows::open_all_runtimes, "cache::cache_files_windows::open_all_runtimes");
	}
}

inline void SubmitCacheFilesPatches(const char *name)
{
	if (ConfigManager.GetBool("Patches", name))
	{
	}
}

//-	004EA5E0, cache::cache_files_windows::load
//-	005016D0, cache::cache_files_windows::read
//-	00501940, cache::cache_files_windows::get_build, called on draw_watermark
//~	00501950, cache::cache_files_windows::verify_header
//~	00501BF0, cache::cache_files_windows::calculate_load_percentage
//-	00501F90, cache::cache_files_windows::get_header
//-	00501FA0, cache::cache_files_windows::get_rsa
//-	00501FA0, cache::cache_files_windows::map_path
//~	00501FD0, cache::cache_files_windows::sub_501FD0, used in c_cache_file_tag_resource_runtime_manager::initialize_for_new_map::c_cache_file_page_restorer
//~	00502210, cache::cache_files_windows::hash_validate
//~	00502300, cache::cache_files_windows::sub_502300, used in cache::cache_files_windows::do_work_internal as right side of ^ (bitwise or)
//~	00502500, cache::cache_files_windows::partitions
//~	00502780, cache::cache_files_windows::load_tag
//-	005028C0, cache::cache_files_windows::open_tags
//-	00502970, cache::cache_files_windows::read_from_tag_list
//-	00502B40, cache::cache_files_windows::setup
//-	00502C90, cache::cache_files_windows::read_blocking
//-	00502CE0, cache::cache_files_windows::reset_tags
//~	00502DC0, cache::cache_files_windows::load_tags
//-	005031A0, cache::cache_files_windows::fixup
//~	00503200, cache::cache_files_windows::release
//~	00503300, cache::cache_files_windows::dispose
//~	00503340, cache::cache_files_windows::initialize
//~	00503470, cache::cache_files_windows::sub_503470, used in cache::cache_files_windows::load_tag
//~	0054C360, cache::cache_files_windows::map_full_path
//~	005A97C0, cache::cache_files_windows::do_work_internal
//~	005A9730, cache::cache_files_windows::close
//~	005AA060, cache::cache_files_windows::get_resource_runtime_file_handle
//~	005AA0C0, cache::cache_files_windows::get_resource_runtime_file_handle_from_scenario_path
//~	005AA1D0, cache::cache_files_windows::get_resource_runtime_indirect_file_handle_from_scenario_path
//~	005AA260, cache::cache_files_windows::get_cache_file_handle
//~	005AA300, cache::cache_files_windows::get_cache_file_handle2
//~	005AA330, cache::cache_files_windows::get_interop_debug_section_size
//~	005AA3C0, cache::cache_files_windows::get_resource_runtime_file_handle2
//~	005AA420, cache::cache_files_windows::get_resource_runtime_file_handle2_from_scenario_path
//~	005AA560, cache::cache_files_windows::get_interop_debug_section_size_from_scenario_path
//~	005AA660, cache::cache_files_windows::has_valid_cache_file_index
//~	005AA7C0, cache::cache_files_windows::open_runtimes
//-	005AA8E0, cache::cache_files_windows::get_guid
//~	005AA910, cache::cache_files_windows::get_guid_from_scenario_path
//~	005AAB20, cache::cache_files_windows::do_work
//~	005AAD30, cache::cache_files_windows::copy_map
//~	005AAE70, cache::cache_files_windows::copy_stop
//~	005AAFD0, cache::cache_files_windows::individual_map_progress
//~	005AB0E0, cache::cache_files_windows::get_file_status
//~	005AB190, cache::cache_files_windows::get_load_action
//~	005AB2B0, cache::cache_files_windows::get_individual_map_size
//~	005AB320, cache::cache_files_windows::get_file_length
//~	005AB370, cache::cache_files_windows::initialize_data
//~	005AB630, cache::cache_files_windows::dispose_from_old_map
//~	005AB6F0, cache::cache_files_windows::dependencies_loaded
//~	005AB820, cache::cache_files_windows::get_cache_path
//~	005ABAD0, cache::cache_files_windows::open_runtime
//~	005ABBD0, cache::cache_files_windows::validation
//~	005ABDF0, cache::cache_files_windows::get_runtime_count
//~	005ABE90, cache::cache_files_windows::get_tag_runtime_index_of_source_file
//~	005ABF00, cache::cache_files_windows::open_all_runtimes
//~	005AC420, cache::cache_files_windows::campare

char *decomposePath(const char *path)
{
#if defined _WIN32
	const char *lastSeparator = strrchr(path, '\\');
#else
	const char *lastSeparator = strrchr(path, '/');
#endif

	const char *lastDot = strrchr(path, '.');
	const char *endOfPath = path + strlen(path);
	const char *startOfName = lastSeparator ? lastSeparator + 1 : path;
	const char *startOfExt = lastDot > startOfName ? lastDot : endOfPath;

	static char name[MAX_PATH + 1] = {};
	memset(name, 0, MAX_PATH);
	_snprintf(name, MAX_PATH, "%.*s", startOfExt - startOfName, startOfName);
	return name;
}

const int k_number_of_runtimes = 6;
void update_runtime(int index, const char *scenario_path = "")
{
	const char *runtimes[k_number_of_runtimes]
	{
		"ui",
		"resources",
		"textures",
		"textures_b",
		"audio",
		"video"
	};

	char full_path[MAX_PATH] = {};
	if (scenario_path[0])
		format<256>(full_path, "%s%s\\%s.dat", g_map_path.c_str(), decomposePath(scenario_path), runtimes[index]);
	else
		format<256>(full_path, "%s%s.dat", g_map_path.c_str(), runtimes[index]);

	g_cache.CacheFile.TagRuntimes[index].InvalidateHandles();

	if (((bool(__cdecl *)(int))0x501E80)(index - 1))
		cache::cache_files_windows::open_runtime(index, full_path);
}


bool cache::cache_files_windows::load(int campaign_id, int map_id, char *scenario_path) // dirty_disk_error(TODO: reimplement this function) if returned value is false
{
	if (cache::cache_files_windows::load_tags(scenario_path)) // TODO: fully reimplement this as a hook, not call hook
	{
		auto scenario = tag_get_definition_hook('scnr', *(uint32_t *)0x189CCF8);
		if ((map_id == -2) || ((uint32_t)(scenario + 4) == campaign_id || campaign_id == -1) && ((uint32_t)(scenario + 8) == map_id || map_id == -1))
		{
			((unsigned int(__cdecl *)())0x4EB6D0)(); // scenario_tags_fixup();
			((bool(__cdecl *)())0x600750)(); // game_startup(), TODO: fixup engine functions that use hf2p functions
			printf_s("cache::load: scenario_tags_fixup called\n");

			return true;
		}
		else
		{
			((void *(__cdecl *)())0x503200)(); // cache::cache_files_windows::release();
			printf_s("cache::load: cache_file_dispose called\n");

			*(uint32_t *)0x189CCF8 = -1;
			**(uint32_t **)0x22AAEB4 = 0;
			**(uint32_t **)0x22AAEB8 = 0;
			*(uint32_t *)0x189CD0C = -1;
			*(uint32_t *)0x22AAEBC = 0;

			return false;
		}
	}

	printf_s("cache::load: map_load_tags failed\n");
	return false;
}

bool cache::cache_files_windows::read(int unused, LONG tag_offset, DWORD size, LPVOID buffer)
{
	printf_s("cache::cache_files_windows::read: [tag_offset, 0x%04X, size, 0x%04X]\n", tag_offset, size);

	//return ((char(*)(uint8_t *, int, LONG, DWORD, LPVOID))(0x5016D0))(a1, a2, tag_offset, size, buffer);
	int file_error;
	if (!file_open(&global_tag_cache_filo, 1, &file_error))
		return 0;
	if (!file_set_position_hook(&global_tag_cache_filo, tag_offset, 0))
		return 0;
	return file_read_hook(&global_tag_cache_filo, size, 0, buffer);
}

char *cache::cache_files_windows::get_build()
{
	auto result = g_cache_file_header.Build;
	//printf_s("cache::cache_files_windows::get_build: [cache_file_header->Build, %s]\n", result);

	return result;
}
s_cache_file_header *cache::cache_files_windows::get_header()
{
	auto result = &g_cache_file_header;
	//printf_s("cache::cache_files_windows::get_header: [cache_file_header->scenario_path, %s]\n", result->scenario_path);

	return result;
}

int32_t *__cdecl cache::cache_files_windows::get_rsa()
{
	auto result = g_cache_file_header.RSA;

	printf_s("cache::cache_files_windows::get_rsa: [cache_file_header->RSA, (%d", result[0]);
	for (size_t i = 1; i < 64; i++)
		printf_s(", %d", result[i]);
	printf_s(")]\n");

	return result;
}

const char *cache::cache_files_windows::map_path()
{
	return g_map_path.c_str();
}

char cache::cache_files_windows::load_tag(uint32_t tag_index)
{
	printf_s("cache::cache_files_windows::load_tag: [tag_index, 0x%04X]\n", tag_index);
	auto result = ((char(*)(uint32_t tag_index))0x502780)(tag_index);

	return result;
}

bool cache::cache_files_windows::open_tags(char *scenario_path)
{
	char full_path[MAX_PATH] = {};
	if (scenario_path[0] && ConfigManager.GetBool("Maps", "UseNewCacheStyle"))
		format<256>(full_path, "%s%s\\tags.dat", g_map_path.c_str(), decomposePath(scenario_path));
	else
		format<256>(full_path, "%stags.dat", g_map_path.c_str());

	char result = 0;
	if (g_cache_file_header.ExternalDependencies & (1 << e_tag_runtime::_resources))
	{
		filo_create_hook(&global_tag_cache_filo, full_path, 0);
		int file_error;
		result = file_open(&global_tag_cache_filo, 1, &file_error);
	}

	printf_s("%s\n", full_path);
	return result;
}

bool cache::cache_files_windows::setup()
{
	printf_s("cache::cache_files_windows::setup: [cache_file_header->ScenarioPath, %s]\n", g_cache_file_header.scenario_path);
	auto result = ((char(*)())0x502B40)();

	return result;
}

bool cache::cache_files_windows::read_blocking(LONG tag_offset, DWORD size, LPVOID buffer)
{
	printf_s("cache::cache_files_windows::read_blocking: [tag_offset, 0x%04X, size, 0x%04X]\n", tag_offset, size);
	if (!(g_cache_file_header.ExternalDependencies & (1 << e_tag_runtime::_resources)))
		return cache::cache_files_windows::read(2, tag_offset, size, buffer);

	int file_error;
	if (!file_open(&global_tag_cache_filo, 1, &file_error))
		return 0;
	if (!file_set_position_hook(&global_tag_cache_filo, tag_offset, 0))
		return 0;
	return file_read_hook(&global_tag_cache_filo, size, 0, buffer);
}

struct s_scenario_definition : s_base_definition<0x824> {};
auto& g_scenario_definition = reference_get<s_scenario_definition>(0x22AAEB4);
auto g_scenario_tag_index = (uint32_t *)0x189CCF8;

struct s_globals_definition : s_base_definition<0x608> {};
auto& g_globals_definition = reference_get<s_globals_definition>(0x22AAEB8);
auto g_globals_tag_index = (uint32_t *)0x189CCFC;

auto g_resources_loaded = (bool *)0x22AAFF0;

static auto main_loop_pregame = (char(__cdecl *)())(0x5063A0);
static auto global_memory_map_allocate_data = (uint32_t * (__cdecl *)(int, int, int datum_size, uint32_t flags))(0x51D180);
static auto secure_working_memory_get_cache_data = (uint32_t(__cdecl *)())(0x5018F0);

bool cache::cache_files_windows::load_tags(char *scenario_path)
{
	printf_s("cache::cache_files_windows::load_tags: [scenario_path, %s]\n", scenario_path);

	if (ConfigManager.GetBool("Maps", "UseNewCacheStyle"))
	{
		for (int i = 0; i < k_number_of_runtimes; i++)
			update_runtime(i, scenario_path);
	}

	if (!g_shouldPrint)
		return ((char(*)(char *))0x502DC0)(scenario_path);

	//void *secure_working_memory = 0;
	//int secure_working_memory_size = 0;
	//secure_working_memory_get(0, &secure_working_memory, &secure_working_memory_size);
	//if (secure_working_memory_size >= 0x38C8 && secure_working_memory)
	//	memset(secure_working_memory, 0, 0x38C8u);

	int32_t scenario_tag_index = -1;
	char scenario_loaded = 0;

	int32_t globals_tag_index = -1;
	char globals_loaded = 0;

	if (cache::cache_files_windows::open_runtimes(scenario_path, &g_cache_file_header))
	{
		if (cache::cache_files_windows::verify_header(&g_cache_file_header))
		{
			if (*(bool *)0x189CFD0 && g_cache_file_header.TrackedBuild)
				((char(__cdecl *)(char *))0x42E390)(g_cache_file_header.Build);

			//s_cache_file_header cache_file_header;
			//memmove(&cache_file_header, g_cache_file_header, 0x3390u);

			float progress = 1.f;
			((void(__cdecl *)(int, int))0x52EEC0)(1, 1);

			cache::cache_files_windows::open_tags(scenario_path);
			cache::cache_files_windows::partitions((uint32_t *)pointer_get<uint8_t[8]>(0x22AE4D0));
			cache::cache_files_windows::setup();

			size_t tag_size = 4 * *g_cache_info.max_tag_count_ptr;
			*(uint32_t * *)g_cache_info.tag_table_ptr = global_memory_map_allocate_data(5, 0, tag_size, 0);
			memset(*(uint32_t * *)g_cache_info.tag_table_ptr, 0, tag_size);

			*(uint32_t *)0x22AB004 = 0;
			*g_cache_info.max_resource_count_ptr = 0x4B00000;
			*(uint32_t * *)g_cache_info.resource_table_ptr = global_memory_map_allocate_data(5, 0, *g_cache_info.max_resource_count_ptr, 0);
			g_cache_info.resource_index_table_ptr = 0;

			char root_tag_loaded = cache::cache_files_windows::load_tag(0) & 1;
			scenario_loaded = cache::cache_files_windows::load_tag(g_cache_file_header.ScenarioTagIndex) & root_tag_loaded;

			if (g_cache_file_header.ExternalDependencies & (1 << e_tag_runtime::_resources))
				file_close(&global_tag_cache_filo);

			((void(__cdecl *)())0x52EEF0)();

			if (scenario_loaded)
			{
				main_loop_pregame();

				if (scenario_loaded)
				{
					cache::cache_files_windows::fixup();
					scenario_tag_index = g_cache_file_header.ScenarioTagIndex;
					*g_resources_loaded = true;
					goto LABEL_25;
				}
				//auto v5 = (s_map_data_unknown_size_of_38C8 *)secure_working_memory_get_cache_data();
				//if (v5)
				//{
				//	
				//	v5->unknown3390[0] = 0;
				//	memset(v5->SHA1_B, 0xBB, 5 * sizeof(int32_t));
				//	memset(v5->SHA1_C, 0xCC, 5 * sizeof(int32_t));
				//	memset(v5->RSA, 0xDD, 64 * sizeof(int32_t));
				//	memmove(v5, &cache_file_header, 0x3390u);
				//	cache_file_header_dispose(&v5->cache_file);
				//	v5->size = 0x3390;
				//	v5->cache_file_ptr = &v5->cache_file;
				//	signed int v9 = 0x3390;
				//	secure_working_memory = v5->SHA;

				//	int SHA1_B;
				//	if (SHA1::Compute(v5->SHA, 1024, 1))
				//	{
				//		do
				//		{
				//			unsigned int v10 = v9;
				//			if (v9 > 0x100000)
				//				v10 = 0x100000;
				//			SHA1::Calculate(secure_working_memory, 1024, v5, v10);
				//			main_loop_pregame();
				//			v9 -= v10;
				//			v5 = (v5 + v10);
				//		} while (v9 > 0);
				//		SHA1_B = secure_working_memory_size;
				//		SHA1::sub_508E80(secure_working_memory, 1024, secure_working_memory_size);
				//	}
				//	else
				//	{
				//		SHA1_B = secure_working_memory_size;
				//	}

				//	int SHA1_C;
				//	ContentHeader::SHA1::Compute(SHA1_B, 20, 1, &SHA1_C);
				//	qmemcpy(v5->RSA, g_cache_file_header->RSA, 256u);
				//	main_loop_pregame();
				//	auto v12 = (s_map_data_unknown_size_of_38C8 *)secure_working_memory_get_cache_data();
				//	scenario_loaded = sub_508F80(v12->SHA1_C, v12->RSA);
				//	

				//	if (scenario_loaded)
				//	{
				//		v12->unknown3390[0] = 1;
				//		cache::cache_files_windows::fixup();
				//		scenario_tag_index = g_cache_file_header->ScenarioTagIndex;
				//		*g_resources_loaded = true;
				//		goto LABEL_25;
				//	}
				//}
				else
				{
					scenario_loaded = false;
				}
			}

			scenario_tag_index = -1;
		}

		((void(__cdecl *)())0x50CBB0)();
	}

	cache::cache_files_windows::reset_tags();
	cache::cache_files_windows::close();

LABEL_25:

	*g_scenario_tag_index = scenario_tag_index;
	if (scenario_tag_index == -1)
		return scenario_loaded;

	g_scenario_definition = *(s_scenario_definition *)tag_get_definition_hook('scnr', scenario_tag_index);


	globals_tag_index = ((uint32_t(__cdecl *)(uint32_t group))0x5017E0)('matg');
	*g_globals_tag_index = globals_tag_index;
	if (globals_tag_index == -1)
		return globals_loaded;
	g_globals_definition = *(s_globals_definition *)tag_get_definition_hook('matg', globals_tag_index);

	auto rasterizer_definition = ((tag_reference *)(g_globals_definition.data + 0x518))->GetDefinition();
	*(uint32_t *)0x50DD9BC = *(uint32_t *)(rasterizer_definition + 0x50);
	*(uint32_t *)0x50DD9C0 = *(uint32_t *)(rasterizer_definition + 0x54);

	return true;
}

bool cache::cache_files_windows::open_runtimes(char *scenario_path, s_cache_file_header *cache_file_header)
{
	auto tag_runtime_index = cache::cache_files_windows::get_tag_runtime_index_of_source_file(scenario_path);
	auto tag_runtimes = g_cache.CacheFile.TagRuntimes;

	//for (int i = 0; i < e_tag_runtime::k_number_of_tag_runtimes; i++)
	//{
	//	if (i == e_tag_runtime::_ui || i == e_tag_runtime::_tags)
	//		continue;

	//	// crashes, probably due to tag_runtimes[count - 1] being invalid
	//	//tag_runtimes[e_tag_runtime::k_tag_runtime_count - 1].Header.MoveTo(&tag_runtimes[i].Header);

	//	// succeeds, probably should throw an error perhaps because its only the header thats moved
	//	tag_runtimes[tag_runtime_index].Header.CopyTo(&tag_runtimes[i].Header);
	//}

	//// doing this is fine when force loading, not so much when using the menu
	//return tag_runtimes[tag_runtime_index].Header.MoveTo(cache_file_header);

	if (((bool(__cdecl *)(char *))0x54C360)(scenario_path))
	{
		if (*(byte *)0x240B1E0)
		{
			if (tag_runtime_index != -1)
				cache::cache_files_windows::dispose_from_old_map(tag_runtime_index);
		}
	}

	if (((bool(__cdecl *)(char *))0x54C360)(scenario_path))
		((char(__cdecl *)(char *, int a2))0x54C330)(scenario_path, 1);

	if (*(byte *)0x240B1E0)
	{
		if (tag_runtime_index == -1)
		{
			tag_runtime_index = 7;

			if (!cache::cache_files_windows::open_runtime(tag_runtime_index, scenario_path))
				return 0;
		}
	}
	else if (tag_runtime_index == -1)
	{
		return 0;
	}

	printf_s("cache::cache_files_windows::initialize\n{\n");
	for (size_t i = 0; i < 15; i++)
	{
		auto CacheFileHeader = tag_runtimes[i].Header;
		if (CacheFileHeader.ScenarioTagIndex)
			printf_s("\t%s.Header(0x%04X, %s)]\n", e_tag_runtime(i).GetName(), CacheFileHeader.ScenarioTagIndex, CacheFileHeader.scenario_path);
	}
	printf_s("\n");
	for (size_t i = 0; i < 15; i++)
	{
		auto CacheFileHeader = tag_runtimes[i].Header;
		if (CacheFileHeader.SourceFile[0] && !CacheFileHeader.ScenarioTagIndex)
			printf_s("\t%s.Header(%s)]\n", e_tag_runtime(i).GetName(), CacheFileHeader.SourceFile);
	}
	printf_s("};\n");

	g_cache.CacheFile.RuntimeIndex = tag_runtime_index;
	tag_runtimes[tag_runtime_index].Header.MoveTo(cache_file_header);
	return 1;
}

bool cache::cache_files_windows::open_all_runtimes(bool *opened)
{
	for (int i = 0; i < k_number_of_runtimes; i++)
		update_runtime(i);

	*opened = true;
	return *opened;
}