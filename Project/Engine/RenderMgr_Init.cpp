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
	m_PostProcessTex = CAssetMgr::GetInst()->CreateTexture(L"PostProcessTex"
														, (UINT)vRenderResolution.x
														, (UINT)vRenderResolution.y
														, DXGI_FORMAT_R8G8B8A8_UNORM
														, D3D11_BIND_SHADER_RESOURCE);

	// Noise Texture Load
	m_vecNoiseTex.push_back(CAssetMgr::GetInst()->Load<CTexture>(L"texture\\noise\\noise_01.png", L"texture\\noise\\noise_01.png"));
	m_vecNoiseTex.push_back(CAssetMgr::GetInst()->Load<CTexture>(L"texture\\noise\\noise_02.png", L"texture\\noise\\noise_02.png"));
	m_vecNoiseTex.push_back(CAssetMgr::GetInst()->Load<CTexture>(L"texture\\noise\\noise_03.jpg", L"texture\\noise\\noise_03.jpg"));

	m_vecNoiseTex[0]->UpdateData(14);
	m_vecNoiseTex[0]->UpdateData_CS_SRV(14);
}

void CRenderMgr::CopyRenderTargetToPostProcessTarget()
{
	Ptr<CTexture> pRTTex = CAssetMgr::GetInst()->FindAsset<CTexture>(L"RenderTargetTex");
	CONTEXT->CopyResource(m_PostProcessTex->GetTex2D().Get(), pRTTex->GetTex2D().Get());

}