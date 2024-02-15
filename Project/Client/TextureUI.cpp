#include "pch.h"
#include "TextureUI.h"

#include <Engine/Texture.h>

TextureUI::TextureUI()
    : AssetUI("Texture", "##Texture", ASSET_TYPE::TEXTURE)
{
}

TextureUI::~TextureUI()
{
}

void TextureUI::Render_Update()
{
    AssetUI::Render_Update();

    // �ش� �ؽ��� �̹��� ���
    Ptr<CTexture> pTex = (CTexture*)GetAsset().Get();

    static bool use_text_color_for_tint = false;
    ImVec2 uv_min = ImVec2(0.0f, 0.0f);                 // Top-left
    ImVec2 uv_max = ImVec2(1.0f, 1.0f);                 // Lower-right
    ImVec4 tint_col = use_text_color_for_tint ? ImGui::GetStyleColorVec4(ImGuiCol_Text) : ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // No tint
    ImVec4 border_col = ImGui::GetStyleColorVec4(ImGuiCol_Border);
    ImGui::Image(pTex->GetSRV().Get(), ImVec2(150, 150), uv_min, uv_max, tint_col, border_col);


    // �ػ� ���� ���
    float Width = pTex->GetWidth();
    float Height = pTex->GetHeight();

    ImGui::Text("Width ");
    ImGui::SameLine();
    ImGui::InputFloat("##TextureWidth", &Width, 0.f, 0.f, "%.3f", ImGuiInputTextFlags_ReadOnly);

    ImGui::Text("Height");
    ImGui::SameLine();
    ImGui::InputFloat("##TextureHeight", &Height, 0.f, 0.f, "%.3f", ImGuiInputTextFlags_ReadOnly);
}