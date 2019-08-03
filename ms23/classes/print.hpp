#pragma once
#include <iostream>

#include <Utils.hpp>

void hook_print(const char *hook, const char *DstBuf)
{
	//printf_s("%s: %s\n", hook, DstBuf);
}
void hook_print(const char *hook, const wchar_t *DstBuf)
{
	//printf_s("%s: %S\n", hook, DstBuf);
}
void hook_wcsn(const char *hook, const wchar_t *dst, const wchar_t *src, size_t size)
{
	//printf_s("%s: src=0x%p, dst=0x%p, size=0x%X\nstring=%S\n", hook, (void *)src, (void *)dst, size, src);
}
void hook_str(const char *hook, const char *dst, const char *src, size_t size)
{
	//printf_s("%s: src=0x%p, dst=0x%p, size=0x%X\nstring=%s\n", hook, (void *)src, (void *)dst, size, src);
}

//===========================================================================

char *__cdecl strcpy_hook(char *dest_string, char *src_string, unsigned __int32 size)
{
	unsigned __int32 v3 = 0;
	char *v4 = src_string;
	if (size)
	{
		while (v3 < size)
		{
			char v5 = *v4++;
			if (!v5)
				break;
			++v3;
		}
	}
	strncpy_s(dest_string, size, src_string, -1);
	if (v3 >= size)
		dest_string[size - 1] = 0;
	else
		memset(&dest_string[v3], 0, size - v3);

	hook_print("strcpy", dest_string);
	return dest_string;
}

wchar_t *__cdecl wchar_string_copy_hook(wchar_t *Dst, wchar_t *Src, size_t MaxCount)
{
	std::wstring ws(Src);
	if (wcscmp(Src, L"?:\\") == 0)
		ws = Utils::String::WidenString(GetDirectory());

	auto length = ws.length();
	wcsncpy_s(Dst, MaxCount, Src, -1);
	if (length >= MaxCount)
		Dst[MaxCount - 1] = 0;
	else
		memset(&Dst[length], 0, 2 * (MaxCount - length));

	hook_print("wchar_string_copy", Dst);
	return Dst;
}


//===========================================================================

wchar_t *__cdecl sub_401760_hook(wchar_t *Dst, wchar_t *Src, size_t MaxCount)
{
	std::wstring ws(Src);
	if (wcscmp(Src, L"\u0020\u0031\u25A1\u0004") == 0)
		ws = std::wstring(L"savegame.dat");

	size_t DstLen = wcsnlen(Dst, MaxCount);
	int SrcLen = ws.length();
	wcsncpy_s(&Dst[DstLen], MaxCount - DstLen, Src, -1);
	if (SrcLen + DstLen >= MaxCount)
		Dst[MaxCount - 1] = 0;
	else
		memset(&Dst[SrcLen + DstLen], 0, 2 * (MaxCount - SrcLen - DstLen));

	hook_print("sub_401760", Dst);
	return Dst;
}

//===========================================================================

char *blam_sprintf_hook(char *DstBuf, size_t SizeInBytes, const char *Format, ...)
{
	va_list ArgList;
	va_start(ArgList, Format);

	_vsnprintf_s(DstBuf, SizeInBytes, SizeInBytes - 1, Format, ArgList);
	DstBuf[SizeInBytes - 1] = 0;

	hook_print("blam_sprintf", DstBuf);
	return DstBuf;
}

wchar_t *sub_401940_hook(wchar_t *DstBuf, size_t SizeInWords, wchar_t *Format, ...)
{
	va_list ArgList;
	va_start(ArgList, Format);

	_vsnwprintf_s(DstBuf, SizeInWords, SizeInWords - 1, Format, ArgList);
	DstBuf[SizeInWords - 1] = 0;

	hook_print("sub_401940", DstBuf);
	return DstBuf;
}

