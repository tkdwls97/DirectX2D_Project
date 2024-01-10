#pragma once
#include "Script.h"

class CPlayerScript : public CScript
{
public:
    CPlayerScript();
    ~CPlayerScript();

public:
    virtual void Begin() override;
    virtual void Tick() override;


public:
    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
private:
    float       m_Speed;

};

