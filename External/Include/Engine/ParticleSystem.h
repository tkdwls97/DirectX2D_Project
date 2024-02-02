#pragma once
#include "RenderComponent.h"

#include "StructuredBuffer.h"

class CParticleSystem :
    public CRenderComponent
{
public:
    CParticleSystem();
    ~CParticleSystem();

public:
    virtual void UpdateData() override;
    virtual void Finaltick() override;
    virtual void Render() override;

private:
    CStructuredBuffer*  m_ParticleBuffer;
    UINT                m_MaxParticleCount;
};

