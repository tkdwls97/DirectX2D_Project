#pragma once
#include "UI.h"
#include <Engine/GameObject.h>
#include <Engine/Asset.h>

// GameObject ����
//  - ������Ʈ
//  - ��ũ��Ʈ

// Asset ����
//  - �� ������ ����
class TransformUI;

class Inspector :
    public UI
{
public:
    Inspector();
    ~Inspector();


public:
    virtual void Tick() override;
    virtual void Render_Update() override;

public:
    void SetTargetObject(CGameObject* _Object);
    void SetTargetAsset(Ptr<CAsset> _Asset);


private:
    CGameObject*    m_TargetObject;
    Ptr<CAsset>     m_TargetAsset;
    TransformUI*    m_TransformUI;
};

