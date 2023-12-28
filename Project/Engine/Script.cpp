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
