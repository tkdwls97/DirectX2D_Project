#pragma once
#include <Engine/Singleton.h>
#include "UI.h"

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


};

