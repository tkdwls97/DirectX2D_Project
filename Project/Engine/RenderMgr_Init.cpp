#include "pch.h"
#include "RenderMgr.h"

#include "GameObject.h"
#include "Transform.h"
#include "MeshRender.h"

#include "StructuredBuffer.h"

void CRenderMgr::Init()
{
	Vec4 arr[3] =
	{
		Vec4(1.f, 0.f, 0.f, 1.f),
		Vec4(0.f, 1.f, 0.f, 1.f),
		Vec4(0.f, 0.f, 1.f, 1.f)
	};

	m_Light2DBuffer = new CStructuredBuffer;
	m_Light2DBuffer->Create(sizeof(Vec4), 2, SB_TYPE::READ_ONLY, true);

	if (m_Light2DBuffer->GetElementCount() < 3)
	{
		m_Light2DBuffer->Create(sizeof(Vec4), 10, SB_TYPE::READ_ONLY, true);
	}

	m_Light2DBuffer->SetData(arr, 3);

	m_Light2DBuffer->UpdateData(14);

	Vec4 arrTest[3] = {};
	m_Light2DBuffer->GetData(arrTest, 3);

	m_pDebugObj = new CGameObject;
	m_pDebugObj->AddComponent(new CTransform);
	m_pDebugObj->AddComponent(new CMeshRender);
}