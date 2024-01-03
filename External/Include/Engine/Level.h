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

	void AddObject(CGameObject* _Object, int _LayerIdx, bool _bChildMove = true);
	void AddObject(CGameObject* _Object, const wstring& _strLayerName, bool _bChildMove = true);

	CLayer* GetLayer(int _layerIdx) { return m_ArrLayer[_layerIdx]; }
	CLayer* GetLayer(const wstring& _strLayerName);

private:
	void Clear();

private:
	CLayer*	 m_ArrLayer[LAYER_MAX];
};

