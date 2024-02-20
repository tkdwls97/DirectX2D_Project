#include "pch.h"
#include "Material.h"

#include "GraphicsShader.h"

#include "Device.h"
#include "ConstBuffer.h"


CMaterial::CMaterial(bool _bEngine)
	: CAsset(ASSET_TYPE::MATERIAL, _bEngine)
	, m_Const{}
{

}

CMaterial::~CMaterial()
{

}



void CMaterial::UpdateData()
{
	if (nullptr == m_GpShader.Get())
		return;

	// 사용할 쉐이더 바인딩
	m_GpShader->UpdateData();

	// Texture Update(Register Binding)
	for (UINT i = 0; i < TEX_PARAM::END; ++i)
	{
		if (nullptr != m_TextureArr[i].Get())
		{
			m_TextureArr[i]->UpdateData(i);
			m_Const.bTex[i] = 1;
		}
		else
		{
			CTexture::Clear(i);
			m_Const.bTex[i] = 0;
		}
	}

	// 상수 데이터 업데이트
	static CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::MATERIAL_CONST);
	pCB->SetData(&m_Const);
	pCB->UpdateData();

	if (nullptr != m_GpShader)
	{
		m_GpShader->UpdateData();
	}
}

void CMaterial::SetTexParam(TEX_PARAM _Param, Ptr<CTexture> _pTexture)
{
	m_TextureArr[_Param] = _pTexture;
}