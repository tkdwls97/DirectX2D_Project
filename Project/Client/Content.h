#pragma once
#include "UI.h"

// AssetMgr �� �ε��Ǿ� �ִ� ��� ���µ��� ����
class Content : public UI
{
public:
    Content();
    ~Content();

public:
    virtual void Render_Update() override;
};

