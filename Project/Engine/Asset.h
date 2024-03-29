#pragma once
#include "Entity.h"

#include "Ptr.h"

class CAsset : public CEntity
{
	friend class CAssetMgr;

	template<typename T>
	friend class Ptr;

public:
	CAsset(ASSET_TYPE _Type, bool _bEngineAsset = false);
	~CAsset();
public:
	virtual int Save(const wstring& _strRelativePath) { return E_FAIL; }
	virtual int Load(const wstring& _strFilePath) { return E_FAIL; }
	virtual CAsset* Clone() { return nullptr; }

public:
	const wstring& GetKey() { return m_Key; }
	const wstring& GetRelativePath() { return m_RelativePath; }
	int GetRefCount() { return m_RefCount; }
	ASSET_TYPE GetType() { return m_Type; }

private:
	void SetKey(const wstring& _Key) { m_Key = _Key; }
	void SetRelativePath(const wstring& _RelativePath) { m_RelativePath = _RelativePath; }

	void AddRef()
	{
		++m_RefCount;
	}

	void Release()
	{
		--m_RefCount;
		if (0 >= m_RefCount)
		{
			delete this;
		}
	}



private:
	wstring             m_Key;
	wstring             m_RelativePath;
	int                 m_RefCount;
	const ASSET_TYPE    m_Type;
	const bool          m_bEngineAsset;
};

