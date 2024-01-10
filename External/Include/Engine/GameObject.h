#pragma once
#include "Entity.h"


class CComponent;
class CRenderComponent;
class CScript;
class CCamera;
class CCollider2D;
class CAnimator2D;
class CLight2D;

class CGameObject : public CEntity
{
    friend class CLayer;
    friend class CTaskMgr;

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
    void DisconnectWithParent();
    void DisconnectWithLayer();

    void AddChild(CGameObject* _Child);
    bool IsDead() { return m_bDead; }
    void Destroy();

public:
    CComponent* GetComponent(COMPONENT_TYPE _Type) { return m_arrCom[(UINT)_Type]; }
    CGameObject* GetParent() { return m_Parent; }

    const vector<CScript*>& GetScripts() { return m_vecScript; }

    template<typename T>
    T* GetScript()
    {
        for (size_t i = 0; i < m_vecScript.size(); ++i)
        {
            if (dynamic_cast<T*>(m_vecScript[i]))
                return (T*)m_vecScript[i];
        }
        return nullptr;
    }

    GET_COMPONENT(Transform, TRANSFORM);
    GET_COMPONENT(MeshRender, MESHRENDER);
    GET_COMPONENT(Camera, CAMERA);
    GET_COMPONENT(Collider2D, COLLIDER2D);
    GET_COMPONENT(Animator2D, ANIMATOR2D);
    GET_COMPONENT(Light2D, LIGHT2D);


private:
    CComponent*             m_arrCom[(UINT)COMPONENT_TYPE::END];
    CRenderComponent*       m_RenderCom;

    vector<CScript*>        m_vecScript;
    vector<CGameObject*>    m_vecChild;

    CGameObject*            m_Parent;

    int                     m_LayerIdx;    // 오브젝트가 소속되어있는 Layer 의 Index
    bool                    m_bDead;
};

