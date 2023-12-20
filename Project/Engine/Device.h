#pragma once

class CConstBuffer;

// Direct11 기준 GPU 제어
class CDevice : public CSingleton<CDevice>
{
	SINGLE(CDevice);

private:
	int CreateSwapChain();
	int CreateTargetView();

	int CreateRasterizerState();
	int CreateDepthStencilState();
	int CreateBlendState();

	int CreateConstBuffer();

public:
	int Init(HWND _hWnd, Vec2 _vResolution);
	void ClearRenderTarget(float(&Color)[4]);
	void Present();

	ID3D11Device* GetDevice() { return m_Device.Get(); }
	ID3D11DeviceContext* GetContext() { return m_Context.Get(); }
	CConstBuffer* GetConstBuffer(CB_TYPE _type) { return m_arrCB[(UINT)_type]; }
	Vec2 GetRenderResolution() { return m_vRenderResolution; }

	ComPtr<ID3D11RasterizerState> GetRSState(RS_TYPE _Type) { return m_arrRS[(UINT)_Type]; }
	ComPtr<ID3D11DepthStencilState> GetDSState(DS_TYPE _Type) { return m_arrDS[(UINT)_Type]; }
	ComPtr<ID3D11BlendState> GetBSState(BS_TYPE _Type) { return m_arrBS[(UINT)_Type]; }


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

	ComPtr<ID3D11RasterizerState>	m_arrRS[(UINT)RS_TYPE::END];	// 레스터라이저 타입설정 배열
	ComPtr<ID3D11DepthStencilState>	m_arrDS[(UINT)DS_TYPE::END];	// 뎁스스텐실 타입설정 배열
	ComPtr<ID3D11BlendState>		m_arrBS[(UINT)BS_TYPE::END];	// 블렌드스테이드 타입 설정 배열
};

