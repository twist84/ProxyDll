#pragma once

#include <Utils.hpp>
#include "../memory/local_types.hpp"

#include <d3d9.h>


auto g_clip_plane = GetStructure<clip_plane<float>>(0x0191068C);
auto g_d3d9ex = *(int*)0x01910700;
auto g_D3dFormatIsD24FS8 = *(bool*)0x050DAE03;
auto g_IDirect3D9Ex = GetStructure<IDirect3D9Ex*>(0x050DADD8);
auto g_IDirect3DDevice9 = GetStructure<IDirect3DDevice9*>(0x050DADDC);
auto g_RenderStateCullMode = GetStructure<D3DCULL>(0x050DAE1C);
auto g_IDirect3DVertexShader9 = GetStructure<IDirect3DVertexShader9*>(0x050DAE20);
auto g_IDirect3DPixelShader9 = GetStructure<IDirect3DPixelShader9*>(0x050DAE24);
auto g_IDirect3DVertexDeclaration9 = GetStructure<IDirect3DVertexDeclaration9*>(0x050DAE28);
auto g_IDirect3DIndexBuffer9 = GetStructure<IDirect3DIndexBuffer9*>(0x050DAE2C);
auto g_IDirect3DTexture9 = GetStructure<IDirect3DTexture9*>(0x050DB214);
auto g_DisplayPreferences = GetStructure<D3DPRESENT_PARAMETERS>(0x050DD928);
auto g_DisplayPreferencesNew = GetStructure<D3DPRESENT_PARAMETERS>(0x050DD960);
auto g_adapter = *(int*)0x050DD9C4;
auto g_IDirect3DDevice9_2 = GetStructure<IDirect3DDevice9*>(0x0524B6AC);


//auto g_DisplayPreferences = GetStructure<D3DPRESENT_PARAMETERS>(0x4341420);
//auto g_NewDisplayPreferences = GetStructure<D3DPRESENT_PARAMETERS>(0x4341458);
//auto g_adapter = *(int *)0x278AFD0;

template<typename T>
struct Rect
{
	T top;
	T left;
	T bottom;
	T right;

	D3DVIEWPORT9 ToViewport(float MinZ, float MaxZ)
	{
		return D3DVIEWPORT9({ (DWORD)left, (DWORD)top, (DWORD)(right - left), (DWORD)(bottom - top), MinZ, MaxZ });
	}
};

struct D3DDevice9
{
	const char* Name;
	bool ShouldRender;

	D3DDevice9(const char* name, bool should_render = true)
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

		//return IDirect3DDevice9__BeginScene();
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
} LoadingScene("Loading", false), UnknownScene("Unknown"), WorldScene("GameWorld");

bool Loading__BeginScene_hook()
{
	return LoadingScene.BeginScene(true);
}
bool Loading__EndScene_hook()
{
	return LoadingScene.EndScene(true);
}

bool Unknown__BeginScene_hook()
{
	return UnknownScene.BeginScene();
}
bool Unknown__EndScene_hook()
{
	return UnknownScene.EndScene();
}

bool World__BeginScene_hook()
{
	return WorldScene.BeginScene();
}
bool World__EndScene_hook()
{
	return WorldScene.EndScene();
}

bool __cdecl IDirect3DDevice9__BeginScene() // 00A212A0
{
	if (!g_IDirect3DDevice9)
		return true;

	*(int*)0x194FEA8 = GetCurrentThreadId();

	if (!*(bool*)0x50DD9D0 && !*(bool*)0x50DD9D1)
		goto End;

	if (*(int*)0x19104FC != ((int(__cdecl*)())0x51C410)())
	{
		((int(__cdecl*)(int, char))0x506EB0)(8, 1);
		return false;
	}

	if (!*(bool*)0x50DD9D0)
	{
		if (*(bool*)0x50DD9D1)
			((bool(__cdecl*)())0xA226D0)();

		goto End;
	}

	if (((bool(__cdecl*)())0xA22670)())
	{
	End:
		((int(__cdecl*)(int, char))0x506EB0)(8, 0);
		return (*g_IDirect3DDevice9)->BeginScene() >= 0;
	}
	return true;
}

