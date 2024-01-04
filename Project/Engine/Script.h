#pragma once
#include "Component.h"

#include "TimeMgr.h"
#include "KeyMgr.h"
//#include "ResMgr.h"

#include "GameObject.h"
#include "Components.h"

class CScript :
    public CComponent
{
public:
    CScript();
    ~CScript();

public:
    void Destroy();

    virtual void Finaltick() final {}

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

private:
    UINT        m_ScriptType;
};

