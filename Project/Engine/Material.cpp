#include "pch.h"
#include "Material.h"

#include "GraphicsShader.h"

#include "Device.h"
#include "ConstBuffer.h"

#include "PathMgr.h"
#include "Ptr.h"

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

	// ����� ���̴� ���ε�
	m_GpShader->UpdateData();

	// Texture Update(Register Binding)
	for (UINT i = 0; i < TEX_PARAM::END; ++i)
	{
		if (nullptr != m_arrTex[i].Get())
		{
			m_arrTex[i]->UpdateData(i);
			m_Const.bTex[i] = 1;
		}
		else
		{
			CTexture::Clear(i);
			m_Const.bTex[i] = 0;
		}
	}

	// ��� ������ ������Ʈ
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
	m_arrTex[_Param] = _pTexture;
}

void* CMaterial::GetScalarParam(SCALAR_PARAM _ParamType)
{
	switch (_ParamType)
	{
	case INT_0:
	case INT_1:
	case INT_2:
	case INT_3:
	{
		int idx = _ParamType - INT_0;
		return m_Const.iArr + idx;
	}
	break;
	case FLOAT_0:
	case FLOAT_1:
	case FLOAT_2:
	case FLOAT_3:
	{
		int idx = _ParamType - FLOAT_0;
		return m_Const.fArr + idx;
	}
	break;
	case VEC2_0:
	case VEC2_1:
	case VEC2_2:
	case VEC2_3:
	{
		int idx = _ParamType - VEC2_0;
		return m_Const.v2Arr + idx;
	}
	break;
	case VEC4_0:
	case VEC4_1:
	case VEC4_2:
	case VEC4_3:
	{
		int idx = _ParamType - VEC4_0;
		return m_Const.v4Arr + idx;
	}
	break;
	case MAT_0:
	case MAT_1:
	case MAT_2:
	case MAT_3:
	{
		int idx = _ParamType - MAT_0;
		return m_Const.matArr + idx;
	}
	break;
	}

	return nullptr;
}


int CMaterial::Save(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");

	if (nullptr == pFile)
		return E_FAIL;

	// ���� ����� ����
	fwrite(&m_Const, sizeof(tMtrlConst), 1, pFile);


	// ������ �����ϴ� �ؽ��� ������ ����	
	for (UINT i = 0; i < (UINT)TEX_PARAM::END; ++i)
	{
		SaveAssetRef<CTexture>(m_arrTex[i], pFile);
	}

	// ������ �����ϴ� ���̴� ������ ����
	SaveAssetRef<CGraphicsShader>(m_GpShader, pFile);
	return 0;
}

int CMaterial::Load(const wstring& _strFilePath)
{
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _strFilePath.c_str(), L"rb");

	if (nullptr == pFile)
		return E_FAIL;

	// ���� ����� ����
	fread(&m_Const, sizeof(tMtrlConst), 1, pFile);


	// ������ �����ϴ� �ؽ��� ������ �ε�
	for (UINT i = 0; i < (UINT)TEX_PARAM::END; ++i)
	{
		LoadAssetRef<CTexture>(m_arrTex[i], pFile);
	}

	// ������ �����ϴ� ���̴� ������ ����
	LoadAssetRef<CGraphicsShader>(m_GpShader, pFile);

	return 0;
}
