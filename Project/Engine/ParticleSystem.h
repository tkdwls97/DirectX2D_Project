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
    tParticleModule         m_Module;
    CStructuredBuffer*      m_ParticleModuleBuffer;
    CStructuredBuffer*      m_SpawnCountBuffer;
    Ptr<CParticleUpdate>    m_CSParticleUpdate;
    Ptr<CTexture>           m_ParticleTex;

    float                   m_Time;
};

