#pragma once
#include "RenderComponent.h"

class CStructuredBuffer;

struct tTileInfo
{
    Vec2 vLeftTopUV;
    int  bRender;
    int  padding;
};

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
    UINT GetFaceX() { return m_FaceX; }
    UINT GetFaceY() { return m_FaceY; }

    void SetFace(UINT _FaceX, UINT _FaceY);
    void SetTileIndex(UINT _Row, UINT _Col, UINT _ImgIdx);


private:
    UINT                m_FaceX;            // ���� Ÿ�� ����
    UINT                m_FaceY;            // ���� Ÿ�� ����
    Vec2                m_vTileRenderSize;  // Ÿ�� 1ĭ ������


    Vec3                m_vTileMapWorldPos;

    Ptr<CTexture>       m_TileAtlas;
    Vec2                m_vTilePixelSize;
    Vec2                m_vSliceSizeUV;

    UINT                m_MaxCol;
    UINT                m_MaxRow;

    UINT                m_TileIdx;

    vector<tTileInfo>   m_vecTileInfo;
    CStructuredBuffer*  m_TileInfoBuffer;
};

