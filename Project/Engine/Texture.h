#pragma once
#include "Asset.h"


class CTexture : public CAsset
{
    friend class CAssetMgr;
public:
	CTexture();
	~CTexture();

public:
    void UpdateData(int _RegisterNum);
    static void Clear(int _RegisterNum);

public:
    UINT GetWidth() { return m_Desc.Width; }
    UINT GetHeight() { return m_Desc.Height; }

    ComPtr<ID3D11RenderTargetView>    GetRTV() { return m_RTV; }
    ComPtr<ID3D11DepthStencilView>    GetDSV() { return m_DSV; }
    ComPtr<ID3D11ShaderResourceView>  GetSRV() { return m_SRV; }
    ComPtr<ID3D11UnorderedAccessView> GetUAV() { return m_UAV; }


private:
    virtual int Load(const wstring& _strFilePath) override;
    int Create(UINT _Width, UINT _Height
        , DXGI_FORMAT _Format, UINT _BindFlag
        , D3D11_USAGE _Usage = D3D11_USAGE_DEFAULT);
  

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

