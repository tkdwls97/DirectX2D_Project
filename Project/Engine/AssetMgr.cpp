#include "pch.h"
#include "AssetMgr.h"

#include "Mesh.h"
#include "GraphicsShader.h"
#include "Material.h"

CAssetMgr::CAssetMgr()
{

}

CAssetMgr::~CAssetMgr()
{
}

Ptr<CTexture> CAssetMgr::CreateTexture(const wstring& _strKey
	, UINT _Width, UINT _Height, DXGI_FORMAT _Format
	, UINT _Flag, D3D11_USAGE _Usage)
{
	// �����Ϸ��� �ؽ��Ŀ� ������ Ű�� �ؽ��İ� �̹� AssetMgr �� �ִٸ�
	Ptr<CTexture> pTex = FindAsset<CTexture>(_strKey);
	assert(!pTex.Get());

	pTex = new CTexture;

	if (FAILED(pTex->Create(_Width, _Height, _Format, _Flag, _Usage)))
	{
		MessageBox(nullptr, L"�ؽ��� ���� ����", L"���ҽ� ���� ����", MB_OK);
		return nullptr;
	}

	AddAsset<CTexture>(_strKey, pTex.Get());

	return pTex;
}

Ptr<CTexture> CAssetMgr::CreateTexture(const wstring& _strKey, ComPtr<ID3D11Texture2D> _tex2D)
{
	// �����Ϸ��� �ؽ��Ŀ� ������ Ű�� �ؽ��İ� �̹� AssetMgr �� �ִٸ�
	Ptr<CTexture> pTex = FindAsset<CTexture>(_strKey);
	assert(!pTex.Get());

	pTex = new CTexture;

	if (FAILED(pTex->Create(_tex2D)))
	{
		MessageBox(nullptr, L"�ؽ��� ���� ����", L"���ҽ� ���� ����", MB_OK);
		return nullptr;
	}

	AddAsset<CTexture>(_strKey, pTex.Get());

	return pTex;
}

void CAssetMgr::GetAssetName(ASSET_TYPE _Type, vector<string>& _Out)
{
	for (const auto& pair : m_mapAsset[(UINT)_Type])
	{
		_Out.push_back(ToString(pair.first));
	}
}
