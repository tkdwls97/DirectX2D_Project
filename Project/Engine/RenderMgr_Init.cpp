#include "pch.h"
#include "RenderMgr.h"

#include "GameObject.h"
#include "Transform.h"
#include "MeshRender.h"

void CRenderMgr::Init()
{
	m_pDebugObj = new CGameObject;
	m_pDebugObj->AddComponent(new CTransform);
	m_pDebugObj->AddComponent(new CMeshRender);
}