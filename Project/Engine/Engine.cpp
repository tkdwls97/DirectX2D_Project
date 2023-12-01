#include "pch.h"
#include "Engine.h"

CEngine::CEngine()
	: m_hMainWnd(nullptr)
	, m_vResolution()
{


}

CEngine::~CEngine()
{


}

void CEngine::Init(HWND _hwnd, Vec2 _vResolution)
{
	m_hMainWnd = _hwnd;
	m_vResolution = _vResolution;

	RECT rt = { 0, 0, (int)m_vResolution.x, (int)m_vResolution.y };
	::AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	::SetWindowPos(m_hMainWnd, nullptr, 10.f, 10.f, rt.right - rt.left, rt.bottom - rt.top, 0);

	
}

void CEngine::Progress()
{
	
}
