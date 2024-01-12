#include "pch.h"
#include "Light2D.h"

#include "RenderMgr.h"
#include "Transform.h"

CLight2D::CLight2D()
	: CComponent(COMPONENT_TYPE::LIGHT2D)
{
}

CLight2D::~CLight2D()
{

}

void CLight2D::Finaltick()
{
	// ���� ��ġ���� LightInfo �ɹ��� �����س��´�.
	Vec3 vWorldPos = Transform()->GetWorldPos();
	Vec3 vWorldDir = Transform()->GetWorldDir(DIR_TYPE::RIGHT);

	m_Info.vWorldPos = vWorldPos;
	m_Info.vWorldDir = vWorldDir;

	// ���� ���
	CRenderMgr::GetInst()->RegisterLight2D(this);
}

void CLight2D::SetLightType(LIGHT_TYPE _type)
{
	m_Info.LightType = (int)_type;

}

void CLight2D::SetRadius(float _Radius)
{
	m_Info.fRadius = _Radius;
}

void CLight2D::SetAngle(float _Angle)
{
	m_Info.fAngle = _Angle;
}
