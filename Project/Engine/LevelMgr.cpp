#include "pch.h"
#include "LevelMgr.h"

#include "Device.h"
#include "AssetMgr.h"

#include "Level.h"
#include "GameObject.h"
#include "components.h"
#include "PlayerScript.h"
#include "CameraMoveScript.h"

#include "Mesh.h"
#include "GraphicsShader.h"
#include "Texture.h"


CLevelMgr::CLevelMgr()
	: m_CurLevel(nullptr)
{

}

CLevelMgr::~CLevelMgr()
{
	if (nullptr != m_CurLevel)
	{
		delete m_CurLevel;
		m_CurLevel = nullptr;
	}
}

void CLevelMgr::Init()
{
	// 초기 레벨 구성하기
	m_CurLevel = new CLevel;

	CTexture* pTex = CAssetMgr::GetInst()->Load<CTexture>(L"PlayerTexture", L"texture\\Effect.png");
	if (nullptr != pTex)
	{
		pTex->UpdateData(0);
	}


	// Camera Object 생성
	CGameObject* pCamObj = new CGameObject;
	pCamObj->AddComponent(new CTransform);
	pCamObj->AddComponent(new CCamera);
	pCamObj->AddComponent(new CCameraMoveScript);

	pCamObj->Transform()->SetRelativePos(Vec3(0.5f, 0.f, 0.f));
	pCamObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));

	m_CurLevel->AddObject(pCamObj, 0);

	// GameObject 생성
	CGameObject* pObj = nullptr;

	pObj = new CGameObject;
	pObj->SetName(L"Player");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CPlayerScript);

	pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 500.f));
	pObj->Transform()->SetRelativeScale(Vec3(1000.f, 1000.f, 1.f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));
	pObj->MeshRender()->GetMaterial()->m_Const.iArr[0] = 1;

	//CGameObject* pChildObj = new CGameObject;
	//pChildObj->SetName(L"Child");

	//pChildObj->AddComponent(new CTransform);
	//pChildObj->AddComponent(new CMeshRender);

	//pChildObj->Transform()->SetRelativePos(Vec3(200.f, 0.f, 0.f));
	//pChildObj->Transform()->SetRelativeScale(Vec3(150.f, 150.f, 1.f));
	//pChildObj->Transform()->SetAbsolute(true);

	//pChildObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	//pChildObj->MeshRender()->SetShader(CAssetMgr::GetInst()->FindAsset<CGraphicsShader>(L"EffectShader"));

	//pObj->AddChild(pChildObj);

	m_CurLevel->AddObject(pObj, 0, false);
}

void CLevelMgr::Tick()
{
	if (nullptr == m_CurLevel)
		return;

	// 이전 프레임에 등록된 오브젝트들 clear
	m_CurLevel->clear();

	m_CurLevel->Tick();
	m_CurLevel->Finaltick();
}

void CLevelMgr::Render()
{
	if (nullptr == m_CurLevel)
		return;

	float ClearColor[4] = { 0.3f, 0.3f, 0.3f, 1.f };
	CDevice::GetInst()->ClearRenderTarget(ClearColor);


	m_CurLevel->Render();


	CDevice::GetInst()->Present();
}
