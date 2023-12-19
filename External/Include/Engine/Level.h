#pragma once
#include "Entity.h"

class CLayer;
class CGameObject;


class CLevel : public CEntity
{
public:
	CLevel();
	~CLevel();

public:
	void Begin();
	void Tick();
	void Finaltick();
	void Render();

	void AddObject(CGameObject* _Object, int _LayerIdx);

private:
	CLayer* m_arrLayer[LAYER_MAX];
};

