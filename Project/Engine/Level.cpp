#include "pch.h"
#include "Level.h"

#include "Layer.h"

CLevel::CLevel()
	: m_ArrLayer{}
{
	for (UINT i = 0; i < LAYER_MAX; ++i)
	{
		m_ArrLayer[i] = new CLayer;
		m_ArrLayer[i]->m_LayerIdx = i;
	}
}

CLevel::~CLevel()
{
	Delete_Array(m_ArrLayer);
}

void CLevel::Begin()
{
	for (int i = 0; i < LAYER_MAX; ++i)
	{
		m_ArrLayer[i]->Begin();
	}
}

void CLevel::Tick()
{
	for (int i = 0; i < LAYER_MAX; ++i)
	{
		m_ArrLayer[i]->Tick();
	}
}

void CLevel::Finaltick()
{
	for (int i = 0; i < LAYER_MAX; ++i)
	{
		m_ArrLayer[i]->Finaltick();
	}
}


void CLevel::AddObject(CGameObject* _Object, int _LayerIdx, bool _bChildMove)
{
	m_ArrLayer[_LayerIdx]->AddObject(_Object, _bChildMove);
}

void CLevel::AddObject(CGameObject* _Object, const wstring& _strLayerName, bool _bChildMove)
{
	CLayer* pLayer = GetLayer(_strLayerName);
	if (nullptr == pLayer)
		return;

	pLayer->AddObject(_Object, _bChildMove);
}

CLayer* CLevel::GetLayer(const wstring& _strLayerName)
{
	for (int i = 0; i < LAYER_MAX; ++i)
	{
		if (_strLayerName == m_ArrLayer[i]->GetName())
		{
			return m_ArrLayer[i];
		}
	}
	return nullptr;
}

void CLevel::Clear()
{
	for (UINT i = 0; i < LAYER_MAX; ++i)
	{
		m_ArrLayer[i]->m_vecObjects.clear();
	}
}
