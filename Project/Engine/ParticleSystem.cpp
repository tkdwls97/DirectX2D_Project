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
	, m_MaxParticleCount(100)
{
	// ���� �޽��� ���� ���� ���
	SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"ParticleMtrl"));

	// ������ �ػ�
	Vec2 vResol = CDevice::GetInst()->GetRenderResolution();

	// �ӽ÷� 5���� ��ƼŬ�� �ʱ� �����͸� �Է��ϸ鼭 ����ȭ ���� ����
	tParticle arrParticle[1000] = { };
	for (int i = 0; i < m_MaxParticleCount; ++i)
	{
		arrParticle[i].vWorldPos = Vec3((vResol.x / -2.f) + (i + 1) * vResol.x / (m_MaxParticleCount + 1), 0.f, 200.f);
		arrParticle[i].vWorldScale = Vec3(10.f, 10.f, 1.f);
		arrParticle[i].Active = 1;
	}

	m_ParticleBuffer = new CStructuredBuffer;
	m_ParticleBuffer->Create(sizeof(tParticle), m_MaxParticleCount, SB_TYPE::READ_WRITE, true, arrParticle);

	// ��ƼŬ ������Ʈ�� ��ǻƮ ���̴� ����
	m_CSParticleUpdate = (CParticleUpdate*)CAssetMgr::GetInst()->FindAsset<CComputeShader>(L"ParticleUpdateShader").Get();
}

CParticleSystem::~CParticleSystem()
{
	if (nullptr != m_ParticleBuffer)
		delete m_ParticleBuffer;
}


void CParticleSystem::Finaltick()
{
	// ��Ƽ�� ������Ʈ ��ǻƮ ���̴�
	m_CSParticleUpdate->SetParticleBuffer(m_ParticleBuffer);
	m_CSParticleUpdate->Execute();

	tParticle arrParticle[100] = { };
	m_ParticleBuffer->GetData(arrParticle);
}

void CParticleSystem::Render()
{
	// View, Proj ��� ����
	Transform()->UpdateData();

	// ParticleBuffer ���ε�
	m_ParticleBuffer->UpdateData(20);

	// ��� ��ƼŬ ������
	// ��ƼŬ ���� ������ -> �ν��Ͻ�
	GetMaterial()->SetScalarParam(INT_0, 0);
	GetMaterial()->UpdateData();
	GetMesh()->Render_Particle(m_MaxParticleCount);

	// �������� ����� ���ҽ� ���ε� Clear
	m_ParticleBuffer->Clear(20);
}

void CParticleSystem::UpdateData()
{
}