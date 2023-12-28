#pragma once
#include "Asset.h"

class CGraphicsShader;
class CTexture;

class CMaterial : public CAsset
{
public:
	CMaterial();
	~CMaterial();

public:
	CGraphicsShader* GetShader() { return m_GpShader; }

	void SetShader(CGraphicsShader* _Shader) { m_GpShader = _Shader; }

public:

	void UpdateData();

public:
	tMtrlConst          m_Const;
	CTexture*			m_arrTex[(UINT)TEX_PARAM::END];
	CGraphicsShader*	m_GpShader;
};

