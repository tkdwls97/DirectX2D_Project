#include "pch.h"
#include "Engine.h"
#include "Device.h"
#include "Test.h"

CEngine::CEngine()
	: m_hMainWnd(nullptr)
	, m_vResolution()
{


}

CEngine::~CEngine()
{
	
}

int CEngine::Init(HWND _hwnd, Vec2 _vResolution)
{
	m_hMainWnd = _hwnd;
	m_vResolution = _vResolution;

	RECT rt = { 0, 0, (int)m_vResolution.x, (int)m_vResolution.y };
	::AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	::SetWindowPos(m_hMainWnd, nullptr, (int)10.f, (int)10.f, rt.right - rt.left, rt.bottom - rt.top, 0);

	if (FAILED(CDevice::GetInst()->Init(m_hMainWnd, m_vResolution)))
	{
		MessageBox(nullptr, L"Device 초기화 실패", L"초기화 실패", MB_OK);
		return E_FAIL;
	}

	if (FAILED(TestInit()))
	{
		return E_FAIL;
	}

	return S_OK;
}

void CEngine::Progress()
{
	TestProgress();
}
