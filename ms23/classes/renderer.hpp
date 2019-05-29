#pragma once

#include <Utils.hpp>
#include "../memory/local_types.hpp"

#include <d3d9.h>


auto			 g_clip_plane_near = *(int*)0x0191068C;
auto			  g_clip_plane_far = *(int*)0x01910690;
auto					  g_d3d9ex = *(int*)0x01910700;
auto		   g_D3dFormatIsD24FS8 = *(bool*)0x050DAE03;
auto			    g_IDirect3D9Ex = GetStructure<IDirect3D9Ex>(0x050DADD8);
auto		    g_IDirect3DDevice9 = GetStructure<IDirect3DDevice9>(0x050DADDC);
auto		 g_RenderStateCullMode = GetStructure<_D3DCULL>(0x050DAE1C);
auto	  g_IDirect3DVertexShader9 = GetStructure<IDirect3DVertexShader9>(0x050DAE20);
auto	   g_IDirect3DPixelShader9 = GetStructure<IDirect3DPixelShader9>(0x050DAE24);
auto g_IDirect3DVertexDeclaration9 = GetStructure<IDirect3DVertexDeclaration9>(0x050DAE28);
auto	   g_IDirect3DIndexBuffer9 = GetStructure<IDirect3DIndexBuffer9>(0x050DAE2C);
auto	   g_IDirect3DBaseTexture9 = GetStructure<IDirect3DBaseTexture9>(0x050DB214);
auto		  g_DisplayPreferences = GetStructure<D3DPRESENT_PARAMETERS>(0x050DD928);
auto	   g_NewDisplayPreferences = GetStructure<D3DPRESENT_PARAMETERS>(0x050DD960);
auto					 g_adapter = *(int*)0x050DD9C4;
auto		  g_IDirect3DDevice9_2 = GetStructure<IDirect3DDevice9>(0x0524B6AC);

//auto		  g_DisplayPreferences =		  GetStructure<D3DPRESENT_PARAMETERS>(0x4341420);
//auto	   g_NewDisplayPreferences =		  GetStructure<D3DPRESENT_PARAMETERS>(0x4341458);
//auto					 g_adapter =							           *(int *)0x278AFD0;


int __cdecl IDirect3DDevice9SetPixelShaderConstantI(UINT StartRegister, UINT Vector4iCount, const int *pConstantData) // 00A663A0
{
	return g_IDirect3DDevice9->SetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}
HRESULT __cdecl IDirect3DDevice9SetPixelShaderConstantB(UINT StartRegister, UINT BoolCount, const BOOL *pConstantData) // 00A66370
{
	if (StartRegister > 15)
		return 0;
	return g_IDirect3DDevice9->SetPixelShaderConstantB(StartRegister, pConstantData, BoolCount);
}
int __cdecl IDirect3DDevice9SetVertexShaderConstantB(UINT StartRegister, UINT BoolCount, const BOOL *pConstantData) // 00A66620
{
	return g_IDirect3DDevice9->SetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);
}
bool __cdecl IDirect3DIndexBuffer9SetIndexData(IDirect3DIndexBuffer9 *pIndexData) // 00A233C0
{
	if (pIndexData == g_IDirect3DIndexBuffer9)
		return 1;
	g_IDirect3DIndexBuffer9 = pIndexData;
	return g_IDirect3DDevice9->SetIndices(pIndexData) >= 0;
}
int __cdecl IDirect3DDevice9RenderStateFillModeSetValue(DWORD Value) // 00A233A0
{
	return g_IDirect3DDevice9->SetRenderState(D3DRS_FILLMODE, Value);
}
bool __cdecl IDirect3DDevice9PixelShaderSet(IDirect3DPixelShader9 *pShader) // 00A23500
{
	if (pShader == g_IDirect3DPixelShader9)
		return 1;
	g_IDirect3DPixelShader9 = pShader;
	return g_IDirect3DDevice9->SetPixelShader(pShader) >= 0;
}
bool __cdecl IDirect3DDevice9SetVertexDeclaration(IDirect3DVertexDeclaration9 *pDecl) // 00A24650
{
	if (pDecl == g_IDirect3DVertexDeclaration9)
		return 1;
	g_IDirect3DVertexDeclaration9 = pDecl;
	return g_IDirect3DDevice9->SetVertexDeclaration(pDecl) >= 0;
}
bool __cdecl IDirect3DDevice9VertexShaderSet(IDirect3DVertexShader9 *pShader) // 00A247B0
{
	if (pShader == g_IDirect3DVertexShader9)
		return 1;
	g_IDirect3DVertexShader9 = pShader;
	return g_IDirect3DDevice9->SetVertexShader(pShader) >= 0;
}
int __cdecl IDirect3DDevice9DepthStencilSurfaceSetZ(IDirect3DSurface9 *pNewZStencil) // 00A48C70
{
	D3DSURFACE_DESC pDesc;
	pNewZStencil->GetDesc(&pDesc);
	g_D3dFormatIsD24FS8 = pDesc.Format == D3DFMT_D24FS8;
	return g_IDirect3DDevice9->SetDepthStencilSurface(pNewZStencil);
}
BOOL IDirect3DDevice9IsNull() // 00A75810
{
	return g_IDirect3DDevice9 == 0;
}

