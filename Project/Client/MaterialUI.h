#pragma once
#include "AssetUI.h"
class MaterialUI : public AssetUI
{
public:
	MaterialUI();
	~MaterialUI();

public:
	virtual void Render_Update() override;

public:
	void SelectTexture(DWORD_PTR _dwData);
	
private:
	TEX_PARAM       m_SelectTexParam;
};

