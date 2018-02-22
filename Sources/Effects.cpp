#include "..\Headers\Effects.h"

ID3D10Effect* fx::SkyFX            = 0;
ID3D10Effect* fx::CubeMapFX		   = 0;
ID3D10Effect* fx::ShadowFX		   = 0;
ID3D10Effect* fx::DrawShadowMapFX  = 0;
ID3D10Effect* fx::NormalMapFX	   = 0;
ID3D10Effect* fx::TerrainFX        = 0;
ID3D10Effect* fx::MeshFX           = 0;
ID3D10Effect* fx::BuildShadowMapFX = 0;
ID3D10Effect* fx::FireFX           = 0;
ID3D10Effect* fx::RainFX           = 0;
 
ID3D10Effect* CreateFX(ID3D10Device* device, std::wstring filename)
{
	DWORD shaderFlags = D3D10_SHADER_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    shaderFlags |= D3D10_SHADER_DEBUG;
	shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif
  
	ID3D10Blob* compilationErrors = 0;
	HRESULT hr = 0;
	ID3D10Effect* fx = 0;
	hr = D3DX10CreateEffectFromFile(filename.c_str(), 0, 0, 
		"fx_4_0", shaderFlags, 0, device, 0, 0, &fx, &compilationErrors, 0);
	if(FAILED(hr))
	{
		if( compilationErrors )
		{
			MessageBoxA(0, (char*)compilationErrors->GetBufferPointer(), 0, 0);
			ReleaseCOM(compilationErrors);
		}
#ifdef defined(DEBUG) || (_DEBUG)
		DXTrace(__FILE__, (DWORD)__LINE__, hr, filename.c_str(), true);
#endif
	}

	return fx;
}

void fx::InitAll(ID3D10Device* device)
{
	SkyFX            = CreateFX(device, L"..\\Shaders\\sky.fx");
	CubeMapFX		 = CreateFX(device, L"..\\Shaders\\cubemap.fx");
	NormalMapFX		 = CreateFX(device, L"..\\Shaders\\normalmap.fx");
	ShadowFX         = CreateFX(device, L"..\\Shaders\\shadow.fx");
	DrawShadowMapFX  = CreateFX(device, L"..\\Shaders\\drawshadowmap.fx");
	TerrainFX        = CreateFX(device, L"..\\Shaders\\terrain.fx");
	MeshFX           = CreateFX(device, L"..\\Shaders\\mesh.fx");
	BuildShadowMapFX = CreateFX(device, L"..\\Shaders\\buildshadowmap.fx");
	FireFX           = CreateFX(device, L"..\\Shaders\\fire.fx");
	RainFX           = CreateFX(device, L"..\\Shaders\\rain.fx");
}

void fx::DestroyAll()
{
	ReleaseCOM(SkyFX);
	ReleaseCOM(CubeMapFX);
	ReleaseCOM(ShadowFX);
	ReleaseCOM(DrawShadowMapFX);
	ReleaseCOM(NormalMapFX);
	ReleaseCOM(TerrainFX);
	ReleaseCOM(MeshFX);
	ReleaseCOM(BuildShadowMapFX);
	ReleaseCOM(FireFX);
	ReleaseCOM(RainFX);
}