int __cdecl vsnprintf_and_end_hook(char *DstBuf, size_t SizeInBytes, const char *Format, va_list ArgList)
{
	int result = _vsnprintf_s(DstBuf, SizeInBytes, SizeInBytes - 1, Format, ArgList);
	DstBuf[SizeInBytes - 1] = 0;

	hook_print("vsnprintf_and_end", DstBuf);
	return result;
}

bool __cdecl string_is_empty_hook(char *a1)
{
	if (!(!a1 || !*a1))
		hook_print("string_is_empty", a1);
	return !a1 || !*a1;
}

bool __cdecl find_string_in_string_hook(const char *a1, const char *a2)
{
	auto str = strcmp(a1, a2);
	if (str)
		return (-(str < 0) | 1) == 0;

	//printf_s("find_string_in_string: %s, %s\n", a1, a2);
	return true;
}

//===========================================================================

int sub_4EC9F0_hook(wchar_t *DstBuf, size_t SizeInWords, wchar_t *Format, ...)
{
	va_list ArgList;

	va_start(ArgList, Format);
	int result = _vsnwprintf_s(DstBuf, SizeInWords, -1, Format, ArgList);

	hook_print("sub_4EC9F0", DstBuf);
	return result;
}

int sub_4ECA10_hook(wchar_t *DstBuf, int a2, wchar_t *Format, ...)
{
	va_list ArgList;
	va_start(ArgList, Format);
	int result = _vsnwprintf_s(DstBuf, a2 - 1, -1, Format, ArgList);
	DstBuf[a2 - 1] = 0;

	hook_print("sub_4EC9F0", DstBuf);
	return result;
}

unsigned int get_wchar_count_hook(wchar_t *a1, unsigned int a2)
{
	unsigned int result = 0;
	while (a2 && result < a2)
	{
		if (!a1[result])
			break;
		++result;
	}

	//printf_s("get_wchar_count: %S, %d\n", a1, result);
	return result;
}

wchar_t *__cdecl wcsncpy_hook(wchar_t *a1, wchar_t *a2, int size_in_bytes)
{
	wchar_t *v3 = a2;
	for (int i = 0; i <= size_in_bytes - 1; ++v3)
	{
		wchar_t v5 = *v3;
		a1[i] = *v3;
		if (!v5)
			break;
		++i;
	}
	a1[size_in_bytes - 1] = 0;

	hook_wcsn("wcsncpy", a1, a2, size_in_bytes);
	return a1;
}

int __cdecl sub_4EDC90_hook(wchar_t *DstBuf, int a2, const wchar_t *Format, va_list ArgList)
{
	int result = _vsnwprintf_s(DstBuf, a2 - 1, -1, Format, ArgList);
	DstBuf[a2 - 1] = 0;

	hook_print("sub_4EDC90", DstBuf);
	return result;
}

//===========================================================================

int sub_5CF710_hook(wchar_t *dst, wchar_t *src, size_t size)
{
	unsigned int v3 = wcslen(dst);
	int result = wcsncmp(dst, src, size);
	if (!result && size != v3)
	{
		((char *)result)[0] = (signed int)(size - v3) >= 0;
		result = 2 * result - 1;
	}

	hook_wcsn("sub_5CF710", dst, src, size);
	return result;
}

wchar_t *wprintf_12288_hook(wchar_t *DstBuf, const wchar_t *Format, ...)
{
	va_list ArgList;
	va_start(ArgList, Format);
	auto wchar_count = get_wchar_count_hook(DstBuf, 0x3000u);
	sub_4EDC90_hook(&DstBuf[wchar_count], 0x3000 - wchar_count, Format, ArgList);

	printf_s("%S\n", DstBuf); // LOADING %d%
	hook_print("wprintf_12288", DstBuf);
	return DstBuf;
}

//===========================================================================

template<size_t SizeInBytes>
char *format(char *DstBuf, const char *Format, ...)
{
	va_list ArgList;
	va_start(ArgList, Format);
	vsnprintf_and_end_hook(DstBuf, SizeInBytes, Format, ArgList);

	char str[32]; sprintf_s(str, "format<%d>", SizeInBytes); hook_print(str, DstBuf);
	//printf_s("%s: %s\n", str, DstBuf);
	return DstBuf;
}

