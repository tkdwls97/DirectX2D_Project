#include "pch.h"
#include "Animation.h"

#include "TimeMgr.h"

#include "Device.h"
#include "ConstBuffer.h"


CAnimation::CAnimation()
	: m_Animator(nullptr)
	, m_CurFrmIdx(0)
	, m_bFinish(false)
	, m_AccTime(0.f)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::Finaltick()
{
	m_AccTime += DT;

	if (m_vecFrm[m_CurFrmIdx].fDuration < m_AccTime)
	{
		++m_CurFrmIdx;
		if (m_vecFrm.size() <= m_CurFrmIdx)
		{
			m_CurFrmIdx = 0;
		}
		m_AccTime = 0.f;
	}
}

void CAnimation::UpdateData()
{
	// 현재 프레임 정보를 상수버퍼로 옮기고 b2 레지스터로 바인딩
	static CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::ANIM2D_DATA);
	tAnimData2D data = {};
	data.UseAnim2D = 1;
	data.vLeftTop = m_vecFrm[m_CurFrmIdx].vLeftTop;
	data.vOffset = m_vecFrm[m_CurFrmIdx].vOffset;
	data.vSlizeSize = m_vecFrm[m_CurFrmIdx].vSlice;
	data.vBackGround = m_vecFrm[m_CurFrmIdx].vBackground;

	pCB->SetData(&data);
	pCB->UpdateData();

	// 아틀라스 텍스쳐 t10 에 바인딩
	m_AtlasTex->UpdateData(10);
}

void CAnimation::Clear()
{
	static CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::ANIM2D_DATA);
	tAnimData2D data = {};
	data.UseAnim2D = 0;

	pCB->SetData(&data);
	pCB->UpdateData();
}

void CAnimation::Create(CAnimator2D* _Animator, Ptr<CTexture> _Atlas, Vec2 _vLeftTop, Vec2 _vSliceSize, Vec2 _vOffset, Vec2	_vBackground, int _FrmCount, float _FPS)
{
	m_Animator = _Animator;
	m_AtlasTex = _Atlas;

	for (int i = 0; i < _FrmCount; ++i)
	{
		tAnimFrm frm = {};

		frm.vSlice = Vec2(_vSliceSize.x / (float)_Atlas->GetWidth(), _vSliceSize.y / (float)_Atlas->GetHeight());

		frm.vLeftTop = Vec2(_vLeftTop.x / (float)_Atlas->GetWidth() + frm.vSlice.x * i, _vLeftTop.y / (float)_Atlas->GetHeight());

		frm.vOffset = Vec2(_vOffset.x / (float)_Atlas->GetWidth(), _vOffset.y / (float)_Atlas->GetHeight());
		frm.fDuration = 1.f / _FPS;
		frm.vBackground = Vec2(_vBackground.x / (float)_Atlas->GetWidth(), _vBackground.y / (float)_Atlas->GetHeight());

		m_vecFrm.push_back(frm);
	}

	m_vecFrm[1].vOffset.x = 5.0f / (float)_Atlas->GetWidth();

}
