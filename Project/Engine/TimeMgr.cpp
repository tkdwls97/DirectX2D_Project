#include "pch.h"
#include "TimeMgr.h"

#include "Engine.h"

CTimeMgr::CTimeMgr()
	: m_Frequency{}
	, m_PrevCount{}
	, m_CurCount{}
	, m_Time(0.f)
{

}

CTimeMgr::~CTimeMgr()
{
}

void CTimeMgr::Init()
{
	// �ʴ� ��
	QueryPerformanceFrequency(&m_Frequency);

	QueryPerformanceCounter(&m_PrevCount);
}

void CTimeMgr::Tick()
{
	QueryPerformanceCounter(&m_CurCount);

	m_DeltaTime = double(m_CurCount.QuadPart - m_PrevCount.QuadPart) / double(m_Frequency.QuadPart);

	m_PrevCount = m_CurCount;

	// DT ����
	if ((1.f / 60.f) < m_DeltaTime)
		m_DeltaTime = (1. / 60.);


	// �ð� ���� ==> 1�ʸ��� if ���� ����
	m_Time += m_DeltaTime;
	if (1.f <= m_Time)
	{
		wchar_t szText[50] = {};
		swprintf_s(szText, 50, L"DeltaTime : %f, FPS : %d", m_DeltaTime, m_iCall);
		SetWindowText(CEngine::GetInst()->GetMainWind(), szText);

		m_iCall = 0;
		m_Time = 0.f;
	}

	++m_iCall;

	g_global.g_dt = (float)m_DeltaTime;
	g_global.g_time += (float)m_DeltaTime;
}