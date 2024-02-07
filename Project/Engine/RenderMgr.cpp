#include "pch.h"
#include "RenderMgr.h"

#include "Device.h"
#include "ConstBuffer.h"

#include "StructuredBuffer.h"

#include "TimeMgr.h"
#include "Device.h"
#include "AssetMgr.h"
#include "components.h"


CRenderMgr::CRenderMgr()
	: m_Light2DBuffer(nullptr)
	, m_pDebugObj(nullptr)
	, m_DebugPosition(true)
{
}

CRenderMgr::~CRenderMgr()
{
	if (nullptr != m_pDebugObj)
		delete m_pDebugObj;

	if (nullptr != m_Light2DBuffer)
		delete m_Light2DBuffer;
}

void CRenderMgr::Tick()
{
	Vec4 vClearColor = Vec4(0.f, 0.f, 0.f, 1.f);
	CDevice::GetInst()->ClearRenderTarget(vClearColor);

	UpdateData();

	Render();
	Render_Debug();

	Clear();

}

void CRenderMgr::Render()
{
	// 렌더타겟 및 깊이 타겟 설정
	// ImGui에서 윈도우 창 밖으로 벗어날 시 렌더타겟을 다시 설정하기 때문에 렌더링 전에 렌더타겟을 다시 갱신해줘야한다. 
	Ptr<CTexture> pRTTex = CAssetMgr::GetInst()->FindAsset<CTexture>(L"RenderTargetTex");
	Ptr<CTexture> pDSTex = CAssetMgr::GetInst()->FindAsset<CTexture>(L"DepthStencilTex");
	CONTEXT->OMSetRenderTargets(1, pRTTex->GetRTV().GetAddressOf(), pDSTex->GetDSV().Get());

	for (size_t i = 0; i < m_vecCam.size(); ++i)
	{
		m_vecCam[i]->SortObject();
		m_vecCam[i]->Render();
	}
}

void CRenderMgr::Render_Debug()
{
	g_Transform.matView = m_vecCam[0]->GetViewMat();
	g_Transform.matProj = m_vecCam[0]->GetProjMat();

	list<tDebugShapeInfo>::iterator iter = m_DebugShapeInfo.begin();
	for (; iter != m_DebugShapeInfo.end(); )
	{
		switch ((*iter).eShape)
		{
		case DEBUG_SHAPE::RECT:
			m_pDebugObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh_Debug"));
			break;
		case DEBUG_SHAPE::CIRCLE:
			m_pDebugObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"CircleMesh_Debug"));
			break;
		case DEBUG_SHAPE::CROSS:
			m_pDebugObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"CrossMesh"));
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
		m_pDebugObj->MeshRender()->GetMaterial()->SetScalarParam(VEC4_0, (*iter).vColor);

		D3D11_PRIMITIVE_TOPOLOGY PrevTopology = m_pDebugObj->MeshRender()->GetMaterial()->GetShader()->GetTopology();
		if (DEBUG_SHAPE::CROSS == (*iter).eShape)
		{
			m_pDebugObj->MeshRender()->GetMaterial()->GetShader()->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_LINELIST);
		}

		m_pDebugObj->Transform()->SetWorldMat((*iter).matWorld);
		m_pDebugObj->Transform()->UpdateData();

		m_pDebugObj->Render();

		m_pDebugObj->MeshRender()->GetMaterial()->GetShader()->SetTopology(PrevTopology);

		(*iter).fLifeTime += DT;
		if ((*iter).fDuration <= (*iter).fLifeTime)
		{
			iter = m_DebugShapeInfo.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void CRenderMgr::UpdateData()
{
	g_global.g_Light2DCount = (int)m_vecLight2D.size();
	//g_global.g_Light3DCount = (int)m_vecLight3D.size();

	// 전역 데이터 업데이트
	static CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::GLOBAL_DATA);
	pCB->SetData(&g_global);
	pCB->UpdateData();
	pCB->UpdateData_CS();


	// 2D 광원정보 업데이트
	static vector<tLightInfo> vecLight2DInfo;

	for (size_t i = 0; i < m_vecLight2D.size(); ++i)
	{
		const tLightInfo& info = m_vecLight2D[i]->GetLightInfo();
		vecLight2DInfo.push_back(info);
	}

	if (!vecLight2DInfo.empty())
	{
		m_Light2DBuffer->SetData(vecLight2DInfo.data(), (UINT)vecLight2DInfo.size());
	}

	m_Light2DBuffer->UpdateData(11);

	vecLight2DInfo.clear();


	// 3D 광원정보 업데이트
}

void CRenderMgr::Clear()
{
	m_vecLight2D.clear();
}

void CRenderMgr::RegisterCamera(CCamera* _Cam, int _Idx)
{
	if (m_vecCam.size() <= _Idx + 1)
	{
		m_vecCam.resize(_Idx + 1);
	}

	// 동일한 우선순위의 카메라가 이미 존재하면 assert
	assert(nullptr == m_vecCam[_Idx]);

	m_vecCam[_Idx] = _Cam;
}


