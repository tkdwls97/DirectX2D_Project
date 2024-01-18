#pragma once

#include <Engine/Singleton.h>

class UI;
typedef void (*CALL_BACK_0)(void);
typedef void (*CALL_BACK_1)(DWORD_PTR);
typedef void (*CALL_BACK_2)(DWORD_PTR, DWORD_PTR);

class CImGuiMgr : public CSingleton<CImGuiMgr>
{
	SINGLE(CImGuiMgr);

public:
	void Init(HWND _hMainWnd, ComPtr<ID3D11Device> _Device, ComPtr <ID3D11DeviceContext> _Context);
	void Progress();

private:
	void Tick();
	void Render();
	void Create_UI();

public:
	UI* FindUI(const string& _strUIName);
	void AddUI(const string& _strKey, UI* _UI);

private:
	map<string, UI*> m_mapUI;

	bool             m_bDemoUI;

};

