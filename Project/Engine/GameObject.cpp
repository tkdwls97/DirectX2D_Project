#include "pch.h"
#include "GameObject.h"

#include "Component.h"
#include "RenderComponent.h"

#include "Script.h"

#include "LevelMgr.h"
#include "Level.h"
#include "Layer.h"
#include "GarbageCollector.h"

CGameObject::CGameObject()
	: m_arrCom{}
	, m_RenderCom(nullptr)
	, m_Parent(nullptr)
	, m_LayerIdx(-1) // ��� ����(���̾�) �ҼӵǾ����� �ʴ�.
	, m_bDead(false)
{
}

CGameObject::~CGameObject()
{
	Delete_Array(m_arrCom);
	Delete_Vec(m_vecScript);
	Delete_Vec(m_vecChild);
}

void CGameObject::Begin()
{
	for (UINT i = 0; i < UINT(COMPONENT_TYPE::END); ++i)
	{
		if (nullptr != m_arrCom[i])
		{
			m_arrCom[i]->Begin();
		}
	}

	for (size_t i = 0; i < m_vecScript.size(); ++i)
	{
		m_vecScript[i]->Begin();
	}

	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->Begin();
	}
}

void CGameObject::Tick()
{
	for (UINT i = 0; i < UINT(COMPONENT_TYPE::END); ++i)
	{
		if (nullptr != m_arrCom[i])
		{
			m_arrCom[i]->Tick();
		}
	}

	for (size_t i = 0; i < m_vecScript.size(); ++i)
	{
		m_vecScript[i]->Tick();
	}

	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->Tick();
	}
}

void CGameObject::Finaltick()
{
	for (UINT i = 0; i < UINT(COMPONENT_TYPE::END); ++i)
	{
		if (nullptr != m_arrCom[i])
		{
			m_arrCom[i]->Finaltick();
		}
	}

	CLayer* pCurLayer = CLevelMgr::GetInst()->GetCurrentLevel()->GetLayer(m_LayerIdx);
	pCurLayer->RegisterGameObject(this);

	vector<CGameObject*>::iterator iter = m_vecChild.begin();
	for (; iter != m_vecChild.end();)
	{
		(*iter)->Finaltick();

		if ((*iter)->m_bDead)
		{
			CGarbageCollector::GetInst()->Add(*iter);
			iter = m_vecChild.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void CGameObject::Render()
{
	if (nullptr != m_RenderCom)
	{
		m_RenderCom->Render();
	}

	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->Render();
	}
}

void CGameObject::AddComponent(CComponent* _Comonent)
{
	COMPONENT_TYPE type = _Comonent->GetType();

	if (type == COMPONENT_TYPE::SCRIPT)
	{
		// Script Ÿ�� Component �� ������ Script Ŭ������ �ƴ� ���
		assert(dynamic_cast<CScript*>(_Comonent));

		m_vecScript.push_back((CScript*)_Comonent);
		_Comonent->m_Owner = this;
	}
	else
	{
		// �̹� �ش� Ÿ���� ������Ʈ�� �����ϰ� �ִ� ��� 
		assert(!m_arrCom[(UINT)type]);

		m_arrCom[(UINT)type] = _Comonent;
		_Comonent->m_Owner = this;

		CRenderComponent* pRenderCom = dynamic_cast<CRenderComponent*>(_Comonent);
		if (nullptr != pRenderCom)
		{
			// �̹� �� ���� �̻��� RenderComponent �� �����ϰ� �ִ� ���
			assert(!m_RenderCom);

			m_RenderCom = pRenderCom;
		}
	}
}

void CGameObject::AddChild(CGameObject* _Child)
{
	if (_Child->m_Parent)
	{
		// ���� �θ� ������Ʈ�� ���� ����
		_Child->DisconnectWithParent();
	}

	// �θ� �ڽ� ����
	_Child->m_Parent = this;
	m_vecChild.push_back(_Child);
}

void CGameObject::DisconnectWithParent()
{
	vector<CGameObject*>::iterator iter = m_Parent->m_vecChild.begin();
	for (; iter != m_Parent->m_vecChild.end(); ++iter)
	{
		if (*iter == this)
		{
			m_Parent->m_vecChild.erase(iter);
			m_Parent = nullptr;
			return;
		}
	}

	// �θ� ���� ������Ʈ�� DisconnectWithParent �Լ��� ȣ�� �߰ų�
	// �θ�� �ڽ��� ����Ű���� �ʰ� �ִµ�, �ڽ��� �θ� ����Ű�� �ִ� ���
	assert(nullptr);
}

void CGameObject::DisconnectWithLayer()
{
	if (-1 == m_LayerIdx)
		return;

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	CLayer* pCurLayer = pCurLevel->GetLayer(m_LayerIdx);
	pCurLayer->DetachGameObject(this);
}

void CGameObject::Destroy()
{
	GamePlayStatic::DestroyGameObject(this);
}


