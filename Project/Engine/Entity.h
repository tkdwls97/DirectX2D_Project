#pragma once


class CEntity
{
public:
	CEntity();
	~CEntity();


public:
	void SetName(const wstring& _strName);
	const wstring& GetName();
	UINT GetID();


private:
	static UINT	g_NextID;

	const UINT	m_ID;
	wstring		m_strName;

};

