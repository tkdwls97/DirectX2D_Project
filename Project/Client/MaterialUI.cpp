#include "pch.h"
#include "MaterialUI.h"

#include <Engine/Material.h>
#include <Engine/GraphicsShader.h>
#include <Engine/Texture.h>

#include "ParamUI.h"

MaterialUI::MaterialUI()
    : AssetUI("Material", "##Material", ASSET_TYPE::MATERIAL)
{
}

MaterialUI::~MaterialUI()
{
}


void MaterialUI::Render_Update()
{
    AssetUI::Render_Update();

    // 해당 텍스쳐 이미지 출력
    Ptr<CMaterial> pMtrl = (CMaterial*)GetAsset().Get();
    string strPath = string(pMtrl->GetRelativePath().begin(), pMtrl->GetRelativePath().end());

    ImGui::Text("Material");
    ImGui::SameLine();
    ImGui::InputText("##TexName", (char*)strPath.c_str(), strPath.length(), ImGuiInputTextFlags_ReadOnly);

    Ptr<CGraphicsShader> pShader = pMtrl->GetShader();
    string strShaderName;
    if (nullptr != pShader)
    {
        strShaderName = string(pShader->GetKey().begin(), pShader->GetKey().end());
    }

    ImGui::Text("Shader  ");
    ImGui::SameLine();
    ImGui::InputText("##ShaderName", (char*)strShaderName.c_str(), strShaderName.length(), ImGuiInputTextFlags_ReadOnly);


    // Shader Parameter
    if (nullptr == pShader)
        return;

    const vector<tScalarParam>& vecScalarParam = pShader->GetScalarParam();
    for (size_t i = 0; i < vecScalarParam.size(); ++i)
    {
        switch (vecScalarParam[i].Type)
        {
        case INT_0:
        case INT_1:
        case INT_2:
        case INT_3:
        {
            int value = *(int*)pMtrl->GetScalarParam(vecScalarParam[i].Type);
            if (ParamUI::Param_INT(&value, vecScalarParam[i].Desc))
            {
                pMtrl->SetScalarParam(vecScalarParam[i].Type, value);
            }
        }
        break;
        case FLOAT_0:
        case FLOAT_1:
        case FLOAT_2:
        case FLOAT_3:
            break;
        case VEC2_0:
        case VEC2_1:
        case VEC2_2:
        case VEC2_3:
            break;
        case VEC4_0:
        case VEC4_1:
        case VEC4_2:
        case VEC4_3:
            break;
        case MAT_0:
        case MAT_1:
        case MAT_2:
        case MAT_3:
            break;
        }

    }
}