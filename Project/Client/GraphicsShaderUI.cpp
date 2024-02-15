#include "pch.h"
#include "GraphicsShaderUI.h"


GraphicsShaderUI::GraphicsShaderUI()
	: AssetUI("GraphicsShaderUI", "##GraphicsShaderUI", ASSET_TYPE::GRAPHICS_SHADER)
{
}

GraphicsShaderUI::~GraphicsShaderUI()
{
}

void GraphicsShaderUI::Render_Update()
{
	AssetUI::Render_Update();
}
