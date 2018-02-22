
#include "Headers/Quad.h"
#include "Headers/Cylinder.h"
#include "Headers/Sphere.h"
#include "Headers/RectangleBox.h"
#include "Headers/TriangleBox.h"
#include "Headers/WindowedBox.h"
#include "Headers/d3dApp.h"
#include "Headers/Light.h"
#include "Headers/Camera.h"
#include "Headers/Effects.h"
#include "Headers/InputLayouts.h"
#include "Headers/TextureMgr.h"
#include "Headers/Sky.h"
#include "Headers/DrawableTex2D.h"
#include "Headers/Mesh.h"
#include "Headers/Terrain.h"
#include "Headers/PSystem.h"
#include <vector>
#include <sstream>
using namespace std;

struct QuadVertex
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 texC;
};

class HouseApp : public D3DApp
{
public:
	HouseApp(HINSTANCE hInstance);
	~HouseApp();

	void initApp();
	void onResize();
	void updateScene(float dt);
	void drawScene();
	void drawSceneToShadowMap();
	void buildNDCQuad();

	LRESULT msgProc(UINT msg, WPARAM wParam, LPARAM lParam);
 
private:

	POINT mOldMousePos;

	Mesh mTreeMesh;

	Quad mHouseFloor;
	Cylinder mCylinder;
	RectangleBox mLeftWall;
	WindowedBox mRightWall;
	RectangleBox mWindow;
	RectangleBox mBackWall;
	RectangleBox mFrontWall;
	RectangleBox mRoof;
	Sphere mHouseTorch;
	RectangleBox mRoofLineL;
	RectangleBox mRoofLineR;
	TriangleBox mRoofTriL;
	TriangleBox mRoofTriR;
	Cylinder mFlagstock;
	RectangleBox mFlag;


	PSystem mFire;
	PSystem mRain;
	Terrain mLand;
	Sky mSky;

	// for drawing shadow map on screen
	ID3D10Buffer* mNDCQuadVB;

	D3DXMATRIX mFrontPane;
	D3DXMATRIX mRoofPane;
	D3DXMATRIX mRoofLineRPane;
	D3DXMATRIX mRoofLineLPane;

	D3DXMATRIX mTreeWorld;
	D3DXMATRIX mHouseTorchPos;
	D3DXMATRIX mFloorPos;
	D3DXMATRIX mCylinderPos;
	D3DXMATRIX mLeftWallPos;
	D3DXMATRIX mRightWallPos;
	D3DXMATRIX mWindowPos;
	D3DXMATRIX mBackWallPos;
	D3DXMATRIX mFrontWallPos;
	D3DXMATRIX mRoofPos;
	D3DXMATRIX mRoofLineLPos;
	D3DXMATRIX mRoofLineRPos;
	D3DXMATRIX mRoofTriLPos;
	D3DXMATRIX mRoofTriRPos;
	D3DXMATRIX mFlagstockPos;
	D3DXMATRIX mFlagPos;

	D3DXMATRIX mLandWorld;

	DrawableTex2D mShadowMap;
	Light mParallelLight;
	Light mHouseLight;

	D3DXVECTOR4 mReflectNone;
	D3DXVECTOR4 mReflectAll;

	D3DXMATRIX mLightView;
	D3DXMATRIX mHLightView;
	D3DXMATRIX mLightVolume;

	D3DXMATRIX mFloorTexMtx;
	D3DXMATRIX mIdentityTexMtx;

	ID3D10RasterizerState* mNoCullRS;

	ID3D10BlendState* mTransparentBS;

	ID3D10ShaderResourceView* mFloorMapRV;
	ID3D10ShaderResourceView* mFloorNormalMapRV;
	ID3D10ShaderResourceView* mWindowMapRV;
	ID3D10ShaderResourceView* mFlareMapRV;
	ID3D10ShaderResourceView* mWindowWallMapRV;
	ID3D10ShaderResourceView* mWall10x5MapRV;
	ID3D10ShaderResourceView* mWall20x5MapRV;
	ID3D10ShaderResourceView* mWallDoorMapRV;
	ID3D10ShaderResourceView* mBrickNormalMapRV;
	ID3D10ShaderResourceView* mRoofTriMapRV;
	ID3D10ShaderResourceView* mRoofMapRV;
	ID3D10ShaderResourceView* mRoofLineMapRV;
	ID3D10ShaderResourceView* mFlagMapRV;
	ID3D10ShaderResourceView* mDoorWallMapRV;
	ID3D10ShaderResourceView* mDoorMapRV;
	ID3D10ShaderResourceView* mBaseMapRV;
	ID3D10ShaderResourceView* mBaseNormalMapRV;

	ID3D10ShaderResourceView* mSpecMapRV;
	ID3D10ShaderResourceView* mDefaultSpecMapRV;
	ID3D10ShaderResourceView* mDefaultNormalMapRV;
	ID3D10ShaderResourceView* mEnvMapRV;
 
	ID3D10EffectTechnique* mTech;
	ID3D10EffectVariable* mfxLightVar;
	ID3D10EffectVariable* mfxEyePosVar;
	ID3D10EffectMatrixVariable* mfxLightWVPVar;
	ID3D10EffectMatrixVariable* mfxWVPVar;
	ID3D10EffectMatrixVariable* mfxWorldVar;
	ID3D10EffectMatrixVariable* mfxTexMtxVar;
	ID3D10EffectVectorVariable* mfxReflectMtrlVar;
	ID3D10EffectScalarVariable* mfxCubeMapEnabledVar;
	ID3D10EffectShaderResourceVariable* mfxDiffuseMapVar;
	ID3D10EffectShaderResourceVariable* mfxSpecMapVar;
	ID3D10EffectShaderResourceVariable* mfxNormalMapVar;
	ID3D10EffectShaderResourceVariable* mfxShadowMapVar;
	ID3D10EffectShaderResourceVariable* mfxCubeMapVar;


	ID3D10EffectTechnique* mBuildShadowMapTech;
	ID3D10EffectMatrixVariable* mfxBuildShadowMapLightWVPVar;
	ID3D10EffectShaderResourceVariable* mfxBuildShadowMapDiffuseMapVar;

	ID3D10EffectTechnique* mDrawShadowMapTech;
	ID3D10EffectShaderResourceVariable* mfxDrawShadowMapTexVar;

