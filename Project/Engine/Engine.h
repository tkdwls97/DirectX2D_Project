#pragma once


class CEngine : public CSingleton<CEngine>
{
	SINGLE(CEngine); // �̱��� ��ũ��

public:
	int Init(HWND _hwnd, Vec2 _vResolution);
	void Progress();

public:
	HWND GetMainWind() { return m_hMainWnd; }

private:
	void DebugFunctionCheck();

private:
	HWND	m_hMainWnd;		// ���� ������ �ڵ�
	Vec2	m_vResolution;	// �ػ� ����

};

