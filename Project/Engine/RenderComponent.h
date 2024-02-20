#pragma once
#include "Component.h"

#include "Mesh.h"
#include "Material.h"


class CRenderComponent : public CComponent
{
public:
    CRenderComponent(COMPONENT_TYPE _Type);
    ~CRenderComponent();

public:
    virtual void Finaltick() {};
    virtual void UpdateData() = 0;
    virtual void Render() = 0;

public:
    void SetMesh(Ptr<CMesh> _Mesh) { m_Mesh = _Mesh; }
    void SetMaterial(Ptr<CMaterial> _Mtrl);

    Ptr<CMesh> GetMesh() { return m_Mesh; }
    Ptr<CMaterial> GetMaterial() { return m_CurMtrl; }
    Ptr<CMaterial> GetSharedMaterial() { return m_SharedMtrl; }
    Ptr<CMaterial> GetDynamicMaterial();

    void RestoreMaterial();

private:
    Ptr<CMesh>      m_Mesh;
    Ptr<CMaterial>  m_Material;
    Ptr<CMaterial>  m_SharedMtrl;
    Ptr<CMaterial>  m_DynamicMtrl;
    Ptr<CMaterial>  m_CurMtrl;
};

