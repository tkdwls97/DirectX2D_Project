#include "pch.h"
#include "Outliner.h"

#include <Engine/LevelMgr.h>
#include <Engine/Level.h>
#include <Engine/Layer.h>
#include <Engine/GameObject.h>

#include "ImGuiMgr.h"
#include "Inspector.h"
#include "TreeUI.h"


OutLiner::OutLiner()
	: UI("Outliner", "##Outliner")
{
	m_Tree = new TreeUI("OutlinerTree");
	m_Tree->ShowRootNode(false);
	m_Tree->UseDragDrop(true);

	AddChildUI(m_Tree);

	// Ʈ���� Ŭ�� �̺�Ʈ ���
	m_Tree->AddSelectDelegate(this, (Delegate_1)&OutLiner::SelectObject);
	m_Tree->AddDragDropDelegate(this, (Delegate_2)&OutLiner::DragDropObject);


	// Ʈ�� ������ ���� ������ ��ü��� ����
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
	// Ʈ�� ������ ����
	m_Tree->ClearNode();

	// Ʈ���� ��Ʈ �߰�
	TreeNode* pRootNode = m_Tree->AddTreeNode(nullptr, "DummyRoot", 0);

	// ���� ������ �����´�.
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

	CGameObject* pDestObj = nullptr;
	if (nullptr != pDestNode)
		pDestObj = (CGameObject*)pDestNode->GetData();

	CGameObject* pSourceObj = (CGameObject*)pSourceNode->GetData();

	// �θ� ������Ʈ�� �ڽ��� �ڽĿ�����Ʈ�� �ڽ����� ������ ���� ����
	if (pDestObj != nullptr && pDestObj->IsAncestor(pSourceObj))
		return;

	if (nullptr == pDestNode)
	{
		int LayerIdx = pSourceObj->DisconnectWithParent();

		// ���� �θ� ������
		if (LayerIdx == -1)
			return;

		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		pCurLevel->AddObject(pSourceObj, LayerIdx, false);
	}
	else
	{
		pDestObj->AddChild(pSourceObj);
	}

	ResetCurrentLevel();
}