int __cdecl IDirect3DDevice9UpdateTexture(IDirect3DBaseTexture9 *pSourceTexture, IDirect3DBaseTexture9 *pDestinationTexture) // 00A75E30
{
	return g_IDirect3DDevice9_2->UpdateTexture(pSourceTexture, pDestinationTexture);
}

HRESULT __cdecl IDirect3DDevice9CreateDepthStencilSurface(UINT Width, UINT Height, D3DFORMAT Format, int a4, DWORD MultisampleQuality, BOOL Discard, IDirect3DSurface9 **ppSurface) // 00A75A00
{
	if (!g_IDirect3DDevice9_2)
		return 0;
	return g_IDirect3DDevice9_2->CreateDepthStencilSurface(Width, Height, Format, D3DMULTISAMPLE_NONE, MultisampleQuality, Discard, ppSurface, 0);
}
int __cdecl IDirect3DDevice9CreateVolumeTexture(UINT Width, UINT Height, UINT Depth, UINT Levels, int a5, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture9 **ppVolumeTexture) // 00A75C70
{
	if (!g_IDirect3DDevice9_2)
		return 0;
	int Usage = a5;
	if (g_d3d9ex)
	{
		if (Pool == D3DPOOL_MANAGED)
		{
			Pool = D3DPOOL_DEFAULT;
			Usage = a5 | 0x200;
		}
	}
	return g_IDirect3DDevice9_2->CreateVolumeTexture(Width, Height, Depth, Levels, Usage, Format, Pool, ppVolumeTexture, 0);
}
HRESULT __cdecl IDirect3DDevice9CreateVertexDeclaration(const D3DVERTEXELEMENT9 *a1, IDirect3DVertexDeclaration9 **a2) // 00A75BD0
{
	if (!g_IDirect3DDevice9_2)
		return 0;
	return g_IDirect3DDevice9_2->CreateVertexDeclaration(a1, a2);
}
int __cdecl IDirect3DDevice9CreateTexture(int a1, int a2, int a3, int a4, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9 **ppTexture) // 00A75B20
{
	if (!g_IDirect3DDevice9_2)
		return 0;
	int v8, v9;
	if (Format == D3DFMT_DXT1 || Format == D3DFMT_DXT2 || Format == D3DFMT_DXT3 || Format == D3DFMT_DXT4 || Format == D3DFMT_DXT5)
	{
		v9 = a1;
		if (a1 & 3)
			v9 = 4 - (a1 & 3) + a1;
		v8 = a2;
		if (a2 & 3)
			v8 = 4 - (a2 & 3) + a2;
	}
	else
	{
		v8 = a2;
		v9 = a1;
	}
	int v11 = a4;
	if (g_d3d9ex)
	{
		if (Pool == D3DPOOL_MANAGED)
		{
			Pool = D3DPOOL_DEFAULT;
			v11 = a4 | 0x200;
		}
	}
	return g_IDirect3DDevice9_2->CreateTexture(v9, v8, a3, v11, Format, Pool, ppTexture, 0);
}
int __cdecl IDirect3DDevice9CreateVertexBuffer(UINT Length, DWORD a2, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9 **ppVertexBuffer, HANDLE *pSharedHandle) // 00A759B0
{
	if (!g_IDirect3DDevice9_2)
		return 0;
	DWORD Usage;
	if (g_d3d9ex && Pool == D3DPOOL_MANAGED)
	{
		Pool = D3DPOOL_DEFAULT;
		Usage = 8;
	}
	else
	{
		Usage = a2;
	}
	return g_IDirect3DDevice9_2->CreateVertexBuffer(Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle);
}
int __cdecl IDirect3DDevice9CreateIndexBuffer(UINT Length, DWORD a2, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer9 **ppIndexBuffer, HANDLE *pSharedHandle) // 00A75960
{
	if (!g_IDirect3DDevice9_2)
		return 0;
	DWORD Usage;
	if (g_d3d9ex && Pool == D3DPOOL_MANAGED)
	{
		Pool = D3DPOOL_DEFAULT;
		Usage = 8;
	}
	else
	{
		Usage = a2;
	}
	return g_IDirect3DDevice9_2->CreateIndexBuffer(Length, Usage, Format, Pool, ppIndexBuffer, pSharedHandle);
}
HRESULT __cdecl IDirect3DDevice9CreateCubeTexture(int EdgeLength, int Levels, int a3, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9 **ppCubeTexture) // 00A758F0
{
	if (!g_IDirect3DDevice9_2)
		return 0;
	int Usage = a3;
	if (g_d3d9ex && Pool == D3DPOOL_MANAGED)
	{
		Pool = D3DPOOL_DEFAULT;
		Usage = a3 | 0x200;
	}
	;
	HRESULT v8 = g_IDirect3DDevice9_2->CreateCubeTexture(EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture, 0);
	D3DSURFACE_DESC *pDesc;
	if (v8 >= 0)
		(*ppCubeTexture)->GetLevelDesc(0, pDesc);
	return v8;
}
HRESULT __cdecl sub_A23700(IDirect3DDevice9 *IDirect3DDevice9, int Sampler, int a4) // 00A23700
{
	HRESULT result;
	DWORD Sampler_1 = Sampler;
	auto IDirect3DDevice9_1 = IDirect3DDevice9;
	auto IDirect3DDevice9_2 = IDirect3DDevice9;
	auto IDirect3DDevice9_3 = IDirect3DDevice9;
	if (Sampler >= 16)
		Sampler_1 = Sampler + 0xF1;
	switch (a4)
	{
	case 0:
		g_IDirect3DDevice9->SetSamplerState(Sampler_1, D3DSAMP_MINFILTER, 2);
		g_IDirect3DDevice9->SetSamplerState(Sampler_1, D3DSAMP_MAGFILTER, 2);
		result = g_IDirect3DDevice9->SetSamplerState(Sampler_1, D3DSAMP_MIPFILTER, 2);
		break;
	case 1:
		IDirect3DDevice9_2 = IDirect3DDevice9;
		IDirect3DDevice9->SetSamplerState(Sampler_1, D3DSAMP_MINFILTER, 1u);
		IDirect3DDevice9_2->SetSamplerState(Sampler_1, D3DSAMP_MAGFILTER, 1u);
		goto LABEL_8;
	case 2:
	case 7:
		IDirect3DDevice9->SetSamplerState(Sampler_1, D3DSAMP_MINFILTER, 2u);
		IDirect3DDevice9_2->SetSamplerState(Sampler_1, D3DSAMP_MAGFILTER, 2u);
	LABEL_8:
		result = IDirect3DDevice9_2->SetSamplerState(Sampler_1, D3DSAMP_MIPFILTER, 1);
		break;
	case 3:
	case 4:
	case 5:
	case 6:
		IDirect3DDevice9->SetSamplerState(Sampler_1, D3DSAMP_MINFILTER, 3);
		IDirect3DDevice9_3->SetSamplerState(Sampler_1, D3DSAMP_MAGFILTER, 2);
		IDirect3DDevice9_3->SetSamplerState(Sampler_1, D3DSAMP_MIPFILTER, 2);
		result = IDirect3DDevice9_3->SetSamplerState(Sampler_1, D3DSAMP_MAXANISOTROPY, a4 - 2);
		break;
	default:
		return result;
	}
	return result;
}

