#pragma once
#include "UI.h"

class TransformUI : public UI
{
public:
    TransformUI();
    ~TransformUI();

public:
    virtual void Render_Update() override;

public:
    void SetTargetObject(CGameObject* _Target)
    {
        m_TargetObject = _Target;
    }

private:
    CGameObject* m_TargetObject;

};

