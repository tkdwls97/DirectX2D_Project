#include "pch.h"
#include "ParticleUpdate.h"

CParticleUpdate::CParticleUpdate()
	: CComputeShader(1024, 1, 1)
{
	Create(L"shader\\particle_update.fx", "CS_ParticleUpdate");
}

CParticleUpdate::~CParticleUpdate()
{
}

int CParticleUpdate::UpdateData()
{
	if (nullptr == m_ParticleBuffer)
		return E_FAIL;

	m_Const.iArr[0] = m_ParticleBuffer->GetElementCount();
	m_ParticleBuffer->UpdateData_CS_UAV(0);

	return S_OK;
}

void CParticleUpdate::UpdateGroupCount()
{
	UINT GroupX = (m_ParticleBuffer->GetElementCount() / m_ThreadX);
	if (0 != m_ParticleBuffer->GetElementCount() % m_ThreadX)
		GroupX += 1;

	SetGroup(GroupX, 1, 1);
}

void CParticleUpdate::Clear()
{
	m_ParticleBuffer->Clear_CS_UAV();
	m_ParticleBuffer = nullptr;
}