//===========================================================================

template<size_t SizeInBytes>
wchar_t *vsnwprintf_s(wchar_t *DstBuf, wchar_t *Format, ...)
{
	va_list ArgList;
	va_start(ArgList, Format);
	sub_4EDC90_hook(DstBuf, SizeInBytes, Format, ArgList);

	char str[32]; sprintf_s(str, "vsnwprintf_s<%d>", SizeInBytes); hook_print(str, DstBuf);
	//printf_s("%s: %S\n", str, DstBuf);
	return DstBuf;
}

//===========================================================================

int sprintf_s_hook(char *DstBuf, size_t SizeInBytes, const char *Format, ...)
{
	va_list ArgList;
	va_start(ArgList, Format);
	int result = _vsprintf_s_l(DstBuf, SizeInBytes, Format, 0, ArgList);

	hook_print("sprintf_s", DstBuf);
	return result;
}

int __cdecl wcsncmp_hook(const wchar_t *dst, const wchar_t *src, size_t size)
{
	int result = size;
	if (size)
	{
		const wchar_t *v4 = src;
		const wchar_t *v5 = dst;
		while (--result && *v5 && *v5 == *v4)
		{
			++v5;
			++v4;
		}
		result = *v5 - *v4;
	}
	if (Utils::String::ThinString(dst) == "" || Utils::String::ThinString(src) == "")
		return result;

	hook_wcsn("wcsncmp", dst, src, size);
	return result;
}

//===========================================================================

int network_debug_print_hook(char *format, ...)
{
	// fix strings using broken printf statements
	std::string formatStr(format);
	Utils::String::ReplaceString(formatStr, "%LX", "%llX");
	Utils::String::ReplaceString(formatStr, "%Lx", "%llx");

	char dstBuf[4096];
	memset(dstBuf, 0, 4096);

	va_list args;
	va_start(args, format);
	vsnprintf_s(dstBuf, 4096, 4096, formatStr.c_str(), args);
	va_end(args);

	printf_s("%s\n", dstBuf);

	return 1;
}

//===========================================================================

int __stdcall print_string_with_int_hook(const char *a1, int a2)
{
	return printf_s("%s: %d\n", a1, a2);
}

int __stdcall print_string_with_vector3d_hook(const char *a1, vector3d<float> a2)
{
	return printf_s("%s: %.2f, %.2f, %.2f\n", a1, a2.I, a2.J, a2.K);
}

int __stdcall print_string_with_string_hook(const char *a1, const char *a2)
{
	return printf_s("%s: %s\n", a1, a2);
}

int __stdcall print_string_with_wide_string_hook(const char *a1, const wchar_t *a2)
{
	return printf_s("%s: %S\n", a1, a2);
}

//===========================================================================

static const auto sub_52BA30 = (wchar_t *(*)(wchar_t *DstBuf, wchar_t *Format, ...))0x52BA30;

void print_vftable(uint32_t *a1)
{
	printf_s("%s::`vftable'\n", g_vftables.at(*a1).Name.c_str());
}

void print_vftable(uint32_t *a1, string_id a2, bool with_addr = false)
{
	auto vftable = g_vftables.at(*a1);
	if (with_addr)
		printf_s("%s::`vftable', 0x%08X, %s, 0x%X\n", vftable.Name.c_str(), vftable.Address, a2.GetName(), a2.value);
	else
		printf_s("%s::`vftable', %s\n", vftable.Name.c_str(), a2.GetName());
}

