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
	void Render();

	void AddObject(CGameObject* _Object) { m_vecParent.push_back(_Object); }


private:
	vector<CGameObject*>    m_vecParent;

};

