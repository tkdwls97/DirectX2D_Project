#pragma once
#include "Script.h"

class CBackgroundScript :public CScript
{
public:
    CBackgroundScript();
    ~CBackgroundScript();


public:
    virtual void Tick() override;


};