	bool notRained;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
				   PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif


	HouseApp theApp(hInstance);
	
	theApp.initApp();

	return theApp.run();
}

HouseApp::HouseApp(HINSTANCE hInstance)
: D3DApp(hInstance), mEnvMapRV(0)
{
	notRained = false;

	D3DXMatrixIdentity(&mLandWorld);

	D3DXMatrixIdentity(&mFloorPos);
	//D3DXMatrixRotationY(&mFloorPos, PI/2);
	//D3DXMatrixIdentity(&mCylinderPos);
	//D3DXMatrixTranslation(&mCylinderPos, 21.6622f, -19.0198f, -115.983f);

	D3DXMatrixTranslation(&mTreeWorld, 43.687f, -19.443f, -113.09f);

	D3DXMatrixRotationY(&mFrontPane, PI/2);
	D3DXMatrixRotationZ(&mRoofPane, PI/2);
	D3DXMatrixRotationZ(&mRoofLineLPane, PI/4);
	D3DXMatrixRotationZ(&mRoofLineRPane, -PI/4);

	D3DXMatrixTranslation(&mCylinderPos, 38.4861f, -18.4183f, -140.024f);
	D3DXMatrixTranslation(&mFloorPos, 21.6622f, -19.0198f, -115.983f);

	D3DXMatrixTranslation(&mLeftWallPos, 0, 2.5f, -10);
	D3DXMatrixTranslation(&mRightWallPos, 0, 2.5f, 10);
	D3DXMatrixTranslation(&mFrontWallPos, -5, 2.5f, 0);
	D3DXMatrixTranslation(&mBackWallPos, 5, 2.5f, 0);
	D3DXMatrixTranslation(&mRoofPos, 0, 5.0f, 0);
	D3DXMatrixTranslation(&mRoofLineLPos, 2.5f, 7.5, 0);
	D3DXMatrixTranslation(&mRoofLineRPos, -2.5f, 7.5, 0);
	D3DXMatrixTranslation(&mRoofTriLPos, 0, 5.0f, 10);
	D3DXMatrixTranslation(&mRoofTriRPos, 0, 5.0f, -10);
	D3DXMatrixTranslation(&mWindowPos, 0, 2.5f, 10);
	D3DXMatrixTranslation(&mFlagstockPos, 0, 12.5f, -10);
	D3DXMatrixTranslation(&mFlagPos, 0, 14.0f, -12);
	D3DXMatrixTranslation(&mHouseTorchPos, 0.0f, 4.2f, 0.0f);

	mLeftWallPos = mLeftWallPos * mFloorPos;
	mRightWallPos = mRightWallPos * mFloorPos;
	mFrontWallPos = mFrontPane * mFrontWallPos * mFloorPos;
	mBackWallPos = mFrontPane * mBackWallPos * mFloorPos;
	mRoofPos = mFrontPane * mRoofPane * mRoofPos * mFloorPos;
	mRoofLineLPos = mFrontPane * mRoofLineLPane * mRoofLineLPos * mFloorPos;
	mRoofLineRPos = mFrontPane * mRoofLineRPane * mRoofLineRPos * mFloorPos;
	mRoofTriLPos = mRoofTriLPos * mFloorPos;
	mRoofTriRPos = mRoofTriRPos * mFloorPos;
	mWindowPos = mWindowPos * mFloorPos;
	mFlagstockPos = mFlagstockPos * mFloorPos;
	mFlagPos = mFrontPane * mFlagPos * mFloorPos;
	mHouseTorchPos = mHouseTorchPos * mFloorPos;

	//D3DXMatrixScaling(&mFloorTexMtx, 10.0f, 20.0f, 1.0f);
	D3DXMatrixRotationZ(&mFloorTexMtx, PI/2);
	D3DXMatrixIdentity(&mIdentityTexMtx);

	D3DXVECTOR3 mHlightPos;
	mHlightPos.x = 0.0f+21.6622f;
	mHlightPos.y = 4.2f-19.0198f;
	mHlightPos.z = 0.0f-115.983f;

	D3DXMatrixLookAtLH(&mHLightView, &mHlightPos,
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.0f, 0.0f, 1.0f));

	D3DXVECTOR3 HlightDirection = -mHlightPos;
	D3DXVec3Normalize(&mHouseLight.dir, &HlightDirection);
 
	mReflectNone = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);
	mReflectAll  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
}

HouseApp::~HouseApp()
{
	if( md3dDevice )
		md3dDevice->ClearState();

	//ReleaseCOM(mNDCQuadVB);

	fx::DestroyAll();
	InputLayout::DestroyAll();
}

