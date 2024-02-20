#include "pch.h"
#include "MaterialUI.h"
#include "Engine/Material.h"

MaterialUI::MaterialUI()
	: AssetUI("Material", "##Material", ASSET_TYPE::MATERIAL)
{
}

MaterialUI::~MaterialUI()
{
}

void MaterialUI::Render_Update()
{
    // 해당 텍스쳐 이미지 출력
    Ptr<CMaterial> pMtrl = (CMaterial*)GetAsset().Get();
    string strPath = string(pMtrl->GetRelativePath().begin(), pMtrl->GetRelativePath().end());

    ImGui::Text("Material");
    ImGui::SameLine();
    ImGui::InputText("##TexName", (char*)strPath.c_str(), strPath.length(), ImGuiInputTextFlags_ReadOnly);
}
