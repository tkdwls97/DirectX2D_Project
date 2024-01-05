#include "pch.h"
#include "Engine.h"

#include "Device.h"

#include "TimeMgr.h"
#include "KeyMgr.h"
#include "PathMgr.h"
#include "AssetMgr.h"
#include "LevelMgr.h"
#include "TaskMgr.h"
#include "GarbageCollector.h"
#include "RenderMgr.h"
#include "CollisionMgr.h"



CEngine::CEngine()
	: m_hMainWnd(nullptr)
	, m_vResolution()
{

}

CEngine::~CEngine()
{

}

int CEngine::Init(HWND _hWnd, Vec2 _vResolution)
{
	m_hMainWnd = _hWnd;
	m_vResolution = _vResolution;

	RECT rt = { 0, 0, (int)m_vResolution.x, (int)m_vResolution.y };
	::AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	::SetWindowPos(m_hMainWnd, nullptr, 10, 10, rt.right - rt.left, rt.bottom - rt.top, 0);

	if (FAILED(CDevice::GetInst()->Init(m_hMainWnd, m_vResolution)))
	{
		MessageBox(nullptr, L"Device 초기화 실패", L"초기화 실패", MB_OK);
		return E_FAIL;
	}

	// Manager 초기화
	CPathMgr::Init();
	CTimeMgr::GetInst()->Init();
	CKeyMgr::GetInst()->Init();
	CAssetMgr::GetInst()->Init();
	CRenderMgr::GetInst()->Init();
	CLevelMgr::GetInst()->Init();

	return S_OK;
}

void CEngine::Progress()
{
	// Manager Update
	CTimeMgr::GetInst()->Tick();
	CKeyMgr::GetInst()->Tick();

	// Level Update
	CLevelMgr::GetInst()->Tick();
	CCollisionMgr::GetInst()->Tick();
	CRenderMgr::GetInst()->Tick();

	// GarbageCollector
	CGarbageCollector::GetInst()->Tick();

	// Task
	CTaskMgr::GetInst()->Tick();

	DebugFunctionCheck();
}

void CEngine::DebugFunctionCheck()
{
	if (KEY_TAP(KEY::O))
	{
		CRenderMgr::GetInst()->IsDebugPosition() ? CRenderMgr::GetInst()->SetDebugPosition(false) : CRenderMgr::GetInst()->SetDebugPosition(true);
	}
}
