#pragma once
#include "Entity.h"

#include "GameObject.h"


class CComponent : public CEntity
{
	friend class CGameObject;

public:
	CComponent(COMPONENT_TYPE _Type);
	~CComponent();

public:
	virtual void Begin() {}
	virtual void Tick() {}
	virtual void Finaltick() = 0;
	virtual void UpdateData() {};

public:
	COMPONENT_TYPE GetType() { return m_Type; }
	CGameObject* GetOwner() { return m_Owner; }

	GET_OTHER_COMPONENT(Transform);
	GET_OTHER_COMPONENT(MeshRender);
	GET_OTHER_COMPONENT(Camera);
	GET_OTHER_COMPONENT(Collider2D);
	GET_OTHER_COMPONENT(Animator2D);

private:
	const COMPONENT_TYPE    m_Type;
	CGameObject* m_Owner;

};

