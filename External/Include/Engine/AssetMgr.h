#pragma once
#include "singleton.h"


#include "PathMgr.h"
#include "Asset.h"

#include "Texture.h"
#include "Mesh.h"
#include "GraphicsShader.h"



class CAssetMgr : public CSingleton<CAssetMgr>
{
	SINGLE(CAssetMgr);

public:
	void Init();

public:
	template<typename T>
	void AddAsset(const wstring& _strKey, T* _Asset);

	template<typename T>
	T* FindAsset(const wstring& _strKey);

	template<typename T>
	T* Load(const wstring& _strKey, const wstring& _strRelativePath);

private:
	map<wstring, CAsset*>   m_mapAsset[(UINT)ASSET_TYPE::END];
};

template<typename T>
ASSET_TYPE GetAssetType()
{
	const type_info& info = typeid(T);

	ASSET_TYPE Type = ASSET_TYPE::END;

	if (&info == &typeid(CMesh))
		Type = ASSET_TYPE::MESH;
	else if (&info == &typeid(CTexture))
		Type = ASSET_TYPE::TEXTURE;
	else if (&info == &typeid(CGraphicsShader))
		Type = ASSET_TYPE::GRAPHICS_SHADER;

	return Type;
}

template<typename T>
inline void CAssetMgr::AddAsset(const wstring& _strKey, T* _Asset)
{
	ASSET_TYPE Type = GetAssetType<T>();

	map<wstring, CAsset*>::iterator iter = m_mapAsset[(UINT)Type].find(_strKey);
	assert(iter == m_mapAsset[(UINT)Type].end());

	m_mapAsset[(UINT)Type].insert(make_pair(_strKey, _Asset));
}

template<typename T>
inline T* CAssetMgr::FindAsset(const wstring& _strKey)
{
	ASSET_TYPE Type = GetAssetType<T>();

	map<wstring, CAsset*>::iterator iter = m_mapAsset[(UINT)Type].find(_strKey);

	if (iter == m_mapAsset[(UINT)Type].end())
	{
		return nullptr;
	}

	return (T*)iter->second;
}

template<typename T>
inline T* CAssetMgr::Load(const wstring& _strKey, const wstring& _strRelativePath)
{
	CAsset* pAsset = FindAsset<T>(_strKey);

	// 로딩할 때 사용할 키로 이미 다른 에셋이 있다면
	if (nullptr != pAsset)
	{
		return (T*)pAsset;
	}

	wstring strFilePath = CPathMgr::GetContentPath();
	strFilePath += _strRelativePath;

	pAsset = new T;
	if (FAILED(pAsset->Load(strFilePath)))
	{
		MessageBox(nullptr, L"에셋 로딩 실패", L"에셋 로딩 실패", MB_OK);
		delete pAsset;
		return nullptr;
	}

	pAsset->SetKey(_strKey);
	pAsset->SetRelativePath(_strRelativePath);
	wstring str = pAsset->GetRelativePath();
	AddAsset<T>(_strKey, (T*)pAsset);

	return (T*)pAsset;
}