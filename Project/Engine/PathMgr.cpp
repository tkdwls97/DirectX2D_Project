#include "pch.h"
#include "PathMgr.h"

wchar_t CPathMgr::g_szContent[255] = {};


void CPathMgr::Init()
{
	// 실행파일 경로
	::GetCurrentDirectory(255, g_szContent);

	size_t Len = wcslen(g_szContent);

	for (size_t i = Len - 1; i >= 0; --i)
	{
		if ('\\' == g_szContent[i])
		{
			g_szContent[i + 1] = '\0';
			break;
		}
	}

	wcscat_s(g_szContent, 255, L"content\\");
}

const wchar_t* CPathMgr::GetContentPath()
{
	return g_szContent;
}
