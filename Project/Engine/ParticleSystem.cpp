#include "pch.h"
#include "ParticleSystem.h"

#include "Device.h"
#include "StructuredBuffer.h"

#include "AssetMgr.h"
#include "Mesh.h"
#include "Material.h"
#include "Transform.h"

CParticleSystem::CParticleSystem()
	: CRenderComponent(COMPONENT_TYPE::PARTICLESYSTEM)
	, m_ParticleBuffer(nullptr)
	, m_MaxParticleCount(5)
{
	// ���� �޽��� ���� ���� ���
	SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"ParticleMtrl"));

	// ������ �ػ�
	Vec2 vResol = CDevice::GetInst()->GetRenderResolution();

	// �ӽ÷� 5���� ��ƼŬ�� �ʱ� �����͸� �Է��ϸ鼭 ����ȭ ���� ����
	tParticle arrParticle[5] = { };
	for (int i = 0; i < m_MaxParticleCount; ++i)
	{
		arrParticle[i].vWorldPos = Vec3((vResol.x / -2.f) + (i + 1) * vResol.x / (m_MaxParticleCount + 1), 0.f, 200.f);
		arrParticle[i].vWorldScale = Vec3(50.f, 50.f, 1.f);
	}

	m_ParticleBuffer = new CStructuredBuffer;
	m_ParticleBuffer->Create(sizeof(tParticle), 5, SB_TYPE::READ_WRITE, true, arrParticle);
}

CParticleSystem::~CParticleSystem()
{
	if (nullptr != m_ParticleBuffer)
		delete m_ParticleBuffer;
}


void CParticleSystem::Finaltick()
{
	// ��Ƽ�� ������Ʈ ��ǻƮ ���̴�

}

void CParticleSystem::Render()
{
	// View, Proj ��� ����
	Transform()->UpdateData();

	// ParticleBuffer ���ε�
	m_ParticleBuffer->UpdateData(20);

	// ��� ��ƼŬ ������
	for (int i = 0; i < m_MaxParticleCount; ++i)
	{
		GetMaterial()->SetScalarParam(INT_0, i);
		GetMaterial()->UpdateData();
		GetMesh()->Render();
	}

	// ��ƼŬ ���� ������ -> �ν��Ͻ�
}

void CParticleSystem::UpdateData()
{
}