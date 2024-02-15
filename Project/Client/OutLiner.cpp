#include "pch.h"
#include "OutLiner.h"

#include <Engine/LevelMgr.h>
#include <Engine/Level.h>
#include <Engine/Layer.h>
#include <Engine/GameObject.h>

#include "TreeUI.h"

OutLiner::OutLiner()
	: UI("OutLiner", "##OutLiner")
{
	m_Tree = new TreeUI("OutLinerTree");
	m_Tree->ShowRootNode(false);
	AddChildUI(m_Tree);

	ResetCurrentLevel();
}

OutLiner::~OutLiner()
{
}

void OutLiner::Render_Update()
{
}

void OutLiner::ResetCurrentLevel()
{
	// 트리 내용을 삭제
	m_Tree->ClearNode();

	// 트리에 루트 추가
	TreeNode* pRootNode = m_Tree->AddTreeNode(nullptr, "DummyRoot", 0);

	// 현재 레벨을 가져온다.
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();

	for (UINT i = 0; i < LAYER_MAX; ++i)
	{
		CLayer* pLayer = pCurLevel->GetLayer(i);
		const vector<CGameObject*>& vecParent = pLayer->GetParentObjects();

		for (size_t i = 0; i < vecParent.size(); ++i)
		{
			AddObjectToTree(pRootNode, vecParent[i]);
		}
	}
}

void OutLiner::AddObjectToTree(TreeNode* _Node, CGameObject* _Object)
{
	TreeNode* pNode = m_Tree->AddTreeNode(_Node, string(_Object->GetName().begin(), _Object->GetName().end()), (DWORD_PTR)_Object);

	const vector<CGameObject*>& vecChild = _Object->GetChild();

	for (size_t i = 0; i < vecChild.size(); ++i)
	{
		AddObjectToTree(pNode, vecChild[i]);
	}
}
