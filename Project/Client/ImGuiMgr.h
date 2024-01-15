#pragma once
#include <Engine/Singleton.h>


class CImGuiMgr : public CSingleton<CImGuiMgr>
{
	SINGLE(CImGuiMgr);
public:
	void Init(HWND _hMainWnd, ComPtr<ID3D11Device> _Device, ComPtr <ID3D11DeviceContext> _Context);
	void Progress();

private:
	void Tick();
	void Render();

};

