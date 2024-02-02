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

public:
    void SetData(void* _SysMem, UINT _ElementCount = 0);
    void GetData(void* _Dest, UINT _ElementCount = 0);

    UINT GetElementSize() { return m_ElementSize; }
    UINT GetElementCount() { return m_ElementCount; }


private:
    ComPtr<ID3D11Buffer>                m_SB;
    ComPtr<ID3D11ShaderResourceView>    m_SRV;
    ComPtr<ID3D11UnorderedAccessView>   m_UAV;
    ComPtr<ID3D11Buffer>                m_SB_Read;          // 데이터를 읽기용 버퍼(Get)
    ComPtr<ID3D11Buffer>                m_SB_Write;         // 데이터를 쓰기용 버퍼(Set)

    UINT                                m_ElementSize;
    UINT                                m_ElementCount;

    SB_TYPE                             m_Type;

    bool                                m_bSysMemMove;    // 쓰기용,읽기용 버퍼를 사용할지 Flag

};

