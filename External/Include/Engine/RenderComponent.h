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
    CMesh* GetMesh() { return m_Mesh; }
    CMaterial* GetMaterial() { return m_Material; }

    void SetMesh(CMesh* _Mesh) { m_Mesh = _Mesh; }
    void SetMaterial(CMaterial* _Material) { m_Material = _Material; }

private:
    CMesh*      m_Mesh;
    CMaterial*  m_Material;
};

