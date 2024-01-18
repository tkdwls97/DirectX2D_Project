#pragma once
#include "ComponentUI.h"

#include <Engine/GameObject.h>

class TransformUI : public ComponentUI
{
public:
    TransformUI();
    ~TransformUI();

public:
    virtual void Render_Update() override;


private:
};

