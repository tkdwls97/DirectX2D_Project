#pragma once
#include "UI.h"


class TreeNode
{
	friend class TreeUI;
public:
	TreeNode();
	~TreeNode();


public:
	void Render_Update();

public:
	void SetName(string& _Name) { m_Name = _Name; }
	void SetFrame(bool _Frame) { m_bFrame = _Frame; }

	const string& GetName() { return m_Name; }
	DWORD_PTR GetData() { return m_Data; }

private:
	void SetID(const string& _ID) { m_ID = _ID; }
	void AddChildNode(TreeNode* _Node)
	{
		m_vecChildNode.push_back(_Node);
		_Node->m_ParentNode = this;
	}

private:
	TreeUI* m_Owner;

	string              m_Name;
	string              m_ID;
	vector<TreeNode*>   m_vecChildNode;

	TreeNode* m_ParentNode;
	DWORD_PTR           m_Data;

	bool                m_bFrame;
	bool                m_bSelected;


};



class TreeUI : public UI
{
	friend class TreeNode;
public:
	TreeUI(const string& _ID);
	~TreeUI();


public:
	virtual void Render_Update() override;

public:
	void AddSelectDelegate(UI* _Inst, Delegate_1 _pFunc) { m_SelectInst = _Inst; m_SelectFunc = _pFunc; }
	void ShowRootNode(bool _bShow) { m_bShowRoot = _bShow; }
	TreeNode* AddTreeNode(TreeNode* _Parent, string _strName, DWORD_PTR _dwData);
	void ClearNode()
	{
		if (nullptr != m_Root)
		{
			delete m_Root;
			m_Root = nullptr;
		}
	}
private:
	void SetSelectedNode(TreeNode* _SelectedNode);

private:
	static  UINT    NodeID;

private:
	TreeNode* m_Root;
	TreeNode* m_Selected;
	bool            m_bShowRoot;

	UI* m_SelectInst;
	Delegate_1      m_SelectFunc;
	bool            m_bSelectEvent;
};
