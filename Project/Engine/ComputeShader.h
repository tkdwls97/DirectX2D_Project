#pragma once
#include "Shader.h"

#include "StructuredBuffer.h"
#include "Texture.h"

class CComputeShader : public CShader
{
public:
    CComputeShader(UINT _ThreadX, UINT _ThreadY, UINT _ThreadZ);
    ~CComputeShader();

private:
    virtual int UpdateData() = 0;
    virtual void Clear() = 0;

public:
    int Create(const wstring& _strRelativePath, const string& _strFuncName);

public:
    void Execute();

protected:
    UINT GetGroupX() { return m_GroupX; }
    UINT GetGroupY() { return m_GroupY; }
    UINT GetGroupZ() { return m_GroupZ; }

    void SetGroupX(UINT _Group) { m_GroupX = _Group; }
    void SetGroupY(UINT _Group) { m_GroupY = _Group; }
    void SetGroupZ(UINT _Group) { m_GroupZ = _Group; }


protected:
    tMtrlConst                  m_Const;

    // ������ ����
    const UINT                  m_ThreadX;
    const UINT                  m_ThreadY;
    const UINT                  m_ThreadZ;

private:
    ComPtr<ID3DBlob>            m_CSBlob;
    ComPtr<ID3D11ComputeShader> m_CS;

    // �׷� ����
    UINT                        m_GroupX;
    UINT                        m_GroupY;
    UINT                        m_GroupZ;


};

