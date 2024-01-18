#pragma once

#include "imgui.h"
#include "ImGuiMgr.h"

class UI
{
public:
	UI(const string& _strName, const string& _strID);
	virtual ~UI();

public:
	virtual void Tick();
	virtual void Render();
	virtual void Render_Update() = 0;

	virtual void Activate() { m_bActive = true; }
	virtual void Deactivate() { m_bActive = false; }

public:
	void SetName(const string& _name) { m_strName = _name; }
	void SetSize(ImVec2 _Size) { m_vSize = _Size; }
	void SetModal(bool _Modal) { m_bModal = _Modal; }
	
	ImVec2 GetSize() { return m_vSize; }
	const string& GetName() { return m_strName; }
	const string& GetID() { return m_strID; }
	void AddChildUI(UI* _ChildUI)
	{
		m_vecChildUI.push_back(_ChildUI);
		_ChildUI->m_Parent = this;
	}

	UI* GetParentUI() { return m_Parent; }
	bool IsActivate() { return m_bActive; }

private:
	string			m_strName;
	const string	m_strID;
	ImVec2			m_vSize;

	bool			m_bModal;
	bool			m_bActive;
	UI*				m_Parent;
	vector<UI*>		m_vecChildUI;

};

