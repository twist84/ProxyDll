#pragma once
#include <windows.h>
#include <stdio.h>
#include <string>
#include <tchar.h>

struct sProxy
{
	HMODULE Dll;
	std::string Name = "D3DX9_43";
	FARPROC proc[329] = { 0 };
	bool DllLoaded = false;

	void LoadDll()
	{
		if (!DllLoaded)
		{
			Dll = ::LoadLibraryA("D3DX9_43_org.dll");
			DllLoaded = true;
		}
	}
	template<typename T>
	T Get(int offset)
	{
		return (T)proc[offset * 4];
	}
	void Set(int offset, LPCSTR name)
	{
		GetProcAddress(Dll, name);
	}
	bool Setup()
	{
		LoadDll();
		//Set(0, "D3DXCheckVersion");

		DisableThreadLibraryCalls(Dll);
		return true;
	}
};
sProxy GetProxy();