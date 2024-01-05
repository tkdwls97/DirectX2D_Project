#pragma once
#include "Entity.h"

#include "Texture.h"


class CAnimator2D;



struct tAnimFrm
{
	Vec2    vLeftTop;
	Vec2    vSlice;
	Vec2    vOffset;
	Vec2    vBackground;
	float   fDuration;
};


class CAnimation : public CEntity
{
public:
	CAnimation();
	~CAnimation();

public:
	void Finaltick();
	void UpdateData();
	static void Clear();

public:
	void Create(CAnimator2D* _Animator, Ptr<CTexture> _Atlas, Vec2 _vLeftTop, Vec2 _vSliceSize, Vec2 _vOffset, Vec2 _vBackground, int _FrmCount, float _FPS);



private:
	CAnimator2D* m_Animator;

	vector<tAnimFrm>    m_vecFrm;
	int                 m_CurFrmIdx;
	bool                m_bFinish;
	float               m_AccTime;

	Ptr<CTexture>       m_AtlasTex;


};

