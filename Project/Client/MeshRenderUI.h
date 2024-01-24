#pragma once
#include "ComponentUI.h"
class MeshRenderUI : public ComponentUI
{
public:
    MeshRenderUI();
    ~MeshRenderUI();

public:
    virtual void Render_Update() override;


public:
    void MeshSelect(DWORD_PTR _ptr);
    void MaterialSelect(DWORD_PTR _ptr);


};

