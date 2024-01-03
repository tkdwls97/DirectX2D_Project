#include "pch.h"
#include "Collider2D.h"

#include "Transform.h"

CCollider2D::CCollider2D()
	: CComponent(COMPONENT_TYPE::COLLIDER2D)
	, m_CollisionCount(0)
	, m_bAbsolute(false)
	, m_Type(COLLIDER2D_TYPE::RECT)
{
}

CCollider2D::~CCollider2D()
{
}

void CCollider2D::Finaltick()
{
	// �浹ü�� ���� ��� ���
	m_matColWorld = XMMatrixScaling(m_vOffsetScale.x, m_vOffsetScale.y, m_vOffsetScale.z);
	m_matColWorld *= XMMatrixTranslation(m_vOffsetPos.x, m_vOffsetPos.y, m_vOffsetPos.z);

	// �浹ü�� �����ų GameObject �� �������
	const Matrix& matObjWorld = Transform()->GetWorldMat();

	// GameObject �� Scale �� ������ ���� �������� ���
	if (m_bAbsolute)
	{
		Vec3 vWorldScale = Transform()->GetWorldScale();
		Matrix matScaleInv = XMMatrixScaling(vWorldScale.x, vWorldScale.y, vWorldScale.z);
		matScaleInv = XMMatrixInverse(nullptr, matScaleInv);

		// Object �� Scale �� ������� ���̿� ��ġ�ؼ� ��ȿȭ ��Ŵ
		m_matColWorld = m_matColWorld * matScaleInv * matObjWorld;
	}
	else
	{
		m_matColWorld *= matObjWorld;
	}


	// �浹���̸� Red, �浹�ϰ� ���� ������ Green
	if (0 == m_CollisionCount)
	{
		GamePlayStatic::DrawDebugRect(m_matColWorld, Vec3(0.f, 1.f, 0.f), false);
	}
	else
	{
		GamePlayStatic::DrawDebugRect(m_matColWorld, Vec3(1.f, 0.f, 0.f), false);
	}
}

void CCollider2D::BeginOverlap(CCollider2D* _OtherCollider)
{
	++m_CollisionCount;
}

void CCollider2D::Overlap(CCollider2D* _OtherCollider)
{
}

void CCollider2D::EndOverlap(CCollider2D* _OtherCollider)
{
	--m_CollisionCount;
}
