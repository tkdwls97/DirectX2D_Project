#pragma once
#include "Entity.h"

class CConstBuffer : public CEntity
{
public:
    CConstBuffer();
    ~CConstBuffer();

public:
    int Create(UINT _ElementSize, UINT _ElementCount);
    void SetData(void* _Src, UINT _ElementCount = 0);
    void UpdateData(UINT _RegisterNum);

private:
    D3D11_BUFFER_DESC       m_Desc;
    ComPtr<ID3D11Buffer>    m_CB;

    UINT                    m_ElementSize;
    UINT                    m_ElementCount;


};