void HouseApp::initApp()
{
	D3DApp::initApp();

	fx::InitAll(md3dDevice);
	InputLayout::InitAll(md3dDevice);
	GetTextureMgr().init(md3dDevice);

	mTech                = fx::ShadowFX->GetTechniqueByName("ShadowTech");
	mfxLightVar          = fx::ShadowFX->GetVariableByName("gLight");
	mfxEyePosVar         = fx::ShadowFX->GetVariableByName("gEyePosW");
	mfxLightWVPVar       = fx::ShadowFX->GetVariableByName("gLightWVP")->AsMatrix();
	mfxWVPVar            = fx::ShadowFX->GetVariableByName("gWVP")->AsMatrix();
	mfxWorldVar          = fx::ShadowFX->GetVariableByName("gWorld")->AsMatrix();
	mfxTexMtxVar         = fx::ShadowFX->GetVariableByName("gTexMtx")->AsMatrix();
	mfxReflectMtrlVar    = fx::ShadowFX->GetVariableByName("gReflectMtrl")->AsVector();
	mfxCubeMapEnabledVar = fx::ShadowFX->GetVariableByName("gCubeMapEnabled")->AsScalar();
	mfxDiffuseMapVar     = fx::ShadowFX->GetVariableByName("gDiffuseMap")->AsShaderResource();
	mfxSpecMapVar        = fx::ShadowFX->GetVariableByName("gSpecMap")->AsShaderResource();
	mfxNormalMapVar      = fx::ShadowFX->GetVariableByName("gNormalMap")->AsShaderResource();
	mfxShadowMapVar      = fx::ShadowFX->GetVariableByName("gShadowMap")->AsShaderResource();
	mfxCubeMapVar        = fx::ShadowFX->GetVariableByName("gCubeMap")->AsShaderResource();

	mBuildShadowMapTech            = fx::BuildShadowMapFX->GetTechniqueByName("BuildShadowMapTech");
	mfxBuildShadowMapLightWVPVar   = fx::BuildShadowMapFX->GetVariableByName("gLightWVP")->AsMatrix();
	mfxBuildShadowMapDiffuseMapVar = fx::BuildShadowMapFX->GetVariableByName("gDiffuseMap")->AsShaderResource();

	mDrawShadowMapTech     = fx::DrawShadowMapFX->GetTechniqueByName("DrawShadowMapTech");
	mfxDrawShadowMapTexVar = fx::DrawShadowMapFX->GetVariableByName("gShadowMap")->AsShaderResource();

	D3D10_RASTERIZER_DESC rsDesc;
	ZeroMemory(&rsDesc, sizeof(D3D10_RASTERIZER_DESC));
	rsDesc.FillMode = D3D10_FILL_SOLID;
	rsDesc.CullMode = D3D10_CULL_NONE;
	rsDesc.FrontCounterClockwise = false;

	HR(md3dDevice->CreateRasterizerState(&rsDesc, &mNoCullRS));

	//buildNDCQuad();

	mShadowMap.init(md3dDevice, 1024, 1024, false, DXGI_FORMAT_UNKNOWN);

	mTreeMesh.init(md3dDevice, L"..\\Models\\tree.m3d");
	mTreeMesh.setCubeMap(mEnvMapRV);

	mClearColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//GetCamera().position() = D3DXVECTOR3(0.0f, 1.8f, -10.0f);
	GetCamera().position() = D3DXVECTOR3(59.9314f, -9.44619f, -161.012f);

	mFloorMapRV         = GetTextureMgr().createTex(L"..\\Textures\\House\\floor.dds");
	mFloorNormalMapRV   = GetTextureMgr().createTex(L"..\\Textures\\House\\floor.dds");
	mFlareMapRV         = GetTextureMgr().createTex(L"..\\Textures\\Flare\\flare.dds");
	mWindowMapRV        = GetTextureMgr().createTex(L"..\\Textures\\House\\window.dds");
	mWindowWallMapRV    = GetTextureMgr().createTex(L"..\\Textures\\House\\wall_window.dds");
	mWall10x5MapRV      = GetTextureMgr().createTex(L"..\\Textures\\House\\wall_10x5.dds");
	mWall20x5MapRV      = GetTextureMgr().createTex(L"..\\Textures\\House\\wall_20x5.dds");
	mDoorWallMapRV      = GetTextureMgr().createTex(L"..\\Textures\\House\\wall_20x5_door_arc.dds");
	mDoorMapRV          = GetTextureMgr().createTex(L"..\\Textures\\House\\wall_20x5.dds");
	mRoofMapRV          = GetTextureMgr().createTex(L"..\\Textures\\House\\ceiling.dds");
	mRoofLineMapRV      = GetTextureMgr().createTex(L"..\\Textures\\House\\roof.dds");
	mRoofTriMapRV       = GetTextureMgr().createTex(L"..\\Textures\\House\\roof_triangle.dds");
	mBrickNormalMapRV   = GetTextureMgr().createTex(L"..\\Textures\\Brick\\bricks_normal.dds");
	mFlagMapRV          = GetTextureMgr().createTex(L"..\\Textures\\House\\Russian.jpg");
	mBaseMapRV          = GetTextureMgr().createTex(L"..\\Textures\\Stone\\stone_diffuse.dds");
	mBaseNormalMapRV    = GetTextureMgr().createTex(L"..\\Textures\\Stone\\stone_normal.dds");
	mSpecMapRV			= GetTextureMgr().createTex(L"..\\Textures\\Default\\spec.dds");
	mDefaultSpecMapRV	= GetTextureMgr().createTex(L"..\\Textures\\Default\\defaultspec.dds");
	mDefaultNormalMapRV = GetTextureMgr().createTex(L"..\\Textures\\Default\\default_normal.dds");
	mEnvMapRV = GetTextureMgr().createCubeTex(L"..\\Textures\\EnvMap\\grassenvmap1024.dds");

	mHouseFloor.init(md3dDevice, 21, 11, 1);
	mCylinder.init(md3dDevice, 0.1f, 0.1f, 5, 30, 30);
	mLeftWall.init(md3dDevice, 5.0f, 2.5f, 0.03125f, 1);
	mRightWall.init(md3dDevice, 5.0f, 2.5f, 1, 1, 0.03125f, 1);
	mWindow.init(md3dDevice, 1, 1, 0.03125f, 1);
	mFrontWall.init(md3dDevice, 10.0f, 2.5f, 0.03125f, 1);
	mBackWall.init(md3dDevice, 10.0f, 2.5f, 0.03125f, 1);
	mRoof.init(md3dDevice, 10.0f, 5.0f, 0.03125f, 1);
	mRoofLineL.init(md3dDevice, 10.0f, sqrt(50.0f)/2, 0.03125f, 1);
	mRoofLineR.init(md3dDevice, 10.0f, sqrt(50.0f)/2, 0.03125f, 1);
	mRoofTriL.init(md3dDevice, -5, 0, 0, 5, 5, 0, 0.03125f, 1);
	mRoofTriR.init(md3dDevice, -5, 0, 0, 5, 5, 0, 0.03125f, 1);
	mFlagstock.init(md3dDevice, 0.05f, 0.05f, 5, 30, 30);
	mFlag.init(md3dDevice, 2.0f, 1.0f, 0.03125f, 1);
	mHouseTorch.init(md3dDevice, 0.1f, 30, 30);

	mSky.init(md3dDevice, mEnvMapRV, 5000.0f);

	Terrain::InitInfo tii;
	tii.HeightmapFilename = L"..\\Heightmap\\terrain1.raw";
	tii.LayerMapFilename0 = L"..\\Textures\\LandTex\\grass.dds";
	tii.LayerMapFilename1 = L"..\\Textures\\LandTex\\lightdirt.dds";
	tii.LayerMapFilename2 = L"..\\Textures\\LandTex\\darkdirt.dds";
	tii.LayerMapFilename3 = L"..\\Textures\\Stone\\stone.dds";
	tii.LayerMapFilename4 = L"..\\Textures\\Snow\\snow.dds";
	tii.BlendMapFilename  = L"..\\Textures\\Default\\blend.dds";
	tii.HeightScale  = 0.25f;
	tii.HeightOffset = -20.0f;
	tii.NumRows      = 513;
	tii.NumCols      = 513;
	tii.CellSpacing  = 1.0f;
	
	D3D10_BLEND_DESC blendDesc = {0};
	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.BlendEnable[0] = true;
	blendDesc.SrcBlend       = D3D10_BLEND_SRC_ALPHA;
	blendDesc.DestBlend      = D3D10_BLEND_INV_SRC_ALPHA;
	blendDesc.BlendOp        = D3D10_BLEND_OP_ADD;
	blendDesc.SrcBlendAlpha  = D3D10_BLEND_ONE;
	blendDesc.DestBlendAlpha = D3D10_BLEND_ZERO;
	blendDesc.BlendOpAlpha   = D3D10_BLEND_OP_ADD;
	blendDesc.RenderTargetWriteMask[0] = D3D10_COLOR_WRITE_ENABLE_ALL;

	HR(md3dDevice->CreateBlendState(&blendDesc, &mTransparentBS));

	vector<wstring> flares;
	flares.push_back(L"..\\Textures\\Flare\\flare0.dds"); 
	ID3D10ShaderResourceView* texArray = GetTextureMgr().createTexArray(L"flares", flares);

	vector<wstring> raindrops;
	raindrops.push_back(L"..\\Textures\\Rain\\raindrop.dds"); 
	texArray = GetTextureMgr().createTexArray(L"raindrops", raindrops);

	mLand.init(md3dDevice, tii);
	mFire.init(md3dDevice, fx::FireFX, texArray, 500); 
	mRain.init(md3dDevice, fx::RainFX, texArray, 10000); 
 
	mParallelLight.dir      = D3DXVECTOR3(0.707f, -0.707f, 0.0f);
	mParallelLight.ambient  = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
	mParallelLight.diffuse  = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
	mParallelLight.specular = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

	mHouseLight.dir      = D3DXVECTOR3(0.707f, -0.707f, 0.0f);
	mHouseLight.ambient  = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
	mHouseLight.diffuse  = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	mHouseLight.specular = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

	//D3DXMatrixOrthoOffCenterLH(&mLightVolume, 25.4858f, 60.0411f, -29.2042f, 47.5315f, -129.811f, -89.9145f);
	//D3DXMatrixOrthoLH(&mLightVolume, 100.0f, 100.0f, 1.0f, 800.0f);
	//D3DXMatrixTranslation(&mLightVolume, 100, 100, 100);
	//D3DXMatrixOrthoLH(&mLightVolume, 30.0f, 30.0f, 1.0f, 100.0f);
	mLand.setDirectionToSun(-mParallelLight.dir);
}

