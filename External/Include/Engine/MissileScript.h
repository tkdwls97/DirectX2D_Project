#pragma once
#include "Script.h"

class CMissileScript : public CScript
{
public:
    CMissileScript();
    ~CMissileScript();


public:
    virtual void Tick() override;

private:
    float   m_fSpeed;


};

