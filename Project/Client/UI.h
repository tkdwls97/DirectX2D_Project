#pragma once

#include "imgui.h"

class UI
{
public:
	UI(const string& _strName, const string& _strID);
	~UI();

public:
	virtual void Tick();
	virtual void Render();
	virtual void Render_Update() = 0;


public:
	void SetName(const string& _name) { m_strName = _name; }
	const string& GetName() { return m_strName; }
	const string& GetID() { return m_strID; }
	void AddChildUI(UI* _ChildUI)
	{
		m_vecChildUI.push_back(_ChildUI);
		_ChildUI->m_Parent = this;
	}

	UI* GetParentUI() { return m_Parent; }
	void Activate() { m_bActive = true; }
	void Deactivate() { m_bActive = false; }
	bool IsActivate() { return m_bActive; }

private:
	string			m_strName;
	const string	m_strID;

	bool			m_bActive;
	UI*				m_Parent;
	vector<UI*>		m_vecChildUI;
};

