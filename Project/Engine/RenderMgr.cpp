#include "pch.h"
#include "RenderMgr.h"

#include "Device.h"
#include "Camera.h"
#include "MeshRender.h"
#include "AssetMgr.h"
#include "Transform.h"

CRenderMgr::CRenderMgr()
	: m_pDebugObj(nullptr)
{

}

CRenderMgr::~CRenderMgr()
{
	if (nullptr != m_pDebugObj)
	{
		delete m_pDebugObj;
		m_pDebugObj = nullptr;
	}
}

void CRenderMgr::Tick()
{
	Vec4 vClearColor = Vec4(0.3f, 0.3f, 0.3f, 1.f);
	CDevice::GetInst()->ClearRenderTarget(vClearColor);

	Render();

	Render_Debug();

	CDevice::GetInst()->Present();
}


void CRenderMgr::Render()
{
	for (size_t i = 0; i < m_vecCam.size(); ++i)
	{
		m_vecCam[i]->Render();
	}
}

void CRenderMgr::Render_Debug()
{
	g_Transform.matView = m_vecCam[0]->GetViewMat();
	g_Transform.matProj = m_vecCam[0]->GetProjMat();

	list<tDebugShapeInfo>::iterator iter = m_DebugShapeInfo.begin();
	for (; iter != m_DebugShapeInfo.end(); ++iter)
	{
		switch ((*iter).eShape)
		{
		case DEBUG_SHAPE::RECT:
			m_pDebugObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
			break;
		case DEBUG_SHAPE::CIRCLE:
			m_pDebugObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"CircleMesh"));
			break;
		case DEBUG_SHAPE::CUBE:
			m_pDebugObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"CubeMesh"));
			break;
		case DEBUG_SHAPE::SPHERE:
			m_pDebugObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"SphereMesh"));
			break;
		default:
			break;
		}

		m_pDebugObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"DebugShapeMtrl"));
		m_pDebugObj->Transform()->SetWorldMat((*iter).matWorld);
		m_pDebugObj->Transform()->UpdateData();

		m_pDebugObj->Render();
	}
}

void CRenderMgr::RegisterCamera(CCamera* _Cam, int _Idx)
{
	if (m_vecCam.size() <= _Idx + 1)
	{
		m_vecCam.resize(_Idx + 1);
	}

	// ������ �켱������ ī�޶� �̹� �����ϸ� assert
	assert(nullptr == m_vecCam[_Idx]);

	m_vecCam[_Idx] = _Cam;
}