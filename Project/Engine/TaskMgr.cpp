#include "pch.h"

#include "TaskMgr.h"
#include "LevelMgr.h"
#include "Level.h"
#include "GameObject.h"
#include "Component.h"

CTaskMgr::CTaskMgr()
{

}

CTaskMgr::~CTaskMgr()
{

}

void CTaskMgr::Tick()
{
	for (size_t i = 0; i < m_vecTask.size(); ++i)
	{
		switch (m_vecTask[i].Type)
		{
		case TASK_TYPE::CREATE_OBJECT:
		{
			int LayerIdx = (int)m_vecTask[i].Param_1;
			CGameObject* Object = (CGameObject*)m_vecTask[i].Param_2;

			CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
			pCurLevel->AddObject(Object, LayerIdx, true);

			/*if (LEVEL_STATE::PLAY == pCurLevel->GetState())
			{
				Object->begin();
			}*/
			break;
		}
		case TASK_TYPE::DELETE_OBJECT:
		{
			CGameObject* pDeadObj = (CGameObject*)m_vecTask[i].Param_1;

			list<CGameObject*> queue;
			queue.push_back(pDeadObj);

			// ���̾ �ԷµǴ� ������Ʈ ����, �� �ؿ� �޸� �ڽĵ���� ��� Ȯ��
			while (!queue.empty())
			{
				CGameObject* pObject = queue.front();
				queue.pop_front();

				pObject->m_bDead = true;

				for (size_t i = 0; i < pObject->m_vecChild.size(); ++i)
				{
					queue.push_back(pObject->m_vecChild[i]);
				}
			}
			break;
		}

		case TASK_TYPE::LEVEL_CHANGE:
		{

			break;
		}
		case TASK_TYPE::ADD_CHILD:
		{
			break;
		}
		case TASK_TYPE::DISCONNECT_PARENT:
		{
			break;

		}

		m_vecTask.clear();
		}
	}
}