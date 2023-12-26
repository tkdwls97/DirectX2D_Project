#pragma once
#include "Entity.h"

class CLayer;
class CGameObject;


class CLevel : public CEntity
{
	friend class CLevelMgr;
public:
	CLevel();
	~CLevel();

public:
	void Begin();
	void Tick();
	void Finaltick();
	void Render();

	void AddObject(CGameObject* _Object, int _LayerIdx, bool _bChildMove = true);
	CLayer* GetLayer(int _layerIdx) { return m_arrLayer[_layerIdx]; }

private:
	void clear();

private:
	CLayer* m_arrLayer[LAYER_MAX];
};

