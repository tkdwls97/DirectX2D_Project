#pragma once
#include "ComponentUI.h"

class Collider2DUI : public ComponentUI
{
public:
    Collider2DUI();
    ~Collider2DUI();

    virtual void Render_Update() override;
};

