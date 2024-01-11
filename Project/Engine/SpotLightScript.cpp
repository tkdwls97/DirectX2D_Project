#include "pch.h"
#include "SpotLightScript.h"

#include "GameObject.h"

CSpotLightScript::CSpotLightScript()
{
}

CSpotLightScript::~CSpotLightScript()
{
}

void CSpotLightScript::Tick()
{
	Vec3 vRot = Transform()->GetRelativeRotation();

	if (KEY_PRESSED(KEY::Z))
	{
		vRot.z += XM_PI * DT;
	}

	if (KEY_PRESSED(KEY::C))
	{
		vRot.z -= XM_PI * DT;
	}
	Transform()->SetRelativeRotation(vRot);
}





