#pragma once
#include "Entity.h"

enum class SB_TYPE
{
    READ_ONLY,
    READ_WRITE,
};



class CStructuredBuffer : public CEntity
{
public:
	CStructuredBuffer();
	~CStructuredBuffer();


public:
    int Create(UINT _ElementSize, UINT _ElementCount, SB_TYPE _Type, bool _bSysMemMove = false, void* _pSysMem = nullptr);
	void UpdateData(UINT _RegisterNum);
    int UpdateData_CS_SRV(UINT _RegisterNum);
    int UpdateData_CS_UAV(UINT _RegisterNum);

    void Clear(UINT _RegisterNum);
    void Clear_CS_SRV();
    void Clear_CS_UAV();

public:
    void SetData(void* _SysMem, UINT _ElementCount = 0);
    void GetData(void* _Dest, UINT _ElementCount = 0);

    UINT GetElementSize() { return m_ElementSize; }
    UINT GetElementCount() { return m_ElementCount; }


private:
    ComPtr<ID3D11Buffer>                m_SB;
    ComPtr<ID3D11ShaderResourceView>    m_SRV;
    ComPtr<ID3D11UnorderedAccessView>   m_UAV;
    ComPtr<ID3D11Buffer>                m_SB_Read;          // �����͸� �б�� ����(Get)
    ComPtr<ID3D11Buffer>                m_SB_Write;         // �����͸� ����� ����(Set)

    UINT                                m_ElementSize;
    UINT                                m_ElementCount;

    UINT                                m_RegentSRV;    // �ֱٿ� ���ε��� t�������� ��ȣ
    UINT                                m_RegentUAV;    // �ֱٿ� ���ε��� u�������� ��ȣ

    SB_TYPE                             m_Type;

    bool                                m_bSysMemMove;    // �����,�б�� ���۸� ������� Flag
};

