#pragma once
#include "UI.h"

#include <Engine/Ptr.h>
#include <Engine/Asset.h>

class AssetUI : public UI
{
public:
    AssetUI(const string& _strName, const string& _ID, ASSET_TYPE _Type);
    ~AssetUI();

public:
    virtual void Render_Update() override;

public:
    Ptr<CAsset> GetAsset() { return m_Asset; }
    void SetAsset(Ptr<CAsset> _Asset);

    ASSET_TYPE GetType() { return m_Type; }


private:
    Ptr<CAsset>     m_Asset;
    ASSET_TYPE      m_Type;
};