struct D3DDevice9
{
	const char *Name;
	bool ShouldRender;

	D3DDevice9(const char *name, bool should_render = true)
	{
		Name = name;
		ShouldRender = should_render;
	}

	bool BeginScene(bool should_print = false)
	{
		if (should_print)
			printf_s("%s::BeginScene\n", Name);

		if (!ShouldRender)
			return false;

		return ((bool(__cdecl*)())0xA212A0)();
	}
	bool EndScene(bool should_print = false)
	{
		if (should_print)
			printf_s("%s::EndScene\n", Name);

		if (!ShouldRender)
			return false;

		return ((bool(__cdecl*)())0xA21510)();
	}
} D3DLoadingScreen("LoadingScreen", false), D3DUnknown("Unknown"), D3DGameWorld("GameWorld");

bool LoadingScreen__BeginScene_hook()
{
	return D3DLoadingScreen.BeginScene(true);
}
bool LoadingScreen__EndScene_hook()
{
	return D3DLoadingScreen.EndScene(true);
}

bool Unknown__BeginScene_hook()
{
	return D3DUnknown.BeginScene();
}
bool Unknown__EndScene_hook()
{
	return D3DUnknown.EndScene();
}

bool GameWorld__BeginScene_hook()
{
	return D3DGameWorld.BeginScene();
}
bool GameWorld__EndScene_hook()
{
	return D3DGameWorld.EndScene();
}