int IDirect3DDevice9__SetRenderState__CullMode(D3DCULL Value) // 00A232D0
{
	if (Value != *g_RenderStateCullMode)
		* g_RenderStateCullMode = Value;

	return (*g_IDirect3DDevice9)->SetRenderState(D3DRS_CULLMODE, Value);
}
int __cdecl IDirect3DDevice9__SetRenderState__FillMode(DWORD Value) // 00A233A0
{
	return (*g_IDirect3DDevice9)->SetRenderState(D3DRS_FILLMODE, Value);
}
bool __cdecl IDirect3DDevice9__SetIndices(IDirect3DIndexBuffer9 *pIndexData) // 00A233C0
{
	if (pIndexData == *g_IDirect3DIndexBuffer9)
		return 1;

	*g_IDirect3DIndexBuffer9 = pIndexData;
	return (*g_IDirect3DDevice9)->SetIndices(pIndexData) >= 0;
}
bool __cdecl IDirect3DDevice9__SetPixelShader(IDirect3DPixelShader9 *pShader) // 00A23500
{
	if (pShader == *g_IDirect3DPixelShader9)
		return 1;

	*g_IDirect3DPixelShader9 = pShader;
	return (*g_IDirect3DDevice9)->SetPixelShader(pShader) >= 0;
}
HRESULT __cdecl sub_A23700(IDirect3DDevice9* IDirect3DDevice9, int Sampler, int a4) // 00A23700
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
		(*g_IDirect3DDevice9)->SetSamplerState(Sampler_1, D3DSAMP_MINFILTER, 2);
		(*g_IDirect3DDevice9)->SetSamplerState(Sampler_1, D3DSAMP_MAGFILTER, 2);
		result = (*g_IDirect3DDevice9)->SetSamplerState(Sampler_1, D3DSAMP_MIPFILTER, 2);
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
bool __cdecl IDirect3DDevice9__SetVertexDeclaration(IDirect3DVertexDeclaration9* pDecl) // 00A24650
{
	if (pDecl == *g_IDirect3DVertexDeclaration9)
		return 1;

	*g_IDirect3DVertexDeclaration9 = pDecl;
	return (*g_IDirect3DDevice9)->SetVertexDeclaration(pDecl) >= 0;
}
bool __cdecl IDirect3DDevice9__SetVertexShader(IDirect3DVertexShader9 *pShader) // 00A247B0
{
	if (pShader == *g_IDirect3DVertexShader9)
		return 1;

	*g_IDirect3DVertexShader9 = pShader;
	return (*g_IDirect3DDevice9)->SetVertexShader(pShader) >= 0;
}
int __cdecl IDirect3DDevice9__SetDepthStencilSurface__ZStencil(IDirect3DSurface9* pNewZStencil) // 00A48C70
{
	D3DSURFACE_DESC pDesc;
	pNewZStencil->GetDesc(&pDesc);
	g_D3dFormatIsD24FS8 = pDesc.Format == D3DFMT_D24FS8;
	return (*g_IDirect3DDevice9)->SetDepthStencilSurface(pNewZStencil);
}

int IDirect3DDevice9__SetViewport(Rect<int16_t>* rect, float MinZ, float MaxZ) // 00A49010
{
	return (*g_IDirect3DDevice9)->SetViewport(&rect->ToViewport(MinZ, MaxZ));
}
HRESULT __cdecl IDirect3DDevice9__SetPixelShaderConstantB(UINT StartRegister, UINT BoolCount, const BOOL *pConstantData) // 00A66370
{
	if (StartRegister > 15)
		return 0;

	return (*g_IDirect3DDevice9)->SetPixelShaderConstantB(StartRegister, pConstantData, BoolCount);
}
int __cdecl IDirect3DDevice9__SetPixelShaderConstantI(UINT StartRegister, UINT Vector4iCount, const int *pConstantData) // 00A663A0
{
	return (*g_IDirect3DDevice9)->SetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}
