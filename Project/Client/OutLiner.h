#pragma once
#include "UI.h"

// ���� ������ �ִ� ��� ������Ʈ�� ����

class OutLiner : public UI
{
public:
    OutLiner();
    ~OutLiner();

public:
    virtual void Render_Update() override;
};

