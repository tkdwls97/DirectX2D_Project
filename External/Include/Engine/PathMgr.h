#pragma once

class CPathMgr
{

public:
	static void Init();
	static const wchar_t* GetContentPath();

private:
	static wchar_t g_szContent[255];
};

