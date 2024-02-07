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


private:
    CStructuredBuffer* m_ParticleBuffer;
};

