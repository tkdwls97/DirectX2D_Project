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
	// _bMove : true  - ���̾ �ԷµǴ� Object�� �ڽ��� �ִ� ���, �ڽı��� ��� �ش� ���̾�� �Ѿ�´�.
	// _bMove : false - ���̾ �ԷµǴ� Object�� �ڽ��� �ش� ���̾�� ���� �Ѿ���� �ʴ´�. �� �ڽĿ�����Ʈ�� ���̾� �Ҽ��� ���� ���(-1)���� ���� �����Ѵ�.      AssortRock

	// �ֻ��� �θ� ������Ʈ����.
	if (nullptr == _Object->GetParent())
	{
		// �ٸ� ���̾� �Ҽ��̾���
		if (-1 != _Object->m_LayerIdx)
		{
			// ���� ���̾��� Parent ���Ϳ��� ���ŵǾ�� �Ѵ�.
			_Object->DisconnectWithLayer();
		}

		// �ֻ��� �θ� ������Ʈ�� m_vecParent ���� ����Ű���� �Ѵ�.
		m_vecParent.push_back(_Object);
	}

	// ������Ʈ�� ���̾� �Ҽ��� ���� ���̾�� ����
	// �ڽ� ������Ʈ���� ���̾� �Ҽ��� ����	
	list<CGameObject*> queue;
	queue.push_back(_Object);

	// ���̾ �ԷµǴ� ������Ʈ ����, �� �ؿ� �޸� �ڽĵ���� ��� Ȯ��
	while (!queue.empty())
	{
		CGameObject* pObject = queue.front();
		queue.pop_front();

		for (size_t i = 0; i < pObject->m_vecChild.size(); ++i)
		{
			queue.push_back(pObject->m_vecChild[i]);
		}

		// ���� �Է� ������Ʈ�� ������ �ش� ���̾� �Ҽ����� ����
		if (pObject == _Object)
			pObject->m_LayerIdx = m_LayerIdx;
		else
		{
			// �ڽ� ������Ʈ���� _bMove �� true �� ���, �θ� ���� �ش� ���̾�Ҽ����� ����
			if (_bMove)
				pObject->m_LayerIdx = m_LayerIdx;
			// _bMove �� false ��쿡��, �ڽ� ������Ʈ�� ���̾�Ҽ��� ���ٸ� �θ� ���� ����
			else if (-1 == pObject->m_LayerIdx)
				pObject->m_LayerIdx = m_LayerIdx;
		}
	}
}

void CLayer::DetachGameObject(CGameObject* _Object)
{
	assert(!(-1 == _Object->m_LayerIdx || _Object->m_LayerIdx != m_LayerIdx));

	// �θ� ������Ʈ�� �ִ� ���
	if (nullptr != _Object->GetParent())
	{
		_Object->m_LayerIdx = -1;
	}

	// �ֻ��� �θ� ������Ʈ�� ���
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
