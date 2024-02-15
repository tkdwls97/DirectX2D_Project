#pragma once
#include "UI.h"

// AssetMgr 에 로딩되어 있는 모든 에셋들을 나열

class TreeUI;

class Content : public UI
{
public:
    Content();
    ~Content();

public:
    virtual void Render_Update() override;

public:
    void ResetContent();
    void SelectAsset(DWORD_PTR _Node);

private:
    TreeUI* m_Tree;

};

