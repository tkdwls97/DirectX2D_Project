#pragma once
#include "RenderComponent.h"

class CTileMap : public CRenderComponent
{
public:
	CTileMap();
	~CTileMap();


public:
    virtual void Finaltick() override;
    virtual void UpdateData() override;
    virtual void Render() override;

public:
    void SetTileAtlas(Ptr<CTexture> _Atlas, Vec2 _TilePixelSize);
    Ptr<CTexture> GetTileAtlas() { return m_TileAtlas; }

private:
    UINT            m_FaceX;            // ���� Ÿ�� ����
    UINT            m_FaceY;            // ���� Ÿ�� ����
    Vec2            m_vTileRenderSize;  // Ÿ�� 1ĭ ������

    Vec3            m_vTileMapWorldPos;

    Ptr<CTexture>   m_TileAtlas;
    Vec2            m_vTilePixelSize;

    UINT            m_MaxCol;
    UINT            m_MaxRow;

    UINT            m_TileIdx;
};

