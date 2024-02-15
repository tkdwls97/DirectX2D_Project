#pragma once
#include "UI.h"
#include <Engine/GameObject.h>
#include <Engine/Asset.h>

// GameObject ����
//  - ������Ʈ
//  - ��ũ��Ʈ

// Asset ����
//  - �� ������ ����
class ComponentUI;
class AssetUI;

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

    CGameObject* GetTargetObject() { return m_TargetObject; }

private:
    void CreateChildUI();
    void CreateComponentUI();
    void CreateAssetUI();

private:
    CGameObject*    m_TargetObject;
    Ptr<CAsset>     m_TargetAsset;
    ComponentUI*    m_arrComUI[(UINT)COMPONENT_TYPE::END];
    AssetUI*        m_arrAssetUI[(UINT)ASSET_TYPE::END];
};

