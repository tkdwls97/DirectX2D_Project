#pragma once
#include "Component.h"



class CCamera : public CComponent
{
public:
    CCamera();
    ~CCamera();

public:
    virtual void Finaltick() override;

public:
    PROJ_TYPE GetProjType() { return m_ProjType; }
    void SetProjType(PROJ_TYPE _Type) { m_ProjType = _Type; }

    float GetScale() { return m_Scale; }
    void SetScale(float _Scale) { m_Scale = _Scale; }

    float GetFOV() { return m_FOV; }
    void SetFOV(float _FOV) { m_FOV = _FOV; }

private:
    PROJ_TYPE   m_ProjType;     // 투영 방식

    // 원근투영(Perspective)
    float       m_FOV;          // 시야 각(Filed Of View)

    // 직교투영(Orthographic)
    float       m_Width;        // 직교투영 가로 길이
    float       m_Scale;        // 직교투영 배율

    // Both
    float       m_AspectRatio;  // 종횡비, 투영 가로세로 비율
    float       m_Far;          // 투영 최대 거리

    // 변환 행렬
    Matrix  m_matView;
    Matrix  m_matProj;
};

