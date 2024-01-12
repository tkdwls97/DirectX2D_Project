#include "pch.h"
#include "RenderMgr.h"

#include "Device.h"
#include "AssetMgr.h"

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

	Vec2 vRenderResolution = CDevice::GetInst()->GetRenderResolution();
	m_PostProcessTex = CAssetMgr::GetInst()->CreateTexture((UINT)vRenderResolution.x
		, (UINT)vRenderResolution.y
		, DXGI_FORMAT_R8G8B8A8_UNORM
		, D3D11_BIND_SHADER_RESOURCE);
}