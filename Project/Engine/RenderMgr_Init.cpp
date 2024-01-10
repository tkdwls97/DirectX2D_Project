#include "pch.h"
#include "RenderMgr.h"

#include "GameObject.h"
#include "Transform.h"
#include "MeshRender.h"

#include "StructuredBuffer.h"

void CRenderMgr::Init()
{
	m_Light2DBuffer = new CStructuredBuffer;
	m_Light2DBuffer->Create(sizeof(tLightInfo), 10, SB_TYPE::READ_ONLY, true);


	m_pDebugObj = new CGameObject;
	m_pDebugObj->AddComponent(new CTransform);
	m_pDebugObj->AddComponent(new CMeshRender);
}