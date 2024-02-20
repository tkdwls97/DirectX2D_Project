#pragma once


class CEntity
{
public:
	CEntity();
	virtual ~CEntity();


public:
	void SetName(const wstring& _strName);
	const wstring& GetName();
	UINT GetID();

	virtual CEntity* Clone() { return nullptr; };

private:
	static UINT	g_NextID;

	const UINT	m_ID;
	wstring		m_strName;

};