inline void SubmitPrintHooks(const char *name)
{
	if (ConfigManager.GetBool("Hooks", name))
	{
		HookManager.Submit({ 0x00401610 }, &strcpy_hook, "strcpy");

		HookManager.Submit({ 0x00401670 }, &wchar_string_copy_hook, "wchar_string_copy");
		HookManager.Submit({ 0x00401760 }, &sub_401760_hook, "sub_401760");

		HookManager.Submit({ 0x00401910 }, &blam_sprintf_hook, "blam_sprintf");
		HookManager.Submit({ 0x00401940 }, &sub_401940_hook, "sub_401940");
		HookManager.Submit({ 0x004019C0 }, &vsnprintf_and_end_hook, "vsnprintf_and_end");
		HookManager.Submit({ 0x00401AE0 }, &string_is_empty_hook, "string_is_empty");
		HookManager.Submit({ 0x00401B00 }, &find_string_in_string_hook, "find_string_in_string");

		HookManager.Submit({ 0x004521A0 }, &format<4>, "format<4>");
		HookManager.Submit({ 0x00430320 }, &format<16>, "format<16>");
		HookManager.Submit({ 0x004779F0 }, &format<17>, "format<17>");
		HookManager.Submit({ 0x005547D0 }, &format<32>, "format<32>");
		HookManager.Submit({ 0x00430360 }, &format<33>, "format<33>");
		HookManager.Submit({ 0x00477A10 }, &format<48>, "format<48>");
		HookManager.Submit({ 0x0042E8E0 }, &format<64>, "format<64>");
		HookManager.Submit({ 0x00830ED0 }, &format<128>, "format<128>");
		HookManager.Submit({ 0x005C5520 }, &format<255>, "format<255>");
		HookManager.Submit({ 0x00430340 }, &format<256>, "format<256>");
		HookManager.Submit({ 0x00440C10 }, &format<260>, "format<260>");
		HookManager.Submit({ 0x004329D0 }, &format<1024>, "format<1024>");
		HookManager.Submit({ 0x004329F0 }, &format<1536>, "format<1536>");
		HookManager.Submit({ 0x0066D2B0 }, &format<3976>, "format<3976>");

		HookManager.Submit({ 0x0052BA30 }, &vsnwprintf_s<256>, "vsnwprintf_s<256>");
		HookManager.Submit({ 0x006E5520 }, &vsnwprintf_s<1024>, "vsnwprintf_s<1024>");

		HookManager.Submit({ 0x004EC9F0 }, &sub_4EC9F0_hook, "sub_4EC9F0");
		HookManager.Submit({ 0x004ECA10 }, &sub_4ECA10_hook, "sub_4ECA10");
		HookManager.Submit({ 0x004ECBD0 }, &get_wchar_count_hook, "get_wchar_count");
		HookManager.Submit({ 0x004ECCD0 }, &wcsncpy_hook, "wcsncpy");
		HookManager.Submit({ 0x004EDC90 }, &sub_4EDC90_hook, "sub_4EDC90");

		HookManager.Submit({ 0x005CF710 }, &sub_5CF710_hook, "sub_5CF710");
		HookManager.Submit({ 0x0052EB80 }, &wprintf_12288_hook, "wprintf_12288");

		HookManager.Submit({ 0x00BF0A93 }, &sprintf_s_hook, "sprintf_s");
		HookManager.Submit({ 0x00BF28CA }, &wcsncmp_hook, "wcsncmp");

		//HookManager.Submit({ 0x00D858D0 }, &network_debug_print_hook, "network_debug_print"); // crashes, I think we hook this in ElDewrito

		HookManager.Submit({ 0x00618A10 }, &print_string_with_int_hook, "print_string_with_int");
		HookManager.Submit({ 0x00618A20 }, &print_string_with_vector3d_hook, "print_string_with_vector3d");
		HookManager.Submit({ 0x00618A30 }, &print_string_with_string_hook, "print_string_with_string");
		HookManager.Submit({ 0x00618A50 }, &print_string_with_wide_string_hook, "print_string_with_wide_string");
	}
}

inline void SubmitPrintPatches(const char *name)
{
	if (ConfigManager.GetBool("Patches", name))
	{

	}
}