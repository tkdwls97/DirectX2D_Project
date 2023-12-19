#pragma once

struct FKeyData
{
	KEY			eKey;
	KEY_STATE	eState;
	bool		bPressed;
};

class CKeyMgr
	: public CSingleton<CKeyMgr>
{
	SINGLE(CKeyMgr);

public:
	void Init();
	void Tick();

public:
	KEY_STATE GetKeyState(KEY _Key) { return m_vecKeyData[_Key].eState; }
	Vec2 GetMousePos() { return m_vMousePos; }
	Vec2 GetMouseDrag() { return m_vMouseDrag; }

private:
	vector<FKeyData>	m_vecKeyData;

	Vec2				m_vMousePos;
	Vec2				m_vMousePrevPos;

	Vec2				m_vMouseDrag;

};

