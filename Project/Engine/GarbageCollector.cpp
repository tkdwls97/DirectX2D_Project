#include "pch.h"
#include "GarbageCollector.h"

#include "Entity.h"


CGarbageCollector::CGarbageCollector()
{

}

CGarbageCollector::~CGarbageCollector()
{
	Delete_Vec(m_vecEntity);
}

void CGarbageCollector::Tick()
{
	if (100 <= m_vecEntity.size())
	{
		Delete_Vec(m_vecEntity);
	}
}
