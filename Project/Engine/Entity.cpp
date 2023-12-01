#include "pch.h"
#include "Entity.h"


UINT CEntity::g_NextID = 0;
CEntity::CEntity()
	: m_ID(g_NextID++)
{
}

CEntity::~CEntity()
{
}

void CEntity::SetName(const wstring& _strName)
{
	m_strName = _strName;
}

const wstring& CEntity::GetName()
{
	return m_strName;

}

UINT CEntity::GetID()
{
	return m_ID;
}

