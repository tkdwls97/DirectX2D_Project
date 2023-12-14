#pragma once
#include "Component.h"

class CMesh;
class CGraphicsShader;


class CRenderComponent : public CComponent
{
public:
    CRenderComponent(COMPONENT_TYPE _Type);
    ~CRenderComponent();

public:
    virtual void finaltick() {};
    virtual void UpdateData() = 0;
    virtual void render() = 0;

public:
    CMesh* GetMesh() { return m_Mesh; }
    CGraphicsShader* GetShader() { return m_Shader; }

    void SetMesh(CMesh* _Mesh) { m_Mesh = _Mesh; }
    void SetShader(CGraphicsShader* _Shader) { m_Shader = _Shader; }

private:
    CMesh* m_Mesh;
    CGraphicsShader* m_Shader;
};

