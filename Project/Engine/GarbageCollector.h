#pragma once
#include "Singleton.h"

class CEntity;

class CGarbageCollector : public CSingleton<CGarbageCollector>
{
	SINGLE(CGarbageCollector);
public:
	void Tick();

	void Add(CEntity* _Entity) { m_vecEntity.push_back(_Entity); }


private:
	vector<CEntity*>    m_vecEntity;

};