int __cdecl IDirect3DDevice9__SetVertexShaderConstantB(UINT StartRegister, UINT BoolCount, const BOOL *pConstantData) // 00A66620
{
	return (*g_IDirect3DDevice9)->SetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);
}
BOOL IDirect3DDevice9__IsNull() // 00A75810
{
	return (*g_IDirect3DDevice9_2) == 0;
}
HRESULT __cdecl IDirect3DDevice9__CreateCubeTexture(int EdgeLength, int Levels, int a3, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9** ppCubeTexture) // 00A758F0
{
	if (!(*g_IDirect3DDevice9_2))
		return 0;

	int Usage = a3;
	if (g_d3d9ex && Pool == D3DPOOL_MANAGED)
	{
		Pool = D3DPOOL_DEFAULT;
		Usage = a3 | 0x200;
	}
	;
	HRESULT v8 = (*g_IDirect3DDevice9_2)->CreateCubeTexture(EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture, 0);
	D3DSURFACE_DESC pDesc;
	if (v8 >= 0)
		(*ppCubeTexture)->GetLevelDesc(0, &pDesc);

	return v8;
}
int __cdecl IDirect3DDevice9__CreateIndexBuffer(UINT Length, DWORD a2, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer9* ppIndexBuffer, HANDLE* pSharedHandle) // 00A75960
{
	if (!(*g_IDirect3DDevice9_2))
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

	return (*g_IDirect3DDevice9_2)->CreateIndexBuffer(Length, Usage, Format, Pool, &ppIndexBuffer, pSharedHandle);
}
int __cdecl IDirect3DDevice9__CreateVertexBuffer(UINT Length, DWORD a2, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9 *ppVertexBuffer, HANDLE *pSharedHandle) // 00A759B0
{
	if (!(*g_IDirect3DDevice9_2))
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

	return (*g_IDirect3DDevice9_2)->CreateVertexBuffer(Length, Usage, FVF, Pool, &ppVertexBuffer, pSharedHandle);
}
HRESULT __cdecl IDirect3DDevice9__CreateDepthStencilSurface__MultisampleNone(UINT Width, UINT Height, D3DFORMAT Format, int a4, DWORD MultisampleQuality, BOOL Discard, IDirect3DSurface9 **ppSurface) // 00A75A00
{
	if (!(*g_IDirect3DDevice9_2))
		return 0;

	return (*g_IDirect3DDevice9_2)->CreateDepthStencilSurface(Width, Height, Format, D3DMULTISAMPLE_NONE, MultisampleQuality, Discard, ppSurface, 0);
}
int __cdecl IDirect3DDevice9__CreateTexture(int a1, int a2, int a3, int a4, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture) // 00A75B20
{
	if (!(*g_IDirect3DDevice9_2))
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

	return (*g_IDirect3DDevice9_2)->CreateTexture(v9, v8, a3, v11, Format, Pool, ppTexture, 0);
}
HRESULT __cdecl IDirect3DDevice9__CreateVertexDeclaration(const D3DVERTEXELEMENT9* a1, IDirect3DVertexDeclaration9** a2) // 00A75BD0
{
	if (!(*g_IDirect3DDevice9_2))
		return 0;
	return (*g_IDirect3DDevice9_2)->CreateVertexDeclaration(a1, a2);
}
int __cdecl IDirect3DDevice9__CreateVolumeTexture(UINT Width, UINT Height, UINT Depth, UINT Levels, int a5, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture9 **ppVolumeTexture) // 00A75C70
{
	if (!(*g_IDirect3DDevice9_2))
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
	return (*g_IDirect3DDevice9_2)->CreateVolumeTexture(Width, Height, Depth, Levels, Usage, Format, Pool, ppVolumeTexture, 0);
}
int __cdecl IDirect3DDevice9__UpdateTexture(IDirect3DBaseTexture9* pSourceTexture, IDirect3DBaseTexture9* pDestinationTexture) // 00A75E30
{
	return (*g_IDirect3DDevice9_2)->UpdateTexture(pSourceTexture, pDestinationTexture);
}

