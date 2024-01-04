#include "pch.h"
#include "Script.h"

CScript::CScript()
	: CComponent(COMPONENT_TYPE::SCRIPT)
{
}

CScript::~CScript()
{
}

void CScript::Destroy()
{
	GamePlayStatic::DestroyGameObject(GetOwner());
}

void CScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}