inline void AddRendererHooks(const char *name)
{
	if (ConfigManager.GetBool("Hooks", name))
	{
		HookManager.AddHook({ 0x1064C4 }, &LoadingScreen__BeginScene_hook, "LoadingScreen::BeginScene", HookFlags::IsCall);
		HookManager.AddHook({ 0x10654A }, &LoadingScreen__EndScene_hook, "LoadingScreen::EndScene", HookFlags::IsCall);

		HookManager.AddHook({ 0x106935 }, &Unknown__BeginScene_hook, "Unknown::BeginScene", HookFlags::IsCall);
		HookManager.AddHook({ 0x106953 }, &Unknown__EndScene_hook, "Unknown::EndScene", HookFlags::IsCall);

		HookManager.AddHook({ 0x204372 }, &GameWorld__BeginScene_hook, "GameWorld::BeginScene", HookFlags::IsCall);
		HookManager.AddHook({ 0x204A20 }, &GameWorld__EndScene_hook, "GameWorld::EndScene", HookFlags::IsCall);

		//HookManager.AddHook({ 0x6233A0 }, &IDirect3DDevice9RenderStateFillModeSetValue, "IDirect3DDevice9RenderStateFillModeSetValue");
		//HookManager.AddHook({ 0x6233C0 }, &IDirect3DIndexBuffer9SetIndexData, "IDirect3DIndexBuffer9SetIndexData");
		//HookManager.AddHook({ 0x623500 }, &IDirect3DDevice9PixelShaderSet, "IDirect3DDevice9PixelShaderSet");
		//HookManager.AddHook({ 0x623700 }, &sub_A23700, "sub_A23700");
		//HookManager.AddHook({ 0x624650 }, &IDirect3DDevice9SetVertexDeclaration, "IDirect3DDevice9SetVertexDeclaration");
		//HookManager.AddHook({ 0x6247B0 }, &IDirect3DDevice9VertexShaderSet, "IDirect3DDevice9VertexShaderSet");
		//HookManager.AddHook({ 0x648C70 }, &IDirect3DDevice9DepthStencilSurfaceSetZ, "IDirect3DDevice9DepthStencilSurfaceSetZ");
		//HookManager.AddHook({ 0x666370 }, &IDirect3DDevice9SetPixelShaderConstantB, "IDirect3DDevice9SetPixelShaderConstantB");
		//HookManager.AddHook({ 0x6663A0 }, &IDirect3DDevice9SetPixelShaderConstantI, "IDirect3DDevice9SetPixelShaderConstantI");
		//HookManager.AddHook({ 0x666620 }, &IDirect3DDevice9SetVertexShaderConstantB, "IDirect3DDevice9SetVertexShaderConstantB");
		//HookManager.AddHook({ 0x675810 }, &IDirect3DDevice9IsNull, "IDirect3DDevice9IsNull");
		//HookManager.AddHook({ 0x6758F0 }, &IDirect3DDevice9CreateCubeTexture, "IDirect3DDevice9CreateCubeTexture");
		//HookManager.AddHook({ 0x675960 }, &IDirect3DDevice9CreateIndexBuffer, "IDirect3DDevice9CreateIndexBuffer");
		//HookManager.AddHook({ 0x6759B0 }, &IDirect3DDevice9CreateVertexBuffer, "IDirect3DDevice9CreateVertexBuffer");
		//HookManager.AddHook({ 0x675A00 }, &IDirect3DDevice9CreateDepthStencilSurface, "IDirect3DDevice9CreateDepthStencilSurface");
		//HookManager.AddHook({ 0x675B20 }, &IDirect3DDevice9CreateTexture, "IDirect3DDevice9CreateTexture");
		//HookManager.AddHook({ 0x675BD0 }, &IDirect3DDevice9CreateVertexDeclaration, "IDirect3DDevice9CreateVertexDeclaration");
		//HookManager.AddHook({ 0x675C70 }, &IDirect3DDevice9CreateVolumeTexture, "IDirect3DDevice9CreateVolumeTexture");
		//HookManager.AddHook({ 0x675E30 }, &IDirect3DDevice9UpdateTexture, "IDirect3DDevice9UpdateTexture");
	}
}

