#pragma once
#include "Asset.h"


class CTexture : public CAsset
{
public:
	CTexture();
	~CTexture();


public:
    void UpdateData(int _RegisterNum);


private:
    virtual int Load(const wstring& _strFilePath) override;

private:
    ScratchImage                        m_Image;    // �ؽ��� �ε� �� �ý��۸޸� ����
    ComPtr<ID3D11Texture2D>             m_Tex2D;    // �ؽ��� �����͸� GPU �޸𸮿� ����
    D3D11_TEXTURE2D_DESC                m_Desc;     // �ؽ��� ���� ����

    ComPtr<ID3D11RenderTargetView>      m_RTV;      // ����Ÿ�� �뵵
    ComPtr<ID3D11DepthStencilView>      m_DSV;      // �X�� ���ٽ� �뵵
    ComPtr<ID3D11ShaderResourceView>    m_SRV;      // ���̴����� ����ϴ� �뵵(�ؽ��� ��������(t) ���ε�)
    ComPtr<ID3D11UnorderedAccessView>   m_UAV;      // GPGPU(General Purpose GPU) - ComputeShader,
                                                    // �б� ���� ���ð���, (Unordered Register(u) �� ���ε� ����)

};

