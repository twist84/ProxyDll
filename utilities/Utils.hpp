#pragma once
#include <Windows.h>
#include <algorithm>
#include <codecvt>
#include <experimental/filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <psapi.h>
#include <rpcdce.h>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include <Patch.hpp>

FILE *fStdIn, *fStdOut, *fStdErr;

FILE *stream;

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

		RPC_STATUS uuidToString(UUID *Uuid, RPC_CSTR *StringUuid)
		{
			if (!(*StringUuid))
				return RPC_S_OUT_OF_MEMORY;

			if (!Uuid) Uuid = &uuid_nil;

			sprintf((char*)*StringUuid, "%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
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
			for (size_t i = 0; i < arr.size(); i++)
			{
				if (Utils::String::ToLower(str) == arr[i])
				{
					*outVal = (int)i;
					result = true;
				}
			}
			return result;
		}

		namespace
		{
			// Modification of https://tweex.net/post/c-anything-tofrom-a-hex-string/

			std::string FromHex(std::vector<uint8_t> data)
			{
				std::stringstream hexStringStream; hexStringStream << std::hex << std::setfill('0');
				for (size_t index = 0; index < data.size(); ++index)
					hexStringStream << std::setw(2) << static_cast<int>(data[index]);

				return hexStringStream.str();
			}

			std::vector<uint8_t> ToHex(const std::string & in_)
			{
				auto in = std::string(in_);
				String::ReplaceString(in, ",", "");
				String::ReplaceString(in, " ", "");
				String::ReplaceString(in, "0x", "");

				std::vector<uint8_t> byteData;
				std::stringstream hexStringStream; hexStringStream >> std::hex;
				for (size_t strIndex = 0; strIndex < in.length(); )
				{
					const char tmpStr[3] = { in[strIndex++], in[strIndex++], 0 };

					hexStringStream.clear();
					hexStringStream.str(tmpStr);

					int tmpValue = 0;
					hexStringStream >> tmpValue;
					byteData.push_back(static_cast<uint8_t>(tmpValue));
				}

				return byteData;
			}
		}
	}

	namespace
	{
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

			if (fStdOut)
				fprintf(fStdOut, str.c_str());
		}

		void LogOutput(const std::string& line)
		{
			std::stringstream ss;
			ss << line << std::endl;
			Log(ss.str(), (".\\bin\\log.txt"));
		}

		std::vector<std::experimental::filesystem::directory_entry> GetDirectoryEntries(std::string path, bool recursive)
		{
			std::vector<std::experimental::filesystem::directory_entry> directory_entries;
			if (recursive)
				for (auto& p : std::experimental::filesystem::recursive_directory_iterator(path))
					directory_entries.push_back(p);
			else
				for (auto& p : std::experimental::filesystem::directory_iterator(path))
					directory_entries.push_back(p);
			return directory_entries;
		}

		std::vector<std::string> ReadFile(std::string Path, char Dilem = '\n')
		{
			std::stringstream ss;
			ss << std::ifstream(Path).rdbuf();
			return Utils::String::SplitString(ss.str(), Dilem);
		}

		std::vector<std::string> ReadLogs(bool RecursiveFolders, std::string LogExtension)
		{
			std::vector<std::string> result;
			for (auto& p : Utils::GetDirectoryEntries(".", RecursiveFolders))
			{
				if (p.path().extension() == LogExtension)
				{
					result.push_back(p.path().generic_string());
					for (std::string line : ReadFile(p.path().generic_string()))
						result.push_back(line);
					//DeleteFileA(entry.path().generic_string().c_str());
				}
			}
			return result;
		}
	}
}

void AssignHotkey(int vKey, void *function)
{
	if (GetAsyncKeyState(vKey))
		((void(*)())function)();
}

struct BaseMan
{
	const char *iniFilename = "";

	void Init(const char *iniFilename_)
	{
		iniFilename = iniFilename_;
	}
	bool IsInitialized()
	{
		return iniFilename != "";
	}

