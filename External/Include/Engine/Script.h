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

private:
    UINT        m_ScriptType;
};

