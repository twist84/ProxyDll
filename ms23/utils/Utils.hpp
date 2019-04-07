#pragma once
#include <vector>
#include <algorithm>
#include <rpcdce.h>

#include "../Patch.hpp"

FILE *fStdIn, *fStdOut, *fStdErr;

FILE* stream;

namespace std {
	template <typename _CharT, typename _Traits>
	inline basic_ostream<_CharT, _Traits> &
		tab(basic_ostream<_CharT, _Traits> &__os) {
		return __os.put(__os.widen('\t'));
	}
}

namespace Utils
{
	namespace Math
	{
		template<typename T>
		T Map(double x, double in_min, double in_max, double out_min, double out_max)
		{
			return (T)((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
		}

		template<typename T>
		bool Between(double val_to_check, double min_val, double max_val, T *outVal)
		{
			if (val_to_check < min_val || val_to_check > max_val)
				return false;
			*outVal = (T)val_to_check;
			return true;
		}
	}

	namespace Uuid
	{
		static UUID uuid_nil;
		static const BYTE hex2bin[] =
		{
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,			/* 0x00 */
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,			/* 0x10 */
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,			/* 0x20 */
				0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 0,			/* 0x30 */
				0, 10, 11, 12, 13, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0,	/* 0x40 */
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,			/* 0x50 */
				0, 10, 11, 12, 13, 14, 15								/* 0x60 */
		};

		RPC_STATUS _UuidCreateNil(UUID *Uuid)
		{
			*Uuid = uuid_nil;
			return RPC_S_OK;
		}

		RPC_STATUS uuidToString(UUID *Uuid, RPC_CSTR* StringUuid)
		{
			if (!(*StringUuid))
				return RPC_S_OUT_OF_MEMORY;

			if (!Uuid) Uuid = &uuid_nil;

			sprintf((char*)*StringUuid, "%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
				Uuid->Data1, Uuid->Data2, Uuid->Data3,
				Uuid->Data4[0], Uuid->Data4[1], Uuid->Data4[2],
				Uuid->Data4[3], Uuid->Data4[4], Uuid->Data4[5],
				Uuid->Data4[6], Uuid->Data4[7]);

			return RPC_S_OK;
		}

		RPC_STATUS uuidFromString(RPC_CSTR s, UUID *uuid)
		{
			int i;

			if (!s) return _UuidCreateNil(uuid);

			if (strlen((char*)s) != 36) return RPC_S_INVALID_STRING_UUID;

			if ((s[8] != '-') || (s[13] != '-') || (s[18] != '-') || (s[23] != '-'))
				return RPC_S_INVALID_STRING_UUID;

			for (i = 0; i < 36; i++)
			{
				if ((i == 8) || (i == 13) || (i == 18) || (i == 23)) continue;
				if (s[i] > 'f' || (!hex2bin[s[i]] && s[i] != '0')) return RPC_S_INVALID_STRING_UUID;
			}

			/* in form XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX */

			uuid->Data1 = (hex2bin[s[0]] << 28 | hex2bin[s[1]] << 24 | hex2bin[s[2]] << 20 | hex2bin[s[3]] << 16 |
				hex2bin[s[4]] << 12 | hex2bin[s[5]] << 8 | hex2bin[s[6]] << 4 | hex2bin[s[7]]);
			uuid->Data2 = hex2bin[s[9]] << 12 | hex2bin[s[10]] << 8 | hex2bin[s[11]] << 4 | hex2bin[s[12]];
			uuid->Data3 = hex2bin[s[14]] << 12 | hex2bin[s[15]] << 8 | hex2bin[s[16]] << 4 | hex2bin[s[17]];

			/* these are just sequential bytes */
			uuid->Data4[0] = hex2bin[s[19]] << 4 | hex2bin[s[20]];
			uuid->Data4[1] = hex2bin[s[21]] << 4 | hex2bin[s[22]];
			uuid->Data4[2] = hex2bin[s[24]] << 4 | hex2bin[s[25]];
			uuid->Data4[3] = hex2bin[s[26]] << 4 | hex2bin[s[27]];
			uuid->Data4[4] = hex2bin[s[28]] << 4 | hex2bin[s[29]];
			uuid->Data4[5] = hex2bin[s[30]] << 4 | hex2bin[s[31]];
			uuid->Data4[6] = hex2bin[s[32]] << 4 | hex2bin[s[33]];
			uuid->Data4[7] = hex2bin[s[34]] << 4 | hex2bin[s[35]];
			return RPC_S_OK;
		}
	}

	namespace String
	{
		std::wstring WidenString(const std::string &s)
		{
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> utf16conv;
			return utf16conv.from_bytes(s);
		}

		std::string ThinString(const std::wstring &str)
		{
			std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> utf8conv;
			return utf8conv.to_bytes(str);
		}

		std::string ToLower(const std::string &str)
		{
			std::string retValue(str);
			std::transform(retValue.begin(), retValue.end(), retValue.begin(), ::tolower);
			return retValue;
		}

		std::vector<std::string> SplitString(const std::string &stringToSplit, char delim)
		{
			std::vector<std::string> retValue;
			std::stringstream ss(stringToSplit);
			std::string item;
			while (std::getline(ss, item, delim))
			{
				retValue.push_back(item);
			}
			return retValue;
		}

		bool ReplaceString(std::string &str, const std::string &replace, const std::string &with)
		{
			size_t start_pos = str.find(replace);
			bool found = false;
			while (start_pos != std::string::npos)
			{
				str.replace(start_pos, replace.length(), with);
				start_pos += with.length();
				found = true;
				start_pos = str.find(replace, start_pos);
			}
			return found;
		}

		char *GuidToString(GUID *guid)
		{
			RPC_CSTR guidStr;
			Uuid::uuidToString(guid, &guidStr);

			return (char *)guidStr;
		}

		GUID GuidFromString(char *guidStr)
		{
			GUID guid;
			Uuid::uuidFromString((RPC_CSTR)guidStr, &guid);

			return guid;
		}

		bool InArray(const char *str, std::vector<const char*> arr, int *outVal)
		{
			bool result = false;
			for (size_t i = 0; i <= arr.size(); i++)
			{
				if (Utils::String::ToLower(str) == arr[i])
				{
					*outVal = (int)i;
					result = true;
				}
			}
			return result;
		}
	}

	void Log(std::string str, std::string file)
	{
		std::ofstream log;
		log.open(file, std::ofstream::app);
		log << str;
		log.close();
	}

	void Con(std::string str)
	{
		fStdIn = freopen("CONIN$", "r", stdin);
		fStdOut = freopen("CONOUT$", "w", stdout);
		fStdErr = freopen("CONOUT$", "w", stderr);

		std::wcout.clear();
		std::cout.clear();
		std::wcerr.clear();
		std::cerr.clear();
		std::wcin.clear();
		std::cin.clear();

		fprintf(fStdOut, str.c_str());
	}

	void LogOutput(const std::string &line)
	{
		std::stringstream ss;
		ss << line << std::endl;
		Utils::Log(ss.str(), (".\\ms23.txt"));
	}
}

void AssignHotkey(int vKey, void *function)
{
	if (GetAsyncKeyState(vKey))
		((void(*)())function)();
}

void HookVftable(DWORD dwVtable, DWORD member, void *function)
{
	DWORD oldProt, newProt;
	VirtualProtect((void*)dwVtable, 0x400, PAGE_EXECUTE_READWRITE, &oldProt);
	*(DWORD*)(dwVtable + (4 * member)) = (DWORD)&function;
	VirtualProtect((void*)dwVtable, 0x400, oldProt, &newProt);
}

struct HookInfo
{
	const char *name;
	std::vector<size_t> offsets;
	void* dest_func;
	HookFlags flags;

