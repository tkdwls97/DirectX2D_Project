#pragma once

#include "Entity.h"

class CGameObject;

class CComponent : public CEntity
{
	friend class CGameObject;
public:
	CComponent(COMPONENT_TYPE _Type);
	~CComponent();

public:
	virtual void begin() {}
	virtual void tick() {}
	virtual void finaltick() = 0;
	virtual void UpdateData() {};

public:
	COMPONENT_TYPE GetType() { return m_Type; }
	CGameObject* GetOwner() { return m_Owner; }

private:
	const COMPONENT_TYPE    m_Type;
	CGameObject* m_Owner;

};

