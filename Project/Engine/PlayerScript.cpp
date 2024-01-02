#include "pch.h"
#include "PlayerScript.h"
#include "AssetMgr.h"

#include "MissileScript.h"

CPlayerScript::CPlayerScript()
	: m_Speed(500.f)
{
}

CPlayerScript::~CPlayerScript()
{
}

void CPlayerScript::Tick()
{
	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 vRot = Transform()->GetRelativeRotation();

	if (KEY_PRESSED(KEY::UP))
	{
		vPos.y += DT * m_Speed;
	}

	if (KEY_PRESSED(KEY::DOWN))
	{
		vPos.y -= DT * m_Speed;
	}

	if (KEY_PRESSED(KEY::LEFT))
	{
		vPos.x -= DT * m_Speed;
	}

	if (KEY_PRESSED(KEY::RIGHT))
	{
		vPos.x += DT * m_Speed;
	}

	if (KEY_PRESSED(KEY::X))
	{
		vRot.x += DT * XM_PI;
	}

	if (KEY_PRESSED(KEY::Y))
	{
		vRot.y += DT * XM_PI;
	}

	if (KEY_PRESSED(KEY::Z))
	{
		vRot.z += DT * XM_PI;
	}

	Transform()->SetRelativePos(vPos);
	Transform()->SetRelativeRotation(vRot);


	if (KEY_TAP(KEY::SPACE))
	{
		//Destroy();
		// GameObject ����
		CGameObject* pObj = nullptr;

		pObj = new CGameObject;
		pObj->SetName(L"Missile");
		pObj->AddComponent(new CTransform);
		pObj->AddComponent(new CMeshRender);
		pObj->AddComponent(new CMissileScript);
		pObj->AddComponent(new CCollider2D);

		pObj->Transform()->SetRelativePos(Transform()->GetRelativePos());
		pObj->Transform()->SetRelativeScale(Vec3(50.f, 50.f, 1.f));

		pObj->Collider2D()->SetAbsolute(false);
		pObj->Collider2D()->SetOffsetScale(Vec2(1.f, 1.f));
		pObj->Collider2D()->SetOffsetPos(Vec2(0.f, 0.f));

		pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
		pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

		GamePlayStatic::SpawnGameObject(pObj, 0);
	}

	GamePlayStatic::DrawDebugRect(Vec3(0.f, 0.f, 0.f), Vec3(200.f, 200.f, 1.f), Vec3(0.f, 0.f, 0.f), Vec3(1.f, 1.f, 1.f), true, 20);
	GamePlayStatic::DrawDebugCircle(Vec3(0.f, 0.f, 0.f), 200.f, Vec3(0.f, 1.f, 1.f), true);
}