void HouseApp::onResize()
{
	D3DApp::onResize();

	float aspect = (float)mClientWidth/mClientHeight;
	GetCamera().setLens(0.25f*PI, aspect, 0.5f, 1000.0f);
}

void HouseApp::updateScene(float dt)
{
	D3DApp::updateScene(dt);

	if(GetAsyncKeyState('A') & 0x8000)	GetCamera().strafe(-20.0f*dt);
	if(GetAsyncKeyState('D') & 0x8000)	GetCamera().strafe(+20.0f*dt);
	if(GetAsyncKeyState('W') & 0x8000)	GetCamera().walk(+20.0f*dt);
	if(GetAsyncKeyState('S') & 0x8000)	GetCamera().walk(-20.0f*dt);

	if(GetAsyncKeyState('R') & 0x8000)
	{
		mFire.reset();
		mRain.reset();
	}
 
	GetCamera().rebuildView();

	mFire.update(dt, mTimer.getGameTime());
	mRain.update(dt, mTimer.getGameTime());

	/*
	// Animate light and keep shadow in sync.
	D3DXVECTOR3 lightPos;
	lightPos.x = 300.0f*cosf(0.25f*mTimer.getGameTime());
	lightPos.y = 200.0f;
	lightPos.z = 300.0f*sinf(0.25f*mTimer.getGameTime());
	*/

	// Animate light and keep shadow in sync.
	D3DXVECTOR3 lightPos;
	lightPos.x = 30.0f*cosf(0.25f*mTimer.getGameTime());
	lightPos.y = 20.0f;
	lightPos.z = 30.0f*sinf(0.25f*mTimer.getGameTime());

	D3DXMatrixLookAtLH(&mLightView, &lightPos,
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	D3DXVECTOR3 lightDirection = -lightPos;
	D3DXVec3Normalize(&mParallelLight.dir, &lightDirection);

	float cx = GetCamera().position().x - 21.6622f;
	float cz = GetCamera().position().z + 115.983f;
	float mx = 5;
	float mz = 10;

	if (!notRained && ((abs(cx) <= mx) || (abs(cz) <= mz)))
	{
		mRain.pause();
		notRained = true;
	}

	if (notRained && ((abs(cx) > mx) || (abs(cz) > mz)))
	{
		mRain.resume();
		notRained = false;
	}

	mLand.setDirectionToSun(-mParallelLight.dir);
}

void HouseApp::drawScene()
{
	D3DApp::drawScene();

	md3dDevice->OMSetDepthStencilState(0, 0);
	float blendFactor[] = {0.0f, 0.0f, 0.0f, 0.0f};
	md3dDevice->OMSetBlendState(0, blendFactor, 0xffffffff);

	static float r;
	D3DXMATRIX wr, wt, wtr;
	D3DXMatrixIdentity(&wr);
	D3DXMatrixTranslation(&wt, 2, 0, 0);
	D3DXMatrixRotationY(&wr, r);
	D3DXMatrixTranslation(&wtr, -2, 0, 0);
	r += 0.001f;

	md3dDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	mLand.draw(mLandWorld);
	mSky.draw();

	md3dDevice->IASetInputLayout(InputLayout::PosShadowTangentNormalTex);

	// Set per frame constants.
	mfxEyePosVar->SetRawValue(&GetCamera().position(), 0, sizeof(D3DXVECTOR3));
	mfxLightVar->SetRawValue(&mParallelLight, 0, sizeof(Light));
	mfxCubeMapVar->SetResource(mEnvMapRV);
	mfxShadowMapVar->SetResource(mShadowMap.depthMap());
 
	//
	// Draw scene to the shadow map.
	//

	mShadowMap.begin();

	drawSceneToShadowMap();

	mShadowMap.end();

	// restore rendering to backbuffer
	resetOMTargetsAndViewport();

	//
	// Draw a quad with shadow map as texture to the screen so we can see
	// what the shadow map looks like.
	//
	//	UINT stride = sizeof(QuadVertex);
	//    UINT offset = 0;
	//    md3dDevice->IASetVertexBuffers(0, 1, &mNDCQuadVB, &stride, &offset);
	//	md3dDevice->IASetInputLayout(InputLayout::PosTex);
	//	mfxDrawShadowMapTexVar->SetResource(mShadowMap.depthMap());
	//
	//	ID3D10EffectPass* pass = mDrawShadowMapTech->GetPassByIndex(0);
	//	pass->Apply(0);
	//	md3dDevice->Draw(6, 0);
	//
	//
	// Draw the rest of the scene.
	//

	md3dDevice->IASetInputLayout(InputLayout::PosShadowTangentNormalTex);

	// Set per frame constants.
	mfxEyePosVar->SetRawValue(&GetCamera().position(), 0, sizeof(D3DXVECTOR3));
	mfxLightVar->SetRawValue(&mParallelLight, 0, sizeof(Light));

	mfxCubeMapVar->SetResource(mEnvMapRV);
	mfxShadowMapVar->SetResource(mShadowMap.depthMap());

	D3DXMATRIX view = GetCamera().view();
	D3DXMATRIX proj = GetCamera().proj();

	// Don't back face cull for tree, since we want to see both sides of leaf triangles.
	md3dDevice->RSSetState(mNoCullRS);
	mTreeMesh.setLight(mHouseLight);
	mTreeMesh.draw(mTreeWorld, mLightView*mLightVolume);
	md3dDevice->RSSetState(0); // restore default

    D3D10_TECHNIQUE_DESC techDesc;
    mTech->GetDesc( &techDesc );

	for(UINT i = 0; i < techDesc.Passes; ++i)
	{
		ID3D10EffectPass* pass = mTech->GetPassByIndex(i);
		//
		// draw columns
		//
		mfxTexMtxVar->SetMatrix((float*)&mIdentityTexMtx);
		mfxCubeMapEnabledVar->SetBool(false);
		mfxReflectMtrlVar->SetFloatVector((float*)&mReflectNone);
		mfxDiffuseMapVar->SetResource(mBaseMapRV);
		mfxNormalMapVar->SetResource(mBaseNormalMapRV);
		mfxSpecMapVar->SetResource(mSpecMapRV);
		mfxWVPVar->SetMatrix((float*)&(mCylinderPos*view*proj));
		mfxLightWVPVar->SetMatrix((float*)&(mCylinderPos*mLightView*mLightVolume));
		mfxWorldVar->SetMatrix((float*)&mCylinderPos);
		pass->Apply(0);
		mCylinder.draw();

		mfxLightVar->SetRawValue(&mHouseLight, 0, sizeof(Light));
		//
		// draw floor
		//
		mfxWVPVar->SetMatrix((float*)&(mFloorPos*view*proj));
		mfxLightWVPVar->SetMatrix((float*)&(mFloorPos*/*mLightView*/mHLightView*mLightVolume));
		mfxWorldVar->SetMatrix((float*)&mFloorPos);
		mfxTexMtxVar->SetMatrix((float*)&mFloorTexMtx);
		mfxDiffuseMapVar->SetResource(mFloorMapRV);
		mfxNormalMapVar->SetResource(mFloorNormalMapRV);
		mfxSpecMapVar->SetResource(mSpecMapRV);
		mfxCubeMapEnabledVar->SetBool(false);
		mfxReflectMtrlVar->SetFloatVector((float*)&mReflectNone);
		pass->Apply(0);
		mHouseFloor.draw();

		//
		// draw left wall
		//
		mfxTexMtxVar->SetMatrix((float*)&mIdentityTexMtx);
		mfxCubeMapEnabledVar->SetBool(false);
		mfxReflectMtrlVar->SetFloatVector((float*)&mReflectNone);
		mfxDiffuseMapVar->SetResource(mWall10x5MapRV);
		mfxNormalMapVar->SetResource(mBrickNormalMapRV);
		mfxSpecMapVar->SetResource(mSpecMapRV);
		mfxWVPVar->SetMatrix((float*)&(mLeftWallPos*view*proj));
		mfxLightWVPVar->SetMatrix((float*)&(mLeftWallPos*/*mLightView*/mHLightView*mLightVolume));
		mfxWorldVar->SetMatrix((float*)&mLeftWallPos);
		pass->Apply(0);
		mLeftWall.draw();

		//
		// draw right wall
		//
		mfxTexMtxVar->SetMatrix((float*)&mIdentityTexMtx);
		mfxCubeMapEnabledVar->SetBool(false);
		mfxReflectMtrlVar->SetFloatVector((float*)&mReflectNone);
		mfxDiffuseMapVar->SetResource(mWindowWallMapRV);
		mfxNormalMapVar->SetResource(mBrickNormalMapRV);
		mfxSpecMapVar->SetResource(mSpecMapRV);
		mfxWVPVar->SetMatrix((float*)&(mRightWallPos*view*proj));
		mfxLightWVPVar->SetMatrix((float*)&(mRightWallPos*/*mLightView*/mHLightView*mLightVolume));
		mfxWorldVar->SetMatrix((float*)&mRightWallPos);
		pass->Apply(0);
		mRightWall.draw();

		//
		// draw front wall
		//
		mfxTexMtxVar->SetMatrix((float*)&mIdentityTexMtx);
		mfxCubeMapEnabledVar->SetBool(false);
		mfxReflectMtrlVar->SetFloatVector((float*)&mReflectNone);
		mfxDiffuseMapVar->SetResource(mWall20x5MapRV);
		mfxNormalMapVar->SetResource(mBrickNormalMapRV);
		mfxSpecMapVar->SetResource(mSpecMapRV);
		mfxWVPVar->SetMatrix((float*)&(mFrontWallPos*view*proj));
		mfxLightWVPVar->SetMatrix((float*)&(mFrontWallPos*/*mLightView*/mHLightView*mLightVolume));
		mfxWorldVar->SetMatrix((float*)&mFrontWallPos);
		pass->Apply(0);
		mFrontWall.draw();

		//
		// draw back wall
		//
		mfxTexMtxVar->SetMatrix((float*)&mIdentityTexMtx);
		mfxCubeMapEnabledVar->SetBool(false);
		mfxReflectMtrlVar->SetFloatVector((float*)&mReflectNone);
		mfxDiffuseMapVar->SetResource(mDoorWallMapRV);
		mfxNormalMapVar->SetResource(mBrickNormalMapRV);
		mfxSpecMapVar->SetResource(mSpecMapRV);
		mfxWVPVar->SetMatrix((float*)&(mBackWallPos*view*proj));
		mfxLightWVPVar->SetMatrix((float*)&(mBackWallPos*/*mLightView*/mHLightView*mLightVolume));
		mfxWorldVar->SetMatrix((float*)&mBackWallPos);
		pass->Apply(0);
		mBackWall.draw();

		//
		// draw roof
		//
		mfxTexMtxVar->SetMatrix((float*)&mIdentityTexMtx);
		mfxCubeMapEnabledVar->SetBool(false);
		mfxReflectMtrlVar->SetFloatVector((float*)&mReflectNone);
		mfxDiffuseMapVar->SetResource(mRoofMapRV);
		mfxNormalMapVar->SetResource(mDefaultNormalMapRV);
		mfxSpecMapVar->SetResource(mSpecMapRV);
		mfxWVPVar->SetMatrix((float*)&(mRoofPos*view*proj));
		mfxLightWVPVar->SetMatrix((float*)&(mRoofPos*/*mLightView*/mHLightView*mLightVolume));
		mfxWorldVar->SetMatrix((float*)&mRoofPos);
		pass->Apply(0);
		mRoof.draw();

		mfxLightVar->SetRawValue(&mParallelLight, 0, sizeof(Light));
		//
		// draw roof line l
		//
		mfxTexMtxVar->SetMatrix((float*)&mIdentityTexMtx);
		mfxCubeMapEnabledVar->SetBool(false);
		mfxReflectMtrlVar->SetFloatVector((float*)&mReflectNone);
		mfxDiffuseMapVar->SetResource(mRoofLineMapRV);
		mfxNormalMapVar->SetResource(mDefaultNormalMapRV);
		mfxSpecMapVar->SetResource(mSpecMapRV);
		mfxWVPVar->SetMatrix((float*)&(mRoofLineLPos*view*proj));
		mfxLightWVPVar->SetMatrix((float*)&(mRoofLineLPos*mLightView*mLightVolume));
		mfxWorldVar->SetMatrix((float*)&mRoofLineLPos);
		pass->Apply(0);
		mRoofLineL.draw();

		//
		// draw roof line r
		//
		mfxTexMtxVar->SetMatrix((float*)&mIdentityTexMtx);
		mfxCubeMapEnabledVar->SetBool(false);
		mfxReflectMtrlVar->SetFloatVector((float*)&mReflectNone);
		mfxDiffuseMapVar->SetResource(mRoofLineMapRV);
		mfxNormalMapVar->SetResource(mDefaultNormalMapRV);
		mfxSpecMapVar->SetResource(mSpecMapRV);
		mfxWVPVar->SetMatrix((float*)&(mRoofLineRPos*view*proj));
		mfxLightWVPVar->SetMatrix((float*)&(mRoofLineRPos*mLightView*mLightVolume));
		mfxWorldVar->SetMatrix((float*)&mRoofLineRPos);
		pass->Apply(0);
		mRoofLineR.draw();

		//
		// draw torch
		//
		
		mfxTexMtxVar->SetMatrix((float*)&mIdentityTexMtx);
		mfxCubeMapEnabledVar->SetBool(false);
		mfxReflectMtrlVar->SetFloatVector((float*)&mReflectNone);
		mfxDiffuseMapVar->SetResource(mFlareMapRV);
		mfxNormalMapVar->SetResource(mDefaultNormalMapRV);
		mfxSpecMapVar->SetResource(mSpecMapRV);
		mfxWVPVar->SetMatrix((float*)&(mHouseTorchPos*view*proj));
		mfxLightWVPVar->SetMatrix((float*)&(mHouseTorchPos*mLightView*mLightVolume));
		mfxWorldVar->SetMatrix((float*)&mHouseTorchPos);
		pass->Apply(0);
		mHouseTorch.draw();
		
		//
		// draw roof triangle l
		//
		mfxTexMtxVar->SetMatrix((float*)&mIdentityTexMtx);
		mfxCubeMapEnabledVar->SetBool(false);
		mfxReflectMtrlVar->SetFloatVector((float*)&mReflectNone);
		mfxDiffuseMapVar->SetResource(mRoofTriMapRV);
		mfxNormalMapVar->SetResource(mDefaultNormalMapRV);
		mfxSpecMapVar->SetResource(mSpecMapRV);
		mfxWVPVar->SetMatrix((float*)&(mRoofTriLPos*view*proj));
		mfxLightWVPVar->SetMatrix((float*)&(mRoofTriLPos*mLightView*mLightVolume));
		mfxWorldVar->SetMatrix((float*)&mRoofTriLPos);
		pass->Apply(0);
		mRoofTriL.draw();

		//
		// draw roof triangle r
		//
		mfxTexMtxVar->SetMatrix((float*)&mIdentityTexMtx);
		mfxCubeMapEnabledVar->SetBool(false);
		mfxReflectMtrlVar->SetFloatVector((float*)&mReflectNone);
		mfxDiffuseMapVar->SetResource(mRoofTriMapRV);
		mfxNormalMapVar->SetResource(mDefaultNormalMapRV);
		mfxSpecMapVar->SetResource(mSpecMapRV);
		mfxWVPVar->SetMatrix((float*)&(mRoofTriRPos*view*proj));
		mfxLightWVPVar->SetMatrix((float*)&(mRoofTriRPos*mLightView*mLightVolume));
		mfxWorldVar->SetMatrix((float*)&mRoofTriRPos);
		pass->Apply(0);
		mRoofTriR.draw();

		//
		// draw flagstock
		//
		mfxTexMtxVar->SetMatrix((float*)&mIdentityTexMtx);
		mfxCubeMapEnabledVar->SetBool(false);
		mfxReflectMtrlVar->SetFloatVector((float*)&mReflectNone);
		mfxDiffuseMapVar->SetResource(mBaseMapRV);
		mfxNormalMapVar->SetResource(mDefaultNormalMapRV);
		mfxSpecMapVar->SetResource(mSpecMapRV);
		mfxWVPVar->SetMatrix((float*)&(wr*mFlagstockPos*view*proj));
		mfxLightWVPVar->SetMatrix((float*)&(wr*mFlagstockPos*mLightView*mLightVolume));
		mfxWorldVar->SetMatrix((float*)&(wr*mFlagstockPos));
		pass->Apply(0);
		mFlagstock.draw();

		//
		// draw flag
		//
		mfxTexMtxVar->SetMatrix((float*)&mIdentityTexMtx);
		mfxCubeMapEnabledVar->SetBool(false);
		mfxReflectMtrlVar->SetFloatVector((float*)&mReflectNone);
		mfxDiffuseMapVar->SetResource(mFlagMapRV);
		mfxNormalMapVar->SetResource(mDefaultNormalMapRV);
		mfxSpecMapVar->SetResource(mSpecMapRV);
		mfxWVPVar->SetMatrix((float*)&(wt*wr*wtr*mFlagPos*view*proj));
		mfxLightWVPVar->SetMatrix((float*)&(wt*wr*wtr*mFlagPos*mLightView*mLightVolume));
		mfxWorldVar->SetMatrix((float*)&(wt*wr*wtr*mFlagPos));
		pass->Apply(0);
		mFlag.draw();

		//
		// draw window
		//
		mfxTexMtxVar->SetMatrix((float*)&mIdentityTexMtx);
		mfxCubeMapEnabledVar->SetBool(true);
		mfxReflectMtrlVar->SetFloatVector((float*)&mReflectAll);
		mfxDiffuseMapVar->SetResource(mWindowMapRV);
		mfxNormalMapVar->SetResource(mDefaultNormalMapRV);
		mfxSpecMapVar->SetResource(mSpecMapRV);
		mfxWVPVar->SetMatrix((float*)&(mWindowPos*view*proj));
		mfxLightWVPVar->SetMatrix((float*)&(mWindowPos*mHLightView*mLightVolume));
		mfxWorldVar->SetMatrix((float*)&mWindowPos);
		pass->Apply(0);
		md3dDevice->OMSetBlendState(mTransparentBS, blendFactor, 0xffffffff);
		mWindow.draw();

		// Unbind shadow map from shader stage since we will be binding it
		// as a depth buffer when we rebuild the shadow map the next frame.
		mfxShadowMapVar->SetResource(0);
		pass->Apply(0);
	}
	md3dDevice->OMSetBlendState( 0, blendFactor, 0xffffffff);
	

	// Draw particle systems last so it is blended with scene.
	mFire.setEmitPos(D3DXVECTOR3(38.4861f, -14.4183f, -140.024f));
	mFire.setEyePos(GetCamera().position());
	mFire.draw();
	
	md3dDevice->OMSetBlendState(0, blendFactor, 0xffffffff); // restore default
	mRain.setEyePos(GetCamera().position());
	mRain.setEmitPos(GetCamera().position());
	mRain.draw();

	// We specify DT_NOCLIP, so we do not care about width/height of the rect.
	RECT R = {5, 5, 0, 0};
	md3dDevice->RSSetState(0);
	
	//std::wostringstream outs;   
	//outs.precision(6);
	//outs << mFrameStats.c_str();
	//outs << L"\n POS: X:" << GetCamera().position().x << " Y:" << GetCamera().position().y << " Z:" << GetCamera().position().z;
	//mFrameStats = outs.str();
	mFont->DrawText(0, mFrameStats.c_str(), -1, &R, DT_NOCLIP, WHITE);

	mSwapChain->Present(0, 0);
}

void HouseApp::drawSceneToShadowMap()
{
	D3D10_TECHNIQUE_DESC techDesc;
	mBuildShadowMapTech->GetDesc( &techDesc );

	//mLand.draw(mLandWorld);

	//md3dDevice->IASetInputLayout(InputLayout::PosShadowTangentNormalTex);

	for(UINT i = 0; i < techDesc.Passes; ++i)
	{
		ID3D10EffectPass* pass = mBuildShadowMapTech->GetPassByIndex(i);

		//
		// draw floor
		//
		D3DXMATRIX floorWVP = mFloorPos*mLightView*mLightVolume;
		mfxBuildShadowMapLightWVPVar->SetMatrix((float*)&floorWVP);
		mfxBuildShadowMapDiffuseMapVar->SetResource(mFloorMapRV);
		pass->Apply(0);
		mHouseFloor.draw();
		//
		// draw left wall
		//
		D3DXMATRIX leftWWVP = mLeftWallPos*mLightView*mLightVolume;
		mfxBuildShadowMapLightWVPVar->SetMatrix((float*)&leftWWVP);
		mfxBuildShadowMapDiffuseMapVar->SetResource(mWall10x5MapRV);
		pass->Apply(0);
		mLeftWall.draw();
		//
		// draw right wall
		//
		D3DXMATRIX rightWWVP = mRightWallPos*mLightView*mLightVolume;
		mfxBuildShadowMapLightWVPVar->SetMatrix((float*)&rightWWVP);
		mfxBuildShadowMapDiffuseMapVar->SetResource(mWall10x5MapRV);
		pass->Apply(0);
		mRightWall.draw();
		//
		// draw front wall
		//
		D3DXMATRIX frontWWVP = mFrontWallPos*mLightView*mLightVolume;
		mfxBuildShadowMapLightWVPVar->SetMatrix((float*)&frontWWVP);
		mfxBuildShadowMapDiffuseMapVar->SetResource(mWall20x5MapRV);
		pass->Apply(0);
		mFrontWall.draw();
		//
		// draw back wall
		//
		D3DXMATRIX backWWVP = mBackWallPos*mLightView*mLightVolume;
		mfxBuildShadowMapLightWVPVar->SetMatrix((float*)&backWWVP);
		mfxBuildShadowMapDiffuseMapVar->SetResource(mWall20x5MapRV);
		pass->Apply(0);
		mBackWall.draw();
		//
		// draw roof
		//
		D3DXMATRIX roofWVP = mRoofPos*mLightView*mLightVolume;
		mfxBuildShadowMapLightWVPVar->SetMatrix((float*)&roofWVP);
		mfxBuildShadowMapDiffuseMapVar->SetResource(mRoofMapRV);
		pass->Apply(0);
		mRoof.draw();
		//
		// draw roof line left
		//
		D3DXMATRIX roofLLWVP = mRoofLineLPos*mLightView*mLightVolume;
		mfxBuildShadowMapLightWVPVar->SetMatrix((float*)&roofLLWVP);
		mfxBuildShadowMapDiffuseMapVar->SetResource(mRoofLineMapRV);
		pass->Apply(0);
		mRoofLineL.draw();
		//
		// draw roof line right
		//
		D3DXMATRIX roofLRWVP = mRoofLineRPos*mLightView*mLightVolume;
		mfxBuildShadowMapLightWVPVar->SetMatrix((float*)&roofLRWVP);
		mfxBuildShadowMapDiffuseMapVar->SetResource(mRoofLineMapRV);
		pass->Apply(0);
		mRoofLineR.draw();
		//
		// draw roof tri left
		//
		D3DXMATRIX roofTLWVP = mRoofTriLPos*mLightView*mLightVolume;
		mfxBuildShadowMapLightWVPVar->SetMatrix((float*)&roofTLWVP);
		mfxBuildShadowMapDiffuseMapVar->SetResource(mRoofTriMapRV);
		pass->Apply(0);
		mRoofTriL.draw();
		//
		// draw roof tri right
		//
		D3DXMATRIX roofTRWVP = mRoofTriRPos*mLightView*mLightVolume;
		mfxBuildShadowMapLightWVPVar->SetMatrix((float*)&roofTRWVP);
		mfxBuildShadowMapDiffuseMapVar->SetResource(mRoofTriMapRV);
		pass->Apply(0);
		mRoofTriR.draw();
		//
		// draw roof flag base
		//
		D3DXMATRIX roofFSWVP = mFlagstockPos*mLightView*mLightVolume;
		mfxBuildShadowMapLightWVPVar->SetMatrix((float*)&roofFSWVP);
		mfxBuildShadowMapDiffuseMapVar->SetResource(mBaseMapRV);
		pass->Apply(0);
		mFlagstock.draw();
		//
		// draw roof flag
		//
		D3DXMATRIX roofFLWVP = mFlagPos*mLightView*mLightVolume;
		mfxBuildShadowMapLightWVPVar->SetMatrix((float*)&roofFLWVP);
		mfxBuildShadowMapDiffuseMapVar->SetResource(mBaseMapRV);
		pass->Apply(0);
		mFlag.draw();
		//
		// draw torch
		//
		D3DXMATRIX columnWVP = mCylinderPos*mLightView*mLightVolume;
		mfxBuildShadowMapLightWVPVar->SetMatrix((float*)&columnWVP);
		mfxBuildShadowMapDiffuseMapVar->SetResource(mBaseMapRV);
		pass->Apply(0);
		mCylinder.draw();

		// Don't back face cull for tree, since we want to see both sides of leaf triangles.
		md3dDevice->RSSetState(mNoCullRS);
		D3DXMATRIX WVP = mTreeWorld*mLightView*mLightVolume;
		mfxBuildShadowMapLightWVPVar->SetMatrix((float*)&WVP);
		mTreeMesh.drawToShadowMap(mfxBuildShadowMapDiffuseMapVar, pass);
		md3dDevice->RSSetState(0); // restore default
	}
}

LRESULT HouseApp::msgProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	POINT mousePos;
	int dx = 0;
	int dy = 0;
	switch(msg)
	{
	case WM_LBUTTONDOWN:
		if( wParam & MK_LBUTTON )
		{
			SetCapture(mhMainWnd);

			mOldMousePos.x = LOWORD(lParam);
			mOldMousePos.y = HIWORD(lParam);
		}
		return 0;

	case WM_LBUTTONUP:
		ReleaseCapture();
		return 0;

	case WM_MOUSEMOVE:
		if( wParam & MK_LBUTTON )
		{
			mousePos.x = (int)LOWORD(lParam); 
			mousePos.y = (int)HIWORD(lParam); 

			dx = mousePos.x - mOldMousePos.x;
			dy = mousePos.y - mOldMousePos.y;

			GetCamera().pitch( dy * 0.0087266f );
			GetCamera().rotateY( dx * 0.0087266f );
			
			mOldMousePos = mousePos;
		}
		return 0;
	}

	return D3DApp::msgProc(msg, wParam, lParam);
}
/*
void HouseApp::buildNDCQuad()
{
	D3DXVECTOR3 pos[] = 
	{
		D3DXVECTOR3(0.0f, -1.0f, 0.0f),
		D3DXVECTOR3(0.0f,  0.0f, 0.0f),
		D3DXVECTOR3(1.0f,  0.0f, 0.0f),

		D3DXVECTOR3(0.0f, -1.0f, 0.0f),
		D3DXVECTOR3(1.0f,  0.0f, 0.0f),
		D3DXVECTOR3(1.0f, -1.0f, 0.0f)
	};

	D3DXVECTOR2 tex[] = 
	{
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(1.0f, 0.0f),

		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(1.0f, 0.0f),
		D3DXVECTOR2(1.0f, 1.0f)
	};

	QuadVertex qv[6];

	for(int i = 0; i < 6; ++i)
	{
		qv[i].pos  = pos[i];
		qv[i].texC = tex[i];
	}

	D3D10_BUFFER_DESC vbd;
    vbd.Usage = D3D10_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(QuadVertex) * 6;
    vbd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
    vbd.CPUAccessFlags = 0;
    vbd.MiscFlags = 0;
    D3D10_SUBRESOURCE_DATA vinitData;
    vinitData.pSysMem = qv;
    HR(md3dDevice->CreateBuffer(&vbd, &vinitData, &mNDCQuadVB));
}
*/