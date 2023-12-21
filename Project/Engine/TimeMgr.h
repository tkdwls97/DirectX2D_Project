#pragma once

class CTimeMgr
	: public CSingleton<CTimeMgr>
{
	SINGLE(CTimeMgr);

public:
	void Init();
	void Tick();

public:
	float GetDeltaTime();

private:
	// Larget Integer �� �׳� 8����Ʈ long long Ÿ�� ������ ���
	LARGE_INTEGER	m_Frequency;
	LARGE_INTEGER	m_PrevCount;
	LARGE_INTEGER	m_CurCount;
	float			m_DeltaTime;


	UINT			m_iCall;
	float			m_fTime;
};

