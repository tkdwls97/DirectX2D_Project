#include "pch.h"
#include "TileMap.h"

#include "AssetMgr.h"
#include "Mesh.h"

#include "Transform.h"

CTileMap::CTileMap()
	: CRenderComponent(COMPONENT_TYPE::TILEMAP)
	, m_FaceX(2)
	, m_FaceY(2)
	, m_vTileRenderSize(Vec2(128.f, 128.f))
	, m_TileIdx(47)
{
	SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"TileMapMtrl"));
}

CTileMap::~CTileMap()
{
}

void CTileMap::Finaltick()
{
	// (Ÿ�� ���� * Ÿ�� ������) �� ����� ����ó���Ѵ�.
	Vec3 vTileMapSize = Vec3(m_FaceX * m_vTileRenderSize.x, m_FaceY * m_vTileRenderSize.y, 1.f);
	Transform()->SetRelativeScale(vTileMapSize);
}

void CTileMap::Render()
{
	// ������ ��Ʋ�� �ؽ��� ����.
	GetMaterial()->SetTexParam(TEX_0, m_TileAtlas);

	// �������� Ÿ�� ����
	UINT iRow = m_TileIdx / m_MaxCol;
	UINT iCol = m_TileIdx % m_MaxCol;

	Vec2 vLeftTopUV = Vec2((iCol * m_vTilePixelSize.x) / m_TileAtlas->GetWidth()
		, (iRow * m_vTilePixelSize.y) / m_TileAtlas->GetHeight());

	Vec2 vSliceSizeUV = Vec2(m_vTilePixelSize.x / m_TileAtlas->GetWidth()
		, m_vTilePixelSize.y / m_TileAtlas->GetHeight());

	GetMaterial()->SetScalarParam(VEC2_0, vLeftTopUV);
	GetMaterial()->SetScalarParam(VEC2_1, vSliceSizeUV);

	GetMaterial()->UpdateData();

	Transform()->UpdateData();

	GetMesh()->Render();
}


void CTileMap::UpdateData()
{

}


void CTileMap::SetTileAtlas(Ptr<CTexture> _Atlas, Vec2 _TilePixelSize)
{
	m_TileAtlas = _Atlas;
	m_vTilePixelSize = _TilePixelSize;

	m_MaxCol = m_TileAtlas->GetWidth() / (UINT)m_vTilePixelSize.x;
	m_MaxRow = m_TileAtlas->GetHeight() / (UINT)m_vTilePixelSize.y;
}