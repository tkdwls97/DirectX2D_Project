#pragma once
#include "Component.h"



class CCamera : public CComponent
{
public:
    CCamera();
    ~CCamera();

public:
    virtual void Finaltick() override;
    void SortObject();
    void Render();

private:
    void Render(vector<CGameObject*>& _vecObj);

public:
    PROJ_TYPE GetProjType() { return m_ProjType; }
    void SetProjType(PROJ_TYPE _Type) { m_ProjType = _Type; }

    float GetScale() { return m_Scale; }
    void SetScale(float _Scale) { m_Scale = _Scale; }

    float GetFOV() { return m_FOV; }
    void SetFOV(float _FOV) { m_FOV = _FOV; }

    const Matrix& GetViewMat() { return m_matView; }
    const Matrix& GetProjMat() { return m_matProj; }

    void SetCameraPriority(int _Priority);

    void LayerCheck(UINT _LayerIdx, bool _bCheck);
    void LayerCheck(const wstring& _strLayerName, bool _bCheck);
    void LayerCheckAll() { m_LayerCheck = 0xffffffff; }



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
    Matrix      m_matView;
    Matrix      m_matProj;

    // ������ �� LayerCheck
    UINT        m_LayerCheck;

    // ��ü �з�
    vector<CGameObject*>    m_vecOpaque;
    vector<CGameObject*>    m_vecMaked;
    vector<CGameObject*>    m_vecTransparent;
    vector<CGameObject*>    m_vecPostProcess;

};

