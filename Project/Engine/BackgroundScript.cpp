#include "pch.h"
#include "BackgroundScript.h"

#include "KeyMgr.h"

CBackgroundScript::CBackgroundScript()
{
}

CBackgroundScript::~CBackgroundScript()
{
}


void CBackgroundScript::Tick()
{

	static int i = 0;
	if (KEY_TAP(KEY::T))
	{
		i ? MeshRender()->GetMaterial()->SetScalarParam(INT_0, 1) : MeshRender()->GetMaterial()->SetScalarParam(INT_0, 0);
		i = !i;
	}
}
