#pragma once
#include "UI.h"


class MenuUI :
    public UI
{
public:
    MenuUI();
    ~MenuUI();

public:
    virtual void Render() override;
    virtual void Render_Update() override;

private:

};

