#include "pch.h"
#include "GameObject.h"

#include "Component.h"
#include "RenderComponent.h"

CGameObject::CGameObject()
	: m_arrCom{}
	, m_RenderCom(nullptr)
{
}

CGameObject::~CGameObject()
{
	Delete_Array(m_arrCom);
}

void CGameObject::begin()
{
	for (UINT i = 0; i < UINT(COMPONENT_TYPE::END); ++i)
	{
		if (nullptr != m_arrCom[i])
		{
			m_arrCom[i]->begin();
		}
	}
}

void CGameObject::tick()
{
	for (UINT i = 0; i < UINT(COMPONENT_TYPE::END); ++i)
	{
		if (nullptr != m_arrCom[i])
		{
			m_arrCom[i]->tick();
		}
	}
}

void CGameObject::finaltick()
{
	for (UINT i = 0; i < UINT(COMPONENT_TYPE::END); ++i)
	{
		if (nullptr != m_arrCom[i])
		{
			m_arrCom[i]->finaltick();
		}
	}
}

void CGameObject::render()
{
	if (nullptr != m_RenderCom)
	{
		m_RenderCom->render();
	}
}

void CGameObject::AddComponent(CComponent* _Comonent)
{
	COMPONENT_TYPE type = _Comonent->GetType();

	m_arrCom[(UINT)type] = _Comonent;
	_Comonent->m_Owner = this;

	m_RenderCom = dynamic_cast<CRenderComponent*>(_Comonent);
}