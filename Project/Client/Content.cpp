#include "pch.h"
#include "Content.h"

#include <Engine/AssetMgr.h>

#include "ImGuiMgr.h"
#include "Inspector.h"
#include "TreeUI.h"

Content::Content()
	: UI("Content", "##Content")
{
	// ContentUI �ڽ����� Tree �� ����
	m_Tree = new TreeUI("ContentTree");
	m_Tree->ShowRootNode(false);
	AddChildUI(m_Tree);

	// AssetMgr �� ���»��¸� Ʈ���� �����Ѵ�.
	ResetContent();

	// Ʈ���� Delegate �� ����Ѵ�.
	m_Tree->AddSelectDelegate(this, (Delegate_1)&Content::SelectAsset);
}

Content::~Content()
{
}

void Content::Render_Update()
{
}


void Content::ResetContent()
{
	// Tree Clear
	m_Tree->ClearNode();

	// ��Ʈ��� �߰�
	TreeNode* RootNode = m_Tree->AddTreeNode(nullptr, "Root", 0);

	for (UINT i = 0; i < (UINT)ASSET_TYPE::END; ++i)
	{
		TreeNode* CategoryNode = m_Tree->AddTreeNode(RootNode, ASSET_TYPE_STRING[i], 0);
		CategoryNode->SetFrame(true);

		const map<wstring, Ptr<CAsset>>& mapAsset = CAssetMgr::GetInst()->GetAssets((ASSET_TYPE)i);

		for (const auto& pair : mapAsset)
		{
			m_Tree->AddTreeNode(CategoryNode
				, string(pair.first.begin(), pair.first.end())
				, (DWORD_PTR)pair.second.Get());
		}
	}
}

void Content::SelectAsset(DWORD_PTR _Node)
{
	TreeNode* pNode = (TreeNode*)_Node;

	if (nullptr == pNode)
		return;

	Ptr<CAsset> pAsset = (CAsset*)pNode->GetData();
	if (nullptr == pAsset)
		return;

	// ������ ������ Inspector ���� �˷��ش�.
	Inspector* pInspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");
	pInspector->SetTargetAsset(pAsset);
}
