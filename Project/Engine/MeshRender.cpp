#include "pch.h"
#include "MeshRender.h"

#include "Mesh.h"
#include "GraphicsShader.h"

#include "GameObject.h"
#include "Animator2D.h"
#include "Transform.h"
#include "Material.h"
#include "RenderMgr.h"

CMeshRender::CMeshRender()
	: CRenderComponent(COMPONENT_TYPE::MESHRENDER)
{
}

CMeshRender::~CMeshRender()
{
}

void CMeshRender::UpdateData()
{
	if (nullptr != GetMaterial())
	{
		GetMaterial()->UpdateData();
	}

	Transform()->UpdateData();
}

void CMeshRender::Finaltick()
{
	if (CRenderMgr::GetInst()->IsDebugPosition())
	{
		GamePlayStatic::DrawDebugCross(Transform()->GetWorldPos(), 20.f, Vec3(0.f, 1.f, 0.f), true);

	}
}

void CMeshRender::Render()
{
	if (nullptr == GetMesh() || nullptr == GetMaterial())
		return;

	if (Animator2D())
	{
		Animator2D()->UpdateData();
	}
	else
	{
		Animator2D()->Clear();
	}

	UpdateData();

	GetMesh()->Render();

}