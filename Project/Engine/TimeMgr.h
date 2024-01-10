#pragma once

class CTimeMgr
	: public CSingleton<CTimeMgr>
{
	SINGLE(CTimeMgr);

public:
	void Init();
	void Tick();

public:
	float GetDeltaTime() { return (float)m_DeltaTime; }
	double GetDeltaTime_d() { return m_DeltaTime; }

private:
	// Larget Integer 는 그냥 8바이트 long long 타입 정수로 취급
	LARGE_INTEGER	m_Frequency;
	LARGE_INTEGER	m_PrevCount;
	LARGE_INTEGER	m_CurCount;
	double			m_DeltaTime;


	UINT			m_iCall;
	double			m_Time;

};

