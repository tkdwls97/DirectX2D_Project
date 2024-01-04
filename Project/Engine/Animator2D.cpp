#include "pch.h"
#include "Animator2D.h"

#include "Animation.h"

CAnimator2D::CAnimator2D()
	: CComponent(COMPONENT_TYPE::ANIMATOR2D)
{
}

CAnimator2D::~CAnimator2D()
{
	Delete_Map(m_mapAnim);
}

void CAnimator2D::Finaltick()
{
	m_CurAnim->Finaltick();
}

void CAnimator2D::UpdateData()
{
	m_CurAnim->UpdateData();
}

void CAnimator2D::Clear()
{
	CAnimation::Clear();
}

CAnimation* CAnimator2D::FindAnimation(const wstring& _strAnimName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strAnimName);

	if (iter == m_mapAnim.end())
		return nullptr;

	return iter->second;
}

void CAnimator2D::Create(const wstring& _strKey, Ptr<CTexture> _AltasTex, Vec2 _LeftTop, Vec2 _vSliceSize, Vec2 _OffsetSize, int _FrmCount, float _FPS)
{
	CAnimation* pAnim = FindAnimation(_strKey);
	assert(!pAnim);

	pAnim = new CAnimation;
	pAnim->Create(this, _AltasTex, _LeftTop, _vSliceSize, _OffsetSize, _FrmCount, _FPS);
	m_mapAnim.insert(make_pair(_strKey, pAnim));
}

void CAnimator2D::Play(const wstring& _strAnimName)
{
	CAnimation* pAnim = FindAnimation(_strAnimName);
	if (nullptr == pAnim)
		return;

	m_CurAnim = pAnim;
}