	const char *GetString(const char *lpAppName, const char *lpKeyName)
	{
		const size_t ArraySize = 256;
		char *iniVal = new char[ArraySize];
		GetPrivateProfileStringA(lpAppName, lpKeyName, "", iniVal, ArraySize, iniFilename);

		return iniVal;
	}
	void SetString(const char *lpAppName, const char *lpKeyName, const char *lpValue = "")
	{
		WritePrivateProfileStringA(lpAppName, lpKeyName, lpValue, iniFilename);
	}
	std::vector<std::string>GetSplitString(const char *lpAppName, const char *lpKeyName, char lpDelim)
	{
		return Utils::String::SplitString(GetString(lpAppName, lpKeyName), lpDelim);
	}
	const wchar_t *GetWString(const char *lpAppName, const char *lpKeyName)
	{
		const size_t ArraySize = 256;
		char *iniVal = new char[ArraySize];
		GetPrivateProfileStringA(lpAppName, lpKeyName, "", iniVal, ArraySize, iniFilename);

		return Utils::String::WidenString(iniVal).c_str();
	}
	void SetWString(const char *lpAppName, const char *lpKeyName, const wchar_t *lpValue = L"")
	{
		WritePrivateProfileStringA(lpAppName, lpKeyName, Utils::String::ThinString(lpValue).c_str(), iniFilename);
	}

	int GetInt(const char *lpAppName, const char *lpKeyName)
	{
		return GetPrivateProfileIntA(lpAppName, lpKeyName, 0, iniFilename);
	}
	std::vector<int>GetSplitInt(const char *lpAppName, const char *lpKeyName, char lpDelim)
	{
		std::vector<int> result;
		for (auto part : Utils::String::SplitString(GetString(lpAppName, lpKeyName), lpDelim))
			result.push_back(std::atoi(part.c_str()));
		return result;
	}
	void SetInt(const char *lpAppName, const char *lpKeyName, int lpValue = 0)
	{
		SetString(lpAppName, lpKeyName, std::to_string(lpValue).c_str());
	}

	bool GetBool(const char *lpAppName, const char *lpKeyName)
	{
		return GetInt(lpAppName, lpKeyName) == 1;
	}
	void SetBool(const char *lpAppName, const char *lpKeyName, bool lpValue = true)
	{
		SetInt(lpAppName, lpKeyName, lpValue);
	}

	float GetDouble(const char *lpAppName, const char *lpKeyName)
	{
		return (float)std::atof(GetString(lpAppName, lpKeyName));
	}
	float GetFloat(const char *lpAppName, const char *lpKeyName)
	{
		return (float)GetDouble(lpAppName, lpKeyName);
	}

	void SetEnvironmentVariables()
	{
		for (auto var : GetSplitString("Environment", "Variables", ';'))
		{
			auto varSplit = Utils::String::SplitString(var.c_str(), '=');
			SetEnvironmentVariableA(varSplit[0].c_str(), varSplit[1].c_str());
			printf_s("%s;", var.c_str());
		}
		printf_s("\n");
	}
};

struct ConMan : BaseMan
{
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
	bool CheckBoolAndRun(const char *lpAppName, const char *lpKeyName, void *function)
	{
		if (ConfigManager.GetBool(lpAppName, lpKeyName))
		{
			((void(*)())function)();
			Sleep(1000);
			ConfigManager.SetBool(lpAppName, lpKeyName, false);
			return true;
		}
		return false;
	}
} ConfigManager;

struct HookMan
{
	struct HookInfo
	{
		const char *name;
		std::vector<size_t> offsets;
		void *dest_func;
		HookFlags flags;

		HookInfo(std::vector<size_t> _offsets, void *_dest_func, const char *_name = "untitled", HookFlags _flags = HookFlags::None)
		{
			name = _name;
			offsets = _offsets;
			dest_func = _dest_func;
			flags = _flags;
		}

		void Apply()
		{
			for (auto offset : offsets)
			{
				if (offsets.size() == 1)
					printf_s("%s\n", name);
				else
					printf_s("%s, 0x%X\n", name, offset);
				Hook(offset - 0x400000, dest_func, flags).Apply();
			}
		}
	};
	struct VtblHookInfo
	{
		const char *name;
		size_t table_addr;
		int table_member;
		void *dest_func;
		HookFlags flags;

