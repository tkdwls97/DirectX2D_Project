#pragma once
#include "Component.h"


class CLight2D : public CComponent
{
public:
	CLight2D();
	~CLight2D();

public:
	virtual void Finaltick() override;

public:
    const tLightInfo& GetLightInfo() { return m_Info; }

    void SetLightColor(Vec3 _vColor) { m_Info.vColor = _vColor; }
    void SetSpecular(Vec3 _vSpec) { m_Info.vSpecular = _vSpec; }
    void SetAmbient(Vec3 _vAmb) { m_Info.vAmbient = _vAmb; }

    Vec4 GetLightColor(Vec3 _vColor) { return m_Info.vColor; }
    Vec4 GetSpecular(Vec3 _vSpec) { return m_Info.vSpecular; }
    Vec4 GetAmbient(Vec3 _vAmb) { return m_Info.vAmbient; }

    void SetLightType(LIGHT_TYPE _type);
    void SetRadius(float _Radius);
    void SetAngle(float _Angle);

    LIGHT_TYPE GetLightType() { return (LIGHT_TYPE)m_Info.LightType; }
    float GetRadius() { return m_Info.fRadius; }
    float GetAngle() { return m_Info.fAngle; }

private:
	tLightInfo      m_Info;


};

