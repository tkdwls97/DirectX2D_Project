#pragma once


class CConstBuffer;

// Direct11 기준 GPU 제어
class CDevice : public CSingleton<CDevice>
{
	SINGLE(CDevice);

public:
	int Init(HWND _hWnd, Vec2 _vResolution);
	void ClearRenderTarget(float(&Color)[4]);
	void Present();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetContext();

	CConstBuffer* GetConstBuffer(CB_TYPE _type);

private:
	int CreateSwapChain();
	int CreateTargetView();
	int CreateConstBuffer();

private:
	ComPtr<ID3D11Device>			m_Device;		// GPU 메모리 관리, 객체 생성, 버퍼 생성
	ComPtr<ID3D11DeviceContext>		m_Context;		// GPU 렌더링 명령 제어

	ComPtr<IDXGISwapChain>			m_SwapChain;	// 스왑체인 (출력 버퍼 지정)
	
	// OM(Output Merge State)
	ComPtr<ID3D11Texture2D>			m_RTTex;		// 렌더 타겟 텍스쳐
	ComPtr<ID3D11RenderTargetView>  m_RTView;		// 렌더 타겟 뷰 (렌더 타겟 텍스처를 전달하는 용도)

	ComPtr<ID3D11Texture2D>			m_DSTex;		// 뎊스 스텐실 텍스처 (깊이 값)
	ComPtr<ID3D11DepthStencilView>  m_DSView;		// 뎊스 스텐실 View (뎊스 스텐실 텍스처를 전달하는 용도)

	HWND							m_hRenderWnd;
	Vec2							m_vRenderResolution;

	CConstBuffer*					m_arrCB[(UINT)CB_TYPE::END];
};

