#include "pch.h"
#include "MissileScript.h"


CMissileScript::CMissileScript()
	: m_fSpeed(500.f)
{
}

CMissileScript::~CMissileScript()
{
}

void CMissileScript::Tick()
{
	Vec3 vPos = Transform()->GetRelativePos();

	vPos.y += m_fSpeed * DT;

	Transform()->SetRelativePos(vPos);
}