		VtblHookInfo(size_t _offset, void *_dest_func, int _member, const char *_name = "untitled", HookFlags _flags = HookFlags::None)
		{
			name = _name;
			table_addr = _offset;
			table_member = _member;
			dest_func = _dest_func;
			flags = _flags;
		}

		void Apply()
		{
			printf_s("%s\n", name);
			DWORD oldProt, newProt;
			VirtualProtect((void*)table_addr, 0x400, PAGE_EXECUTE_READWRITE, &oldProt);
			*(DWORD*)(table_addr + (4 * table_member)) = (DWORD)&dest_func;
			VirtualProtect((void*)table_addr, 0x400, oldProt, &newProt);
		}
	};

	std::vector<HookInfo> hooks;
	std::vector<VtblHookInfo> vtbl_hooks;

	inline void Submit(std::vector<size_t> offsets, void *dest_func, const char *name = "untitled", HookFlags flags = HookFlags::None)
	{
		hooks.push_back(HookInfo(offsets, dest_func, name, flags));
	}
	inline void SubmitVtbl(size_t offset, void *dest_func, int member, const char *name = "untitled", HookFlags flags = HookFlags::None)
	{
		vtbl_hooks.push_back(VtblHookInfo(offset, dest_func, member, name, flags));
	}
	inline void Apply()
	{
		for (auto hook : hooks)
			hook.Apply();
		for (auto hook : vtbl_hooks)
			hook.Apply();
	}
} HookManager;

struct PatchMan
{
	struct PatchInfo
	{
		const char *name;
		void *dest_func;

		PatchInfo(void *_dest_func, const char *_name = "untitled")
		{
			name = _name;
			dest_func = _dest_func;
		}

		void Apply()
		{
			printf_s("%s\n", name);
			((void(*)())dest_func)();
		}
	};

	std::vector<PatchInfo> patches;

	inline void Submit(void *dest_func, const char *name = "untitled")
	{
		patches.push_back(PatchInfo(dest_func, name));
	}
	inline void Apply()
	{
		for (auto patch : patches)
			patch.Apply();
	}
} PatchManager;

struct PlugMan : BaseMan
{
	//WritePrivateProfileStringA("Plugins", "Libs", ".\\mtndew.dll", iniFilename);
	std::vector<HMODULE> LoadedPlugins = {};
	HMODULE Load(const char *path)
	{
		printf_s("loading plugin... [%s]\n", path);
		auto lib = ::LoadLibraryA(path);
		if (!lib)
			printf_s("...failed to load plugin [%s]\n", path);
		else
			printf_s("...loaded plugin [%s]\n", path);
		return lib;
	}
	bool LoadPlugins(const char *lpAppName, const char *lpKeyName)
	{
		for (auto lib : GetSplitString(lpAppName, lpKeyName, ';'))
			LoadedPlugins.push_back(Load(lib.c_str()));
		return true;
	}
	bool LoadFolder(const char *lpAppName, const char *lpFolderKeyName, const char *lpExtensionKeyName)
	{
		for (auto& p : Utils::GetDirectoryEntries(GetString(lpAppName, lpFolderKeyName), GetBool("Config", "RecursiveFolders")))
			if (p.path().extension() == GetString(lpAppName, lpExtensionKeyName))
				LoadedPlugins.push_back(Load(p.path().generic_string().c_str()));
		return true;
	}
	void Run(const char *iniFilename_)
	{
		Init(iniFilename_);
		if (GetBool("Config", "UseFolder"))
			LoadFolder("Config", "Folder", "Extension");
		else
			LoadPlugins("Plugins", "Libs");
	}

	void Free()
	{
		for (auto Plugin : LoadedPlugins)
			FreeLibrary(Plugin);
	}
} PluginManager;


struct ProxMan
{
	HMODULE Dll;
	std::string Name;
	bool DllLoaded = false;

