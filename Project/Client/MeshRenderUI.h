#pragma once
#include "ComponentUI.h"

class MeshRenderUI : public ComponentUI
{
public:
	MeshRenderUI();
	virtual ~MeshRenderUI();

public:
	virtual void Render_Update() override;
	
public:
	void MeshDBClicked();

private:

};

