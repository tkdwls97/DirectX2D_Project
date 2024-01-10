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
	if (nullptr == m_CurAnim)
		return;

	if (m_CurAnim->IsFinish() && m_bRepeat)
	{
		m_CurAnim->Reset();
	}

	m_CurAnim->Finaltick();
}

void CAnimator2D::UpdateData()
{
	if (nullptr == m_CurAnim)
		return;

	m_CurAnim->UpdateData();
}

void CAnimator2D::Clear()
{
	CAnimation::Clear();
}

void CAnimator2D::Create(const wstring& _strKey, Ptr<CTexture> _AltasTex, Vec2 _LeftTop
	, Vec2 _vSliceSize, Vec2 _OffsetSize, Vec2 _Background, int _FrmCount, float _FPS)
{
	CAnimation* pAnim = FindAnimation(_strKey);
	assert(!pAnim);

	pAnim = new CAnimation;
	pAnim->Create(this, _AltasTex, _LeftTop, _vSliceSize, _OffsetSize, _Background, _FrmCount, _FPS);
	m_mapAnim.insert(make_pair(_strKey, pAnim));
}

CAnimation* CAnimator2D::FindAnimation(const wstring& _strKey)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strKey);

	if (iter == m_mapAnim.end())
		return nullptr;

	return iter->second;
}

void CAnimator2D::Play(const wstring& _strAnimName, bool _bRepeat)
{
	CAnimation* pAnim = FindAnimation(_strAnimName);
	if (nullptr == pAnim)
		return;

	m_bRepeat = _bRepeat;

	m_CurAnim = pAnim;
	m_CurAnim->Reset();
}
