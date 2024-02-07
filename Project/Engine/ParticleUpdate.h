#pragma once
#include "ComputeShader.h"


class CParticleUpdate : public CComputeShader
{
public:
    CParticleUpdate();
    ~CParticleUpdate();

public:
    virtual int UpdateData() override;
    virtual void UpdateGroupCount() override;
    virtual void Clear() override;

public:
    void SetParticleBuffer(CStructuredBuffer* _ParticleBuffer) { m_ParticleBuffer = _ParticleBuffer; }
    void SetParticleModuleBuffer(CStructuredBuffer* _Buffer) { m_ParticleModuleBuffer = _Buffer; }
    void SetParticleSpawnCount(CStructuredBuffer* _Buffer) { m_SpawnCountBuffer = _Buffer; }



private:
    CStructuredBuffer* m_ParticleBuffer;
    CStructuredBuffer* m_ParticleModuleBuffer;
    CStructuredBuffer* m_SpawnCountBuffer;

};