inline void AddRendererHooks(const char *name)
{
	if (ConfigManager.GetBool("Hooks", name))
	{
		//HookManager.AddHook({ 0x1064C4 }, &Loading__BeginScene_hook, "Loading::BeginScene", HookFlags::IsCall);
		//HookManager.AddHook({ 0x10654A }, &Loading__EndScene_hook, "Loading::EndScene", HookFlags::IsCall);

		//HookManager.AddHook({ 0x106935 }, &Unknown__BeginScene_hook, "Unknown::BeginScene", HookFlags::IsCall);
		//HookManager.AddHook({ 0x106953 }, &Unknown__EndScene_hook, "Unknown::EndScene", HookFlags::IsCall);

		//HookManager.AddHook({ 0x204372 }, &World__BeginScene_hook, "World::BeginScene", HookFlags::IsCall);
		//HookManager.AddHook({ 0x204A20 }, &World__EndScene_hook, "World::EndScene", HookFlags::IsCall);

		// correct* implementations
		
		HookManager.AddHook({ 0x6212A0 }, &IDirect3DDevice9__BeginScene, "IDirect3DDevice9::BeginScene");
		HookManager.AddHook({ 0x6232D0 }, &IDirect3DDevice9__SetRenderState__CullMode, "IDirect3DDevice9::SetRenderState::CullMode");
		HookManager.AddHook({ 0x6233A0 }, &IDirect3DDevice9__SetRenderState__FillMode, "IDirect3DDevice9::SetRenderState::FillMode");
		HookManager.AddHook({ 0x6233C0 }, &IDirect3DDevice9__SetIndices, "IDirect3DDevice9::SetIndices");
		HookManager.AddHook({ 0x623500 }, &IDirect3DDevice9__SetPixelShader, "IDirect3DDevice9::SetPixelShader");
		HookManager.AddHook({ 0x624650 }, &IDirect3DDevice9__SetVertexDeclaration, "IDirect3DDevice9::SetVertexDeclaration");
		HookManager.AddHook({ 0x6247B0 }, &IDirect3DDevice9__SetVertexShader, "IDirect3DDevice9::SetVertexShader");
		HookManager.AddHook({ 0x648C70 }, &IDirect3DDevice9__SetDepthStencilSurface__ZStencil, "IDirect3DDevice9::DepthStencilSurfaceSetZ");
		HookManager.AddHook({ 0x649010 }, &IDirect3DDevice9__SetViewport, "IDirect3DDevice9::SetViewport");
		HookManager.AddHook({ 0x666370 }, &IDirect3DDevice9__SetPixelShaderConstantB, "IDirect3DDevice9::SetPixelShaderConstantB");
		HookManager.AddHook({ 0x6663A0 }, &IDirect3DDevice9__SetPixelShaderConstantI, "IDirect3DDevice9::SetPixelShaderConstantI");
		HookManager.AddHook({ 0x666620 }, &IDirect3DDevice9__SetVertexShaderConstantB, "IDirect3DDevice9::SetVertexShaderConstantB");
		HookManager.AddHook({ 0x675810 }, &IDirect3DDevice9__IsNull, "IDirect3DDevice9::IsNull");
		HookManager.AddHook({ 0x6758F0 }, &IDirect3DDevice9__CreateCubeTexture, "IDirect3DDevice9::CreateCubeTexture");
		HookManager.AddHook({ 0x675A00 }, &IDirect3DDevice9__CreateDepthStencilSurface__MultisampleNone, "IDirect3DDevice9::CreateDepthStencilSurface::MultisampleNone");
		HookManager.AddHook({ 0x675BD0 }, &IDirect3DDevice9__CreateVertexDeclaration, "IDirect3DDevice9::CreateVertexDeclaration");
		HookManager.AddHook({ 0x675E30 }, &IDirect3DDevice9__UpdateTexture, "IDirect3DDevice9::UpdateTexture");

		// incorrect implementations
		//HookManager.AddHook({ 0x623700 }, &sub_A23700, "sub_A23700");
		//HookManager.AddHook({ 0x675960 }, &IDirect3DDevice9__CreateIndexBuffer, "IDirect3DDevice9::CreateIndexBuffer");
		//HookManager.AddHook({ 0x6759B0 }, &IDirect3DDevice9__CreateVertexBuffer, "IDirect3DDevice9::CreateVertexBuffer");
		//HookManager.AddHook({ 0x675B20 }, &IDirect3DDevice9__CreateTexture, "IDirect3DDevice9::CreateTexture");
		//HookManager.AddHook({ 0x675C70 }, &IDirect3DDevice9__CreateVolumeTexture, "IDirect3DDevice9::CreateVolumeTexture");
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