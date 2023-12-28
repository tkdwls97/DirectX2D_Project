#include "pch.h"
#include "Material.h"

#include "GraphicsShader.h"

#include "Device.h"
#include "ConstBuffer.h"

CMaterial::CMaterial()
	: CAsset(ASSET_TYPE::MATERIAL)
	, m_Const{}
{

}

CMaterial::~CMaterial()
{

}

void CMaterial::UpdateData()
{
	static CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::MATERIAL_CONST);
	pCB->SetData(&m_Const);
	pCB->UpdateData();

	if (nullptr != m_GpShader)
	{
		m_GpShader->UpdateData();
	}
}
