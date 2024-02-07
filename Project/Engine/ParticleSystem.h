#pragma once
#include "RenderComponent.h"

#include "StructuredBuffer.h"
#include "ParticleUpdate.h"

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
    CStructuredBuffer*      m_ParticleBuffer;
    UINT                    m_MaxParticleCount;
    Ptr<CParticleUpdate>    m_CSParticleUpdate;
};

