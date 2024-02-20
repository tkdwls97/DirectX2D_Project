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


public:
	void AddObject(CGameObject* _Object, int _LayerIdx, bool _bChildMove = true);
	void AddObject(CGameObject* _Object, const wstring& _strLayerName, bool _bChildMove = true);

	CLayer* GetLayer(int _layerIdx) { return m_ArrLayer[_layerIdx]; }
	CLayer* GetLayer(const wstring& _strLayerName);

	CGameObject* FindObjectByName(const wstring& _strName);
	void FindObjectsByName(const wstring& _strName, vector<CGameObject*>& _vecObj);

private:
	void Clear();

private:
	CLayer*	 m_ArrLayer[LAYER_MAX];
};

