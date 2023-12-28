#include "pch.h"
#include "Layer.h"

#include "GameObject.h"
#include "GarbageCollector.h"

CLayer::CLayer()
	: m_LayerIdx(-1)
{

}

CLayer::~CLayer()
{
	Delete_Vec(m_vecParent);
}

void CLayer::Begin()
{
	for (size_t i = 0; i < m_vecParent.size(); ++i)
	{
		m_vecParent[i]->Begin();
	}
}

void CLayer::Tick()
{
	for (size_t i = 0; i < m_vecParent.size(); ++i)
	{
		m_vecParent[i]->Tick();
	}
}

void CLayer::Finaltick()
{
	vector<CGameObject*>::iterator iter = m_vecParent.begin();

	for (; iter != m_vecParent.end(); )
	{
		(*iter)->Finaltick();

		if ((*iter)->IsDead())
		{
			CGarbageCollector::GetInst()->Add(*iter);
			iter = m_vecParent.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void CLayer::Render()
{
	for (size_t i = 0; i < m_vecObjects.size(); ++i)
	{
		m_vecObjects[i]->Render();
	}
}

void CLayer::AddObject(CGameObject* _Object, bool _bMove)
{
	// _bMove : true  - 레이어에 입력되는 Object가 자식이 있는 경우, 자식까지 모두 해당 레이어로 넘어온다.
	// _bMove : false - 레이어에 입력되는 Object의 자식은 해당 레이어로 같이 넘어오지 않는다. 단 자식오브젝트가 레이어 소속이 없는 경우(-1)에만 같이 변경한다.      AssortRock

	// 최상위 부모 오브젝트였다.
	if (nullptr == _Object->GetParent())
	{
		// 다른 레이어 소속이었다
		if (-1 != _Object->m_LayerIdx)
		{
			// 기존 레이어의 Parent 벡터에서 제거되어야 한다.
			_Object->DisconnectWithLayer();
		}

		// 최상위 부모 오브젝트는 m_vecParent 에서 가리키도록 한다.
		m_vecParent.push_back(_Object);
	}

	// 오브젝트의 레이어 소속을 현재 레이어로 변경
	// 자식 오브젝트들의 레이어 소속을 변경	
	list<CGameObject*> queue;
	queue.push_back(_Object);

	// 레이어에 입력되는 오브젝트 포함, 그 밑에 달린 자식들까지 모두 확인
	while (!queue.empty())
	{
		CGameObject* pObject = queue.front();
		queue.pop_front();

		for (size_t i = 0; i < pObject->m_vecChild.size(); ++i)
		{
			queue.push_back(pObject->m_vecChild[i]);
		}

		// 최초 입력 오브젝트는 무조건 해당 레이어 소속으로 변경
		if (pObject == _Object)
			pObject->m_LayerIdx = m_LayerIdx;
		else
		{
			// 자식 오브젝트들은 _bMove 가 true 인 경우, 부모를 따라서 해당 레이어소속으로 변경
			if (_bMove)
				pObject->m_LayerIdx = m_LayerIdx;
			// _bMove 가 false 경우에도, 자식 오브젝트의 레이어소속이 없다면 부모를 따라서 변경
			else if (-1 == pObject->m_LayerIdx)
				pObject->m_LayerIdx = m_LayerIdx;
		}
	}
}

void CLayer::DetachGameObject(CGameObject* _Object)
{
	assert(!(-1 == _Object->m_LayerIdx || _Object->m_LayerIdx != m_LayerIdx));

	// 부모 오브젝트가 있는 경우
	if (nullptr != _Object->GetParent())
	{
		_Object->m_LayerIdx = -1;
	}

	// 최상위 부모 오브젝트인 경우
	else
	{
		vector<CGameObject*>::iterator iter = m_vecParent.begin();
		for (; iter != m_vecParent.end(); ++iter)
		{
			if (*iter == _Object)
			{
				m_vecParent.erase(iter);
				_Object->m_LayerIdx = -1;
				return;
			}
		}
	}

	assert(nullptr);
}