	HookInfo(std::vector<size_t> _offsets, void *_dest_func, const char *_name = "untitled", HookFlags _flags = HookFlags::None)
	{
		name = _name;
		offsets = _offsets;
		dest_func = _dest_func;
		flags = _flags;
	}
};
struct PatchInfo
{
	const char *name;
	void* dest_func;

	PatchInfo(void *_dest_func, const char *_name = "untitled")
	{
		name = _name;
		dest_func = _dest_func;
	}
};
struct VftHookInfo
{
	const char *name;
	size_t table_addr;
	int table_member;
	void* dest_func;
	HookFlags flags;

	VftHookInfo(size_t _offset, void *_dest_func, int _member, const char *_name = "untitled", HookFlags _flags = HookFlags::None)
	{
		name = _name;
		table_addr = _offset;
		table_member = _member;
		dest_func = _dest_func;
		flags = _flags;
	}
};
std::vector<HookInfo> hooks;
std::vector<PatchInfo> patches;
std::vector<VftHookInfo> vfthooks;
inline void AddHook(std::vector<size_t> offsets, void *dest_func, const char *name = "untitled", HookFlags flags = HookFlags::None)
{
	hooks.push_back(HookInfo(offsets, dest_func, name, flags));
}
inline void AddPatch(void* dest_func, const char *name = "untitled")
{
	patches.push_back(PatchInfo(dest_func, name));
}
inline void AddVftHook(size_t offset, void *dest_func, int member, const char *name = "untitled", HookFlags flags = HookFlags::None)
{
	vfthooks.push_back(VftHookInfo(offset, dest_func, member, name, flags));
}
inline void ApplyHooks()
{
	for (auto hook : hooks)
	{
		for (auto offset : hook.offsets)
			Hook(offset, hook.dest_func, hook.flags).Apply();
		printf_s("%s\n", hook.name);
	}
	for (auto hook : vfthooks)
	{
		HookVftable(hook.table_addr, hook.table_member, hook.dest_func);
		printf_s("%s\n", hook.name);
	}
}
inline void ApplyPatches()
{
	for (auto patch : patches)
	{
		((void(*)())patch.dest_func)();
		printf_s("%s\n", patch.name);
	}
}

template<typename T>
T VftableGetMember(DWORD dwVtable, int member)
{
	auto memAdr = *(DWORD *)(dwVtable + (4 * member));
	printf_s("Getting 0x%X at vft_%X[%d]\n", memAdr, dwVtable, member);
	return (T)memAdr;
}

struct ConMan
{
	const char *iniFilename;