struct
{
	bool val = true;

	void Apply()
	{
		// PresentationParameters->Windowed
		Patch(0x621FEA, { 0x00 }).Apply(val);
		// PresentationParameters->EnableAutoDepthStencil
		Patch(0x621FF8, { 0x00 }).Apply(val);
	}
	const char *Type()
	{
		return val ? "ms23" : "ms30";
	}
	const char *String()
	{
		return val ? "true" : "false";
	}
	const char *Set(bool val_)
	{
		val = val_;
		return Type();
	}
} StandardRendering;

// if true
// PresentationParameters->Windowed to false making the game fullscreen on borderless windowed
// PresentationParameters->EnableAutoDepthStencil to false like MS30 (note: I've no idea what this actually does)
// if false
// Continue rendering like normal
void UseStandardRendering(bool val)
{
	printf_s("%s style fullscreen | ", StandardRendering.Set(val));
	printf_s("PresentationParameters: (Windowed = %s), (EnableAutoDepthStencil = %s)\n", StandardRendering.String(), StandardRendering.String());
	StandardRendering.Set(val);
}

void SetInitialPresentationParametersPatch()
{
	StandardRendering.Apply();
}

inline void AddRendererPatches(const char *name)
{
	if (ConfigManager.GetBool("Patches", name))
	{
		PatchManager.AddPatch(&SetInitialPresentationParametersPatch, "SetInitialPresentationParameters");
	}
}