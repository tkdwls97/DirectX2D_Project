#pragma once
#include "Asset.h"

class CShader :	public CAsset
{
public:
	CShader(ASSET_TYPE _Type);
	~CShader();

public:
	virtual int UpdateData() = 0;

protected:
	ComPtr<ID3DBlob>	m_ErrBlob;

};

