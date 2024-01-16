#pragma once
#include "UI.h"

// 현재 레벨에 있는 모든 오브젝트들 나열

class OutLiner : public UI
{
public:
    OutLiner();
    ~OutLiner();

public:
    virtual void Render_Update() override;
};

