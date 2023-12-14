#include "pch.h"
#include "MeshRender.h"

#include "Mesh.h"
#include "GraphicsShader.h"

#include "GameObject.h"
#include "Transform.h"

CMeshRender::CMeshRender()
	: CRenderComponent(COMPONENT_TYPE::MESHRENDER)
{
}

CMeshRender::~CMeshRender()
{
}

void CMeshRender::UpdateData()
{
	if (nullptr != GetShader())
	{
		GetShader()->UpdateData();
	}

	GetOwner()->Transform()->UpdateData();
}

void CMeshRender::render()
{
	if (nullptr == GetMesh() || nullptr == GetShader())
		return;

	UpdateData();

	GetMesh()->render();
}