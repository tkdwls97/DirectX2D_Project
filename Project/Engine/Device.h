#pragma once


class CDevice : public CSingleton<CDevice>
{
	SINGLE(CDevice);

public:
	int Init(HWND _hWnd, Vec2 _vResoluti);


private:
	ComPtr<ID3D11Device>			m_Device;		// GPU �޸� ����, ��ü ����
	ComPtr<ID3D11DeviceContext>		m_Context;		// GPU ������ ���

	ComPtr<IDXGISwapChain>			m_SwapChain;	// ����ü�� (��� ���� ����)
	
	// OM(Output Merge State)
	ComPtr<ID3D11Texture2D>			m_RTTex;		// ���� Ÿ�� �ؽ���
	ComPtr<ID3D11RenderTargetView>  m_RTView;		// ���� Ÿ�� �� (���� Ÿ�� �ؽ�ó�� �����ϴ� �뵵)

	ComPtr<ID3D11Texture2D>			m_DsTex;		// �X�� ���ٽ� �ؽ�ó (���� ��)
	ComPtr<ID3D11DepthStencilView>  m_DsView;		// �X�� ���ٽ� View (�X�� ���ٽ� �ؽ�ó�� �����ϴ� �뵵)

	HWND							m_hRenderWnd;
	Vec2							m_vRenderResolution;
};

