#pragma once
#include "Component.h"

#include "Texture.h"

class CAnimation;


class CAnimator2D : public CComponent
{
public:
    CAnimator2D();
    ~CAnimator2D();

public:
    virtual void Finaltick() override;
    void UpdateData();
    static void Clear();


public:

    CAnimation* FindAnimation(const wstring& _strAnimName);

    // _LeftTop, _SliceSize, _Offset : Pixel Unit
    void Create(const wstring& _strKey, Ptr<CTexture> _AltasTex, Vec2 _LeftTop, Vec2 _vSliceSize, Vec2 _OffsetSize, Vec2 _Background, int _FrmCount, float _FPS);
    void Play(const wstring& _strAnimName);


private:
    map<wstring, CAnimation*>    m_mapAnim;
    CAnimation*                  m_CurAnim;
    bool                         m_bRepeat;
};  

