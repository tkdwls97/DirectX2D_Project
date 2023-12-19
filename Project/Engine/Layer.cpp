#include "pch.h"
#include "Layer.h"

#include "GameObject.h"

CLayer::CLayer()
{

}

CLayer::~CLayer()
{

}

void CLayer::Begin()
{
	for (size_t i = 0; i < m_vecParent.size(); ++i)
	{
		m_vecParent[i]->Begin();
	}
}

void CLayer::Tick()
{
	for (size_t i = 0; i < m_vecParent.size(); ++i)
	{
		m_vecParent[i]->Tick();
	}
}

void CLayer::Finaltick()
{
	for (size_t i = 0; i < m_vecParent.size(); ++i)
	{
		m_vecParent[i]->Finaltick();
	}
}

void CLayer::Render()
{
	for (size_t i = 0; i < m_vecParent.size(); ++i)
	{
		m_vecParent[i]->Render();
	}
}