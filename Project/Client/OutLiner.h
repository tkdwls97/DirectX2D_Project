#pragma once
#include "UI.h"

// ���� ������ �ִ� ��� ������Ʈ�� ����

class TreeUI;
class TreeNode;

class OutLiner : public UI
{
public:
    OutLiner();
    ~OutLiner();

public:
    virtual void Render_Update() override;

public:
    void ResetCurrentLevel();

private:
    void AddObjectToTree(TreeNode* _Node, CGameObject* _Object);

private:
    TreeUI* m_Tree;
};

