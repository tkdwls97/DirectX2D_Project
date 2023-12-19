#pragma once
#include "Script.h"


class CCameraMoveScript :public CScript
{
public:
    CCameraMoveScript();
    ~CCameraMoveScript();

public:
    virtual void Tick();

private:
    void MoveOrthographic();
    void MovePerspective();



private:
    float       m_CamSpeed;
};

