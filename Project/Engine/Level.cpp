#include "pch.h"
#include "Level.h"

#include "Layer.h"

CLevel::CLevel()
	: m_arrLayer{}
{
	for (UINT i = 0; i < LAYER_MAX; ++i)
	{
		m_arrLayer[i] = new CLayer;
		m_arrLayer[i]->m_LayerIdx = i;
	}
}

CLevel::~CLevel()
{
	Delete_Array(m_arrLayer);
}

void CLevel::Begin()
{
	for (int i = 0; i < LAYER_MAX; ++i)
	{
		m_arrLayer[i]->Begin();
	}
}

void CLevel::Tick()
{
	for (int i = 0; i < LAYER_MAX; ++i)
	{
		m_arrLayer[i]->Tick();
	}
}

void CLevel::Finaltick()
{
	for (int i = 0; i < LAYER_MAX; ++i)
	{
		m_arrLayer[i]->Finaltick();
	}
}

void CLevel::Render()
{
	for (int i = 0; i < LAYER_MAX; ++i)
	{
		m_arrLayer[i]->Render();
	}
}

void CLevel::AddObject(CGameObject* _Object, int _LayerIdx, bool _bChildMove)
{
	m_arrLayer[_LayerIdx]->AddObject(_Object, _bChildMove);
}

void CLevel::clear()
{
	for (UINT i = 0; i < LAYER_MAX; ++i)
	{
		m_arrLayer[i]->m_vecObjects.clear();
	}
}
