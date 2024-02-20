#include "pch.h"
#include "RenderComponent.h"

CRenderComponent::CRenderComponent(COMPONENT_TYPE _Type)
	: CComponent(_Type)
{
}

CRenderComponent::~CRenderComponent()
{

}

void CRenderComponent::SetMaterial(Ptr<CMaterial> _Mtrl)
{
	// ������ ����Ǹ� ������ ���纻 �޾Ƶ� DynamicMaterial �� �����Ѵ�.
	m_CurMtrl = m_SharedMtrl = _Mtrl;
	m_DynamicMtrl = nullptr;
}


Ptr<CMaterial> CRenderComponent::GetDynamicMaterial()
{
	// �̹� ���������� �����ϰ� ������ �װ� �ش�.
	if (nullptr != m_DynamicMtrl)
		return m_DynamicMtrl;

	// ���������� �ִٸ�
	if (nullptr != m_SharedMtrl)
	{
		// ���������� �����ؼ� ���������� ����� �װ� ���� ��������� �����Ѵ�.
		m_CurMtrl = m_DynamicMtrl = m_SharedMtrl->Clone();
		return m_DynamicMtrl;
	}

	return nullptr;
}

void CRenderComponent::RestoreMaterial()
{
	m_CurMtrl = m_SharedMtrl;
}