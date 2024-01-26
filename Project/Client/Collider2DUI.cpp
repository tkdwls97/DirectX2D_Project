#include "pch.h"
#include "Collider2DUI.h"

#include <Engine/Collider2D.h>

Collider2DUI::Collider2DUI()
	: ComponentUI("Collider2D", "##Collider2D", COMPONENT_TYPE::COLLIDER2D)
{
	SetSize(ImVec2(0.f, 150.f));
	SetComponentTitle("Collider2D");
}

Collider2DUI::~Collider2DUI()
{
}

void Collider2DUI::Render_Update()
{
	if (nullptr == GetTargetObject())
		return;

	ComponentUI::Render_Update();

	Vec2 vOffsetPos = GetTargetObject()->Collider2D()->GetOffsetPos();
	Vec2 vOffsetScale = GetTargetObject()->Collider2D()->GetOffsetScale();
	float fRadius = GetTargetObject()->Collider2D()->GetOffsetRadius();
	bool bAbsolute = GetTargetObject()->Collider2D()->IsAbsolute();
	COLLIDER2D_TYPE eColliderType = GetTargetObject()->Collider2D()->GetType();
	int iCollisionCount = GetTargetObject()->Collider2D()->GetCollisionCount();

	// Position
	ImGui::Text("Offset Pos");
	ImGui::SameLine();
	ImGui::DragFloat2("##Offset Position", vOffsetPos);

	// Scale
	ImGui::Text("Offset Scale");
	ImGui::SameLine();

	GetTargetObject()->Collider2D()->SetOffsetPos(vOffsetPos);

	if (eColliderType == COLLIDER2D_TYPE::RECT)
	{
		ImGui::DragFloat2("##Offset Scale", vOffsetScale);

		GetTargetObject()->Collider2D()->SetOffsetScale(vOffsetScale);
	}
	else
	{
		ImGui::DragFloat("##Offset Radius", &fRadius);

		GetTargetObject()->Collider2D()->SetOffsetRadius(fRadius);
	}


	ImGui::Text("Scale Absolute Check");
	ImGui::SameLine();
	ImGui::Checkbox("##Scale Absolute Check", &bAbsolute);
	GetTargetObject()->Collider2D()->SetAbsolute(bAbsolute);

	ImGui::Text("Collider Type");
	ImGui::SameLine();
	const char* items[] = { "RECT", "CIRCLE" };
	static int item_current_idx = 0; // Here we store our selection data as an index.

	// Pass in the preview value visible before opening the combo (it could technically be different contents or not pulled from items[])
	const char* combo_preview_value = items[(int)eColliderType];

	if (ImGui::BeginCombo("##Collider Type", combo_preview_value))
	{
		for (int i = 0; i < IM_ARRAYSIZE(items); i++)
		{
			const bool is_selected = (item_current_idx == i);
			if (ImGui::Selectable(items[i], is_selected))
			{
				eColliderType = COLLIDER2D_TYPE(i);
			}

			// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
			if (is_selected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}

	GetTargetObject()->Collider2D()->SetColliderType(eColliderType);


	ImGui::Text("Collision Count : ");
	ImGui::SameLine();
	
	string str = std::to_string(iCollisionCount);
	ImGui::Text((str.c_str()));

	
	


}