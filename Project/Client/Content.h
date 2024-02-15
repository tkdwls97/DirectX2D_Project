#pragma once
#include "UI.h"

// AssetMgr �� �ε��Ǿ� �ִ� ��� ���µ��� ����

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

