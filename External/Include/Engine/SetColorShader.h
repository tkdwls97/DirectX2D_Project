#pragma once
#include "ComputeShader.h"


class CSetColorShader : public CComputeShader
{

public:
    CSetColorShader();
    ~CSetColorShader();

public:
    virtual void UpdateData() override;
    virtual void Clear() override;

public:
    void SetTargetTexture(Ptr<CTexture> _tex) { m_TargetTex = _tex; }
    void SetColor(Vec3 _Color) { m_Color = _Color; }

private:
    Ptr<CTexture>   m_TargetTex;
    Vec4            m_Color;

};