	void LoadDll()
	{
		if (!DllLoaded)
		{
			Dll = LoadLibraryA((Name + "_org.dll").c_str());
			if (!Dll)
				DllLoaded = false;
			else
				DllLoaded = true;
		}
	}
	std::string GetInitString()
	{
		return "Proxied " + Name + "_org.dll";
	}
	bool Load(std::string name)
	{
		Name = name;
		LoadDll();
		if (!DllLoaded)
			return false;

		DisableThreadLibraryCalls(Dll);
		return true;
	}
	bool Free()
	{
		return FreeLibrary(Dll);
	}
} ProxyManager;

uint32_t g_end_address = 0xFFFFFFFF;
struct s_vftable
{
	uint32_t Address;
	int Count;
	std::string Name;

	s_vftable(uint32_t address, int count, std::string name)
	{
		Address = address;
		Count = count;
		Name = name;
	}
	void UpdateEndAddress(int end_address)
	{
		g_end_address = end_address;
	}
	uint32_t GetMemberOffset(int member, bool base = false)
	{
		return (!base ? Address : Address - 0x400000) + (sizeof(uint32_t) * member);
	}
	uint32_t GetMemberReference(int member, bool base = false)
	{
		return *(uint32_t *)GetMemberOffset(member);
	}
	bool MemberHasReference(int member, bool base = false)
	{
		return GetMemberReference(member) != 0;
	}
	bool MemberReferenceIsGood(int member, bool base = false)
	{
		return MemberHasReference(member) && *(uint8_t *)GetMemberReference(member) != 0xC3;
	}
	bool MemberReferenceIsHook(int member, bool base = false)
	{
		return MemberHasReference(member) && GetMemberReference(member) > g_end_address;
	}
	bool AnyMemberHasRef()
	{
		bool result = false;
		for (int i = 0; i < Count; i++)
			if (MemberHasReference(i))
				result = true;
		return result;
	}
	bool AnyMemberRefIsGood()
	{
		bool result = false;
		for (int i = 0; i < Count; i++)
			if (MemberHasReference(i) && MemberReferenceIsGood(i))
				result = true;
		return result;
	}
	bool AnyMemberRefIsHook()
	{
		bool result = false;
		for (int i = 0; i < Count; i++)
			if (MemberHasReference(i) && MemberReferenceIsHook(i))
				result = true;
		return result;
	}
	void ReplaceMember(int member, void *func)
	{
		Pointer(GetMemberOffset(member)).Write(uint32_t(func));
	}
	template<typename T>
	T GetMember(int member, bool base = false)
	{
		return (T)GetMemberReference(member);
	}
	void PrintMembers()
	{
		//printf_s("%s::`vftable', member count: %d\n", Utils::String::SplitString(Name, ':')[0].c_str(), Count);
		printf_s("class %s {\n", Name.c_str());
		for (int i = 0; i < Count; i++)
		{
			if (MemberHasReference(i))
			{
				if (MemberReferenceIsGood(i))
				{
					if (MemberReferenceIsHook(i))
						printf_s("\thook_%08X;\t// %02d\n", GetMemberReference(i), i);
					else
						switch (GetMemberReference(i))
						{
						case 0xBED54F:
							printf_s("\t__purecall;\t// %02d\n", i);
							break;
						default:
							printf_s("\tsub_%08X;\t// %02d\n", GetMemberReference(i), i);
							break;
						}
				}
				else
					printf_s("\tnull_%08X;\t// %02d\n", GetMemberReference(i), i);
			}
			else
				printf_s("\tno_reference;\t// %02d\n", i);
		}
		printf_s("};\n\n");
	}
};

struct CliMan
{
	size_t Address;
	std::vector<std::pair<std::string, std::string>> Args;

	CliMan *Init(size_t addr)
	{
		Address = addr;
		return this;
	}

	CliMan *Add(std::string key, std::string val)
	{
		Args.push_back(std::make_pair(key, val));
		return this;
	}

	std::string At(std::string key)
	{
		for (auto parts : Utils::String::SplitString(Utils::String::SplitString(*(LPSTR *)Address, '?')[1], '&'))
		{
			std::string key = Utils::String::SplitString(parts, '=')[0];
			std::string val = Utils::String::SplitString(parts, '=')[1];
			Add(key, val);
		}

		for (auto pair : Args)
			if (pair.first == key)
				return pair.second;

		return "";
	}
} CliManager;