	const char *GetString(const char *lpAppName, const char *lpKeyName)
	{
		const size_t ArraySize = 256;
		char* iniVal = new char[ArraySize];
		GetPrivateProfileStringA(lpAppName, lpKeyName, "", iniVal, ArraySize, iniFilename);

		return iniVal;
	}
	std::vector<std::string>GetSplitString(const char *lpAppName, const char *lpKeyName, char lpDelim)
	{
		return Utils::String::SplitString(GetString(lpAppName, lpKeyName), lpDelim);
	}
	int GetInt(const char *lpAppName, const char *lpKeyName)
	{
		return GetPrivateProfileIntA(lpAppName, lpKeyName, 0, iniFilename);
	}
	bool GetBool(const char *lpAppName, const char *lpKeyName)
	{
		return GetInt(lpAppName, lpKeyName) == 1;
	}
	LANGID GetLanguage(const char *lpAppName, const char *lpKeyName)
	{
		std::vector<const char *> languages = {
			"english",
			"japanese",
			"german",
			"french",
			"spanish",
			"mexican",
			"italian",
			"korean",
			"chinese-traditional",
			"chinese-simplified",
			"portuguese",
			"russian"
		};
		LANGID ids[] {
			LANG_ENGLISH,
			LANG_JAPANESE,
			LANG_GERMAN,
			LANG_FRENCH,
			LANG_SPANISH,
			LANG_SPANISH,
			LANG_ITALIAN,
			LANG_KOREAN,
			LANG_CHINESE_TRADITIONAL,
			LANG_CHINESE_SIMPLIFIED,
			LANG_PORTUGUESE,
			LANG_RUSSIAN
		};

		int outVal;
		if (Utils::String::InArray(GetString(lpAppName, lpKeyName), languages, &outVal))
			return ids[outVal];
		if (Utils::Math::Between(GetInt(lpAppName, lpKeyName), 0, 12, &outVal))
			return ids[outVal];

		return LANG_NEUTRAL;
	}
} ConfigManager;