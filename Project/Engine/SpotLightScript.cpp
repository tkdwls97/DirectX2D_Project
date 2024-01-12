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
	float vAngle = Light2D()->GetAngle();

	if (KEY_PRESSED(KEY::Z))
	{
		vRot.z += XM_PI * DT;
	}

	if (KEY_PRESSED(KEY::C))
	{
		vRot.z -= XM_PI * DT;
	}
	
	if (KEY_PRESSED(KEY::Q))
	{
		vAngle += DT * 1.0f;
	}

	if (KEY_PRESSED(KEY::E))
	{
		vAngle -= DT * 1.0f;
	}
	Transform()->SetRelativeRotation(vRot);
	Light2D()->SetAngle(vAngle);
}





