#include "pch.h"
#include "LevelMgr.h"

#include "Device.h"
#include "AssetMgr.h"

#include "Level.h"
#include "Layer.h"
#include "GameObject.h"
#include "components.h"
#include "PlayerScript.h"
#include "SpotLightScript.h"
#include "CameraMoveScript.h"
#include "BackgroundScript.h"

#include "Mesh.h"
#include "GraphicsShader.h"
#include "Texture.h"
#include "CollisionMgr.h"
#include "SetColorShader.h"

CLevelMgr::CLevelMgr()
	: m_CurLevel(nullptr)
{

}

CLevelMgr::~CLevelMgr()
{
	if (nullptr != m_CurLevel)
		delete m_CurLevel;
}

void CLevelMgr::Init()
{
	// 초기 레벨 구성하기
	m_CurLevel = new CLevel;
	m_CurLevel->GetLayer(0)->SetName(L"Default");
	m_CurLevel->GetLayer(1)->SetName(L"Background");
	m_CurLevel->GetLayer(2)->SetName(L"Tile");
	m_CurLevel->GetLayer(3)->SetName(L"Player");
	m_CurLevel->GetLayer(4)->SetName(L"Monster");
	m_CurLevel->GetLayer(5)->SetName(L"Light");
	m_CurLevel->GetLayer(31)->SetName(L"UI");

	// ComputeShader 테스트
	// 사용할 텍스쳐 생성
	Ptr<CTexture> pTestTex = CAssetMgr::GetInst()->CreateTexture(L"TestTex"
		, 1024, 1024, DXGI_FORMAT_R8G8B8A8_UNORM
		, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS);

	Ptr<CSetColorShader> pCS = (CSetColorShader*)CAssetMgr::GetInst()->FindAsset<CComputeShader>(L"SetColorShader").Get();
	pCS->SetColor(Vec3(1.f, 0.f, 0.f));
	pCS->SetTargetTexture(pTestTex);
	pCS->Execute();

	tPixel* pPixel = pTestTex->GetPixels();
	tPixel pixel = pPixel[0];


	// 충돌 설정
	CCollisionMgr::GetInst()->LayerCheck(L"Player", L"Monster");
	CCollisionMgr::GetInst()->LayerCheck(L"Monster", L"Monster");

	// Main Camera Object 생성
	CGameObject* pCamObj = new CGameObject;
	pCamObj->SetName(L"MainCamera");
	pCamObj->AddComponent(new CTransform);
	pCamObj->AddComponent(new CCamera);
	pCamObj->AddComponent(new CCameraMoveScript);

	pCamObj->Transform()->SetRelativePos(Vec3(0.5f, 0.f, 0.f));
	pCamObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));

	pCamObj->Camera()->SetCameraPriority(0);
	pCamObj->Camera()->LayerCheckAll();
	pCamObj->Camera()->LayerCheck(L"UI", false);

	m_CurLevel->AddObject(pCamObj, 0);


	pCamObj = new CGameObject;
	pCamObj->SetName(L"UICamera");
	pCamObj->AddComponent(new CTransform);
	pCamObj->AddComponent(new CCamera);

	pCamObj->Transform()->SetRelativePos(Vec3(0.5f, 0.f, 0.f));
	pCamObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));

	pCamObj->Camera()->SetCameraPriority(1);
	pCamObj->Camera()->LayerCheck(L"UI", true);

	m_CurLevel->AddObject(pCamObj, 0);


	//// Spot Light
	//CGameObject* pLight = new CGameObject;
	//pLight->SetName(L"Spot Light");
	//pLight->AddComponent(new CTransform);
	//pLight->AddComponent(new CMeshRender);
	//pLight->AddComponent(new CLight2D);
	//pLight->AddComponent(new CSpotLightScript);


	//pLight->Light2D()->SetLightType(LIGHT_TYPE::SPOT);
	//pLight->Light2D()->SetLightColor(Vec3(1.0f, 1.0f, 1.0f));
	//pLight->Light2D()->SetRadius(300.f);
	//pLight->Light2D()->SetAngle(XM_PI / 4.0f);

	//m_CurLevel->AddObject(pLight, L"Light");

	// 전역 광원 추가
	CGameObject* pLight = new CGameObject;
	pLight->SetName(L"Directional Light");
	pLight->AddComponent(new CTransform);
	pLight->AddComponent(new CMeshRender);
	pLight->AddComponent(new CLight2D);

	pLight->Light2D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	pLight->Light2D()->SetAmbient(Vec3(1.0f, 1.0f, 1.0f));
	m_CurLevel->AddObject(pLight, L"Light");



	CGameObject* pObj = nullptr;

	// Backgruond Object 생성
	pObj = new CGameObject;
	pObj->SetName(L"Background");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CBackgroundScript);

	pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 600.f));
	pObj->Transform()->SetRelativeScale(Vec3(1600.f, 800.f, 1.f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"BackgroundMtrl"));

	Ptr<CTexture> pTex = CAssetMgr::GetInst()->Load<CTexture>(L"BackgroundTex", L"texture\\Title.png");
	pObj->MeshRender()->GetMaterial()->SetTexParam(TEX_0, pTestTex);

	m_CurLevel->AddObject(pObj, L"Background", false);

	//// TileMap Object
	//pObj = new CGameObject;
	//pObj->SetName(L"TileMap");

	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CTileMap);

	//pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 300.f));

	//Ptr<CTexture> pTileAtlas = CAssetMgr::GetInst()->Load<CTexture>(L"TileAtlasTex", L"texture\\TILE.bmp");

	//pObj->TileMap()->SetTileAtlas(pTileAtlas, Vec2(64.f, 64.f));
	//pObj->TileMap()->SetFace(6, 6);
	//for (int i = 0; i < 6; ++i)
	//{
	//	for (int j = 0; j < 6; ++j)
	//	{
	//		pObj->TileMap()->SetTileIndex(i, j, i * 6 + j);
	//	}
	//}

	//m_CurLevel->AddObject(pObj, L"Tile", false);


	// Player Object 생성
	CGameObject* pPlayer = new CGameObject;
	pPlayer->SetName(L"Player");

	pPlayer->AddComponent(new CTransform);
	pPlayer->AddComponent(new CMeshRender);
	pPlayer->AddComponent(new CCollider2D);
	pPlayer->AddComponent(new CAnimator2D);
	pPlayer->AddComponent(new CPlayerScript);

	pPlayer->Transform()->SetRelativePos(Vec3(0.f, 0.f, 500.f));
	pPlayer->Transform()->SetRelativeScale(Vec3(200.f, 200.f, 1.f));

	pPlayer->Collider2D()->SetAbsolute(true);
	pPlayer->Collider2D()->SetOffsetScale(Vec2(100.f, 130.f));
	pPlayer->Collider2D()->SetOffsetPos(Vec2(0.f, 0.f));
	pPlayer->Collider2D()->SetColliderType(COLLIDER2D_TYPE::RECT);

	pPlayer->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pPlayer->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

	m_CurLevel->AddObject(pPlayer, L"Player", false);

	// Monster Object 생성
	pObj = new CGameObject;
	pObj->SetName(L"Monster");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);

	pObj->Transform()->SetRelativePos(Vec3(300.f, 0.f, 500.f));
	pObj->Transform()->SetRelativeScale(Vec3(200.f, 200.f, 1.f));

	pObj->Collider2D()->SetAbsolute(true);
	pObj->Collider2D()->SetOffsetScale(Vec2(100.f, 100.f));
	pObj->Collider2D()->SetOffsetPos(Vec2(0.f, 0.f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));
	pObj->MeshRender()->GetMaterial()->SetTexParam(TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"MonsterTexture", L"texture\\Saladin_Gold.bmp"));
	pObj->MeshRender()->GetMaterial()->SetScalarParam(FLOAT_0, 0.f);

	m_CurLevel->AddObject(pObj, L"Monster", false);

	pObj = new CGameObject;
	pObj->SetName(L"UI");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);

	pObj->Transform()->SetRelativePos(Vec3(-590, 310.f, 500.f));
	pObj->Transform()->SetRelativeScale(Vec3(50.f, 50.f, 1.f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

	m_CurLevel->AddObject(pObj, L"UI", false);

	// PostProcess 오브젝트 추가
	/*pObj = new CGameObject;
	pObj->SetName(L"GrayFilter");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"GrayFilterMtrl"));

	m_CurLevel->AddObject(pObj, L"Default", false);*/

	//// Distortion 효과 추가
	//pObj = new CGameObject;
	//pObj->SetName(L"Distortion Object");

	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);

	//pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 200.f));
	//pObj->Transform()->SetRelativeScale(Vec3(1280.f, 768.f, 1.f));

	//pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"WarpDistortionMtrl"));
	//pObj->MeshRender()->GetMaterial()->SetTexParam(TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"NoiseTex", L"texture\\noise\\noise_03.jpg"));

	//m_CurLevel->AddObject(pObj, L"Default", false);

	// Level 시작
	m_CurLevel->Begin();
}

void CLevelMgr::Tick()
{
	if (nullptr == m_CurLevel)
		return;

	// 이전 프레임에 등록된 오브젝트들 clear
	m_CurLevel->Clear();

	m_CurLevel->Tick();
	m_CurLevel->Finaltick();
}
