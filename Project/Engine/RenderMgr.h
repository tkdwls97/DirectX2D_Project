#pragma once
#include "Singleton.h"

class CGameObject;
class CCamera;

class CRenderMgr : public CSingleton<CRenderMgr>
{
	SINGLE(CRenderMgr);

public:
	void Init();
	void Tick();

public:
	void RegisterCamera(CCamera* _Cam, int _Idx);
	void AddDebugShapeInfo(const tDebugShapeInfo& _Info) { m_DebugShapeInfo.push_back(_Info); }

private:
	void Render();
	void Render_Debug();

private:
	vector<CCamera*>        m_vecCam;		// 카메라를 저장할 vector (0번 Index -> main Camera)

	list<tDebugShapeInfo>   m_DebugShapeInfo;

	CGameObject* m_pDebugObj;
};

