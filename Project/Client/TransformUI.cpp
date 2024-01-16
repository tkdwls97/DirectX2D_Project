#include "pch.h"
#include "TransformUI.h"

#include <Engine/Transform.h>

TransformUI::TransformUI()
	: UI("Transform", "##Transform")
	, m_TargetObject(nullptr)
{
}

TransformUI::~TransformUI()
{

}


void TransformUI::Render_Update()
{
	if (nullptr == m_TargetObject)
		return;

	Vec3 vPos = m_TargetObject->Transform()->GetRelativePos();
	Vec3 vScale = m_TargetObject->Transform()->GetRelativeScale();
	Vec3 vRot = m_TargetObject->Transform()->GetRelativeRotation();
	vRot.ToDegree();

	ImGui::InputFloat3("Relative Position", vPos);
	ImGui::InputFloat3("Relative Scale", vScale);
	ImGui::InputFloat3("Relative Rotation", vRot);

	vRot.ToRadian();
	m_TargetObject->Transform()->SetRelativePos(vPos);
	m_TargetObject->Transform()->SetRelativeScale(vScale);
	m_TargetObject->Transform()->SetRelativeRotation(vRot);
}
