#pragma once

#include "Script.h"

class CSpotLightScript :public CScript
{
public:
	CSpotLightScript();
	~CSpotLightScript();

public:
	virtual void Tick() override;

private:

};


