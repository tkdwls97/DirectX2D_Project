#pragma once

class CConstBuffer;

// Direct11 ���� GPU ����
class CDevice : public CSingleton<CDevice>
{
	SINGLE(CDevice);

private:
	int CreateSwapChain();
	int CreateTargetView();
	int CreateConstBuffer();

public:
	int Init(HWND _hWnd, Vec2 _vResolution);
	void ClearRenderTarget(float(&Color)[4]);
	void Present();

	ID3D11Device* GetDevice() { return m_Device.Get(); }
	ID3D11DeviceContext* GetContext() { return m_Context.Get(); }
	CConstBuffer* GetConstBuffer(CB_TYPE _type) { return m_arrCB[(UINT)_type]; }
	Vec2 GetRenderResolution() { return m_vRenderResolution; }

private:
	ComPtr<ID3D11Device>			m_Device;		// GPU �޸� ����, ��ü ����, ���� ����
	ComPtr<ID3D11DeviceContext>		m_Context;		// GPU ������ ��� ����

	ComPtr<IDXGISwapChain>			m_SwapChain;	// ����ü�� (��� ���� ����)
	
	// OM(Output Merge State)
	ComPtr<ID3D11Texture2D>			m_RTTex;		// ���� Ÿ�� �ؽ���
	ComPtr<ID3D11RenderTargetView>  m_RTView;		// ���� Ÿ�� �� (���� Ÿ�� �ؽ�ó�� �����ϴ� �뵵)

	ComPtr<ID3D11Texture2D>			m_DSTex;		// �X�� ���ٽ� �ؽ�ó (���� ��)
	ComPtr<ID3D11DepthStencilView>  m_DSView;		// �X�� ���ٽ� View (�X�� ���ٽ� �ؽ�ó�� �����ϴ� �뵵)

	HWND							m_hRenderWnd;
	Vec2							m_vRenderResolution;

	CConstBuffer*					m_arrCB[(UINT)CB_TYPE::END];
};

