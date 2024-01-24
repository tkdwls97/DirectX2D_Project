#pragma once
#include "UI.h"
#include <Engine/GameObject.h>


class ComponentUI : public UI
{
public:
	ComponentUI(const string& _strName, const string& _ID, COMPONENT_TYPE _Type);
	~ComponentUI();

public:
	virtual void Render_Update() override;

public:
	CGameObject* GetTargetObject() { return m_TargetObject; }
	void SetTargetObject(CGameObject* _Target);
	void SetComponentTitle(const string& _title) { m_ComponentTitle = _title; }
	COMPONENT_TYPE GetType() { return m_Type; }

private:
	CGameObject*	 m_TargetObject;
	COMPONENT_TYPE   m_Type;
	string			 m_ComponentTitle;
};

