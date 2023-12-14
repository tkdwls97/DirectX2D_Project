#pragma once
#include "Shader.h"

class CGraphicsShader :	public CShader
{
public:
    CGraphicsShader();
    ~CGraphicsShader();

public:
    virtual void UpdateData();
    

public:
    int CreateVertexShader(const wstring& _strRelativePath, const string& _strFuncName);
    int CreateHullShader();
    int CreateDomainShader();
    int CreateGeometryShader();
    int CreatePixelShader(const wstring& _strRelativePath, const string& _strFuncName);

    void SetTopology(D3D11_PRIMITIVE_TOPOLOGY _Topology) { m_Topology = _Topology; }

private:
    ComPtr<ID3DBlob>    m_VSBlob;
    ComPtr<ID3DBlob>    m_HSBlob;
    ComPtr<ID3DBlob>    m_DSBlob;
    ComPtr<ID3DBlob>    m_GSBlob;
    ComPtr<ID3DBlob>    m_PSBlob;

    ComPtr<ID3D11VertexShader>      m_VS;
    ComPtr<ID3D11HullShader>        m_HS;
    ComPtr<ID3D11DomainShader>      m_DS;
    ComPtr<ID3D11GeometryShader>    m_GS;
    ComPtr<ID3D11PixelShader>       m_PS;

    ComPtr<ID3D11InputLayout>       m_Layout;

    D3D11_PRIMITIVE_TOPOLOGY        m_Topology;

    // Rasterizer State

    // OutputMerge
    // DepthStencilState
    // BlendState
};

