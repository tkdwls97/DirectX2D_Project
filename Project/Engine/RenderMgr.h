#pragma once
#include "Singleton.h"

class CGameObject;
class CCamera;
class CLight2D;
class CStructuredBuffer;

class CRenderMgr : public CSingleton<CRenderMgr>
{
	SINGLE(CRenderMgr);

public:
	void Init();
	void Tick();

public:
	bool IsDebugPosition() { return m_DebugPosition; }
	void SetDebugPosition(bool _OnOff) { m_DebugPosition = _OnOff; }

public:
	void RegisterCamera(CCamera* _Cam, int _Idx);
	void AddDebugShapeInfo(const tDebugShapeInfo& _Info) { m_DebugShapeInfo.push_back(_Info); }
	void RegisterLight2D(CLight2D* _Light2D) { m_vecLight2D.push_back(_Light2D); }

private:
	void Render();
	void Render_Debug();

	// ���ҽ� ���ε�
	void UpdateData();

	// ���ҽ� Ŭ����
	void Clear();

private:
	vector<CCamera*>        m_vecCam;		// ī�޶� ������ vector (0�� Index -> main Camera)
	list<tDebugShapeInfo>   m_DebugShapeInfo;
	CGameObject*			m_pDebugObj;
	CStructuredBuffer*		m_Light2DBuffer;
	vector<CLight2D*>       m_vecLight2D;

	bool                    m_DebugPosition;
};

