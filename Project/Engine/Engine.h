#pragma once


class CEngine : public CSingleton<CEngine>
{
	SINGLE(CEngine); // 싱글톤 매크로

public:
	void Init(HWND _hwnd, Vec2 _vResolution);
	void Progress();

private:
	HWND	m_hMainWnd;		// 메인 윈도우 핸들
	Vec2	m_vResolution;	// 해상도 정보

};

