#include "pch.h"
#include "OutLiner.h"

#include <Engine/LevelMgr.h>
#include <Engine/Level.h>
#include <Engine/Layer.h>
#include <Engine/GameObject.h>

#include "ImGuiMgr.h"
#include "Inspector.h"
#include "TreeUI.h"

OutLiner::OutLiner()
	: UI("OutLiner", "##OutLiner")
{
	m_Tree = new TreeUI("OutLinerTree");
	m_Tree->ShowRootNode(false);
	m_Tree->UseDragDrop(true);
	AddChildUI(m_Tree);

	// 트리에 클릭 이벤트 등록
	m_Tree->AddSelectDelegate(this, (Delegate_1)&OutLiner::SelectObject);
	m_Tree->AddDragDropDelegate(this, (Delegate_2)&OutLiner::DragDropObject);


	// 트리 내용을 현재 레벨의 물체들로 구성
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

void OutLiner::SelectObject(DWORD_PTR _Node)
{
	TreeNode* pNode = (TreeNode*)_Node;
	CGameObject* pObject = (CGameObject*)pNode->GetData();

	if (nullptr == pObject)
		return;

	Inspector* pInspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");
	pInspector->SetTargetObject(pObject);
}

void OutLiner::DragDropObject(DWORD_PTR _Dest, DWORD_PTR _Source)
{
	TreeNode* pDestNode = (TreeNode*)_Dest;
	TreeNode* pSourceNode = (TreeNode*)_Source;

	if (nullptr == pDestNode)
	{
		CGameObject* pSourceObj = (CGameObject*)pSourceNode->GetData();

		int LayerIdx = pSourceObj->DisconnectWithParent();

		// 원래 부모가 없었다
		if (LayerIdx == -1)
			return;

		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		pCurLevel->AddObject(pSourceObj, LayerIdx, false);
	}
	else
	{
		CGameObject* pDestObj = (CGameObject*)pDestNode->GetData();
		CGameObject* pSourceObj = (CGameObject*)pSourceNode->GetData();
		pDestObj->AddChild(pSourceObj);
	}

	ResetCurrentLevel();
}
