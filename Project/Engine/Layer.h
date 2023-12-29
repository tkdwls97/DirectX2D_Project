#pragma once
#include "Entity.h"

class CGameObject;


class CLayer : public CEntity
{
	friend class CLevel;
public:
	CLayer();
	~CLayer();

private:
	void Begin();
	void Tick();
	void Finaltick();

	void AddObject(CGameObject* _Object, bool _bMove);

public:
	// Ư�� ������Ʈ�� ���̾�� ����
	void DetachGameObject(CGameObject* _Object);
	void RegisterGameObject(CGameObject* _Object) { m_vecObjects.push_back(_Object); }

	int GetLayerIdx() { return m_LayerIdx; }

	const vector<CGameObject*>& GetParentObjects() { return  m_vecParent; }
	const vector<CGameObject*>& GetLayerObjects() { return m_vecObjects; }

private:
	vector<CGameObject*>    m_vecParent;
	vector<CGameObject*>    m_vecObjects;
	int                     m_LayerIdx;


};
