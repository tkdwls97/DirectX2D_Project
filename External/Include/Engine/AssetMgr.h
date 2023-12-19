#pragma once
#include "singleton.h"

#include "Asset.h"



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

private:
	map<wstring, CAsset*>   m_mapAsset[(UINT)ASSET_TYPE::END];
};

template<typename T>
ASSET_TYPE GetAssetType()
{
	const type_info& info = typeid(T);

	ASSET_TYPE Type = ASSET_TYPE::END;

	if (&info == &typeid(class CMesh))
		Type = ASSET_TYPE::MESH;
	else if (&info == &typeid(class CGraphicsShader))
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
