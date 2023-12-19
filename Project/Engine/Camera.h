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
    PROJ_TYPE   m_ProjType;     // ���� ���

    // ��������(Perspective)
    float       m_FOV;          // �þ� ��(Filed Of View)

    // ��������(Orthographic)
    float       m_Width;        // �������� ���� ����
    float       m_Scale;        // �������� ����

    // Both
    float       m_AspectRatio;  // ��Ⱦ��, ���� ���μ��� ����
    float       m_Far;          // ���� �ִ� �Ÿ�

    // ��ȯ ���
    Matrix  m_matView;
    Matrix  m_matProj;
};

