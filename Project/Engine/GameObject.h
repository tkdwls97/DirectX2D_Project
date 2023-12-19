#pragma once
#include "Entity.h"


class CComponent;
class CRenderComponent;
class CScript;
class CCamera;

class CGameObject : public CEntity
{
public:
    CGameObject();
    ~CGameObject();

public:
    void Begin();
    void Tick();
    void Finaltick();
    void Render();

public:
    void AddComponent(CComponent* _Comonent);
    CComponent* GetComponent(COMPONENT_TYPE _Type) { return m_arrCom[(UINT)_Type]; }

    GET_COMPONENT(Transform, TRANSFORM);
    GET_COMPONENT(MeshRender, MESHRENDER);
    GET_COMPONENT(Camera, CAMERA);

private:
    CComponent* m_arrCom[(UINT)COMPONENT_TYPE::END];
    CRenderComponent* m_RenderCom;

    vector<CScript*>    m_vecScript;

};

