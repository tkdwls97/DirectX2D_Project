#include "pch.h"
#include "Device.h"

#include "ConstBuffer.h"

CDevice::CDevice()
	: m_hRenderWnd(nullptr)
	, m_arrCB{}
{

}

CDevice::~CDevice()
{
	Delete_Array(m_arrCB);
}

int CDevice::Init(HWND _hWnd, Vec2 _vResolution)
{
	// 출력 윈도우 
	m_hRenderWnd = _hWnd;

	// 버퍼 해상도
	m_vRenderResolution = _vResolution;

	// 장치 초기화
	D3D_FEATURE_LEVEL eLevel = D3D_FEATURE_LEVEL_11_0;

	if (FAILED(D3D11CreateDevice(nullptr
		, D3D_DRIVER_TYPE_HARDWARE, nullptr
		, D3D11_CREATE_DEVICE_DEBUG
		, nullptr, 0, D3D11_SDK_VERSION
		, m_Device.GetAddressOf(), &eLevel, m_Context.GetAddressOf())))
	{
		MessageBox(nullptr, L"Device, Context 생성 실패", L"Device 초기화 실패", MB_OK);
		return E_FAIL;
	}

	// 스왑체인 생성
	if (FAILED(CreateSwapChain()))
	{
		MessageBox(nullptr, L"SwapChain 생성 실패", L"Device 초기화 실패", MB_OK);
		return E_FAIL;
	}

	// 렌더타겟, 렌더타겟 뷰, 뎁스 스텐실 타겟, 뎁스 스텐실 뷰 생성
	if (FAILED(CreateTargetView()))
	{
		MessageBox(nullptr, L"타겟 및 View 생성 실패", L"Device 초기화 실패", MB_OK);
		return E_FAIL;
	}

	// ViewPort 설정
	D3D11_VIEWPORT ViewportDesc = {};

	ViewportDesc.MinDepth = 0;
	ViewportDesc.MaxDepth = 1.f;

	ViewportDesc.TopLeftX = 0;
	ViewportDesc.TopLeftX = 0;
	ViewportDesc.Width = m_vRenderResolution.x;
	ViewportDesc.Height = m_vRenderResolution.y;

	CONTEXT->RSSetViewports(1, &ViewportDesc);

	if (FAILED(CreateConstBuffer()))
	{
		MessageBox(nullptr, L"상수버퍼 생성 실패", L"Device 초기화 실패", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

void CDevice::ClearRenderTarget(float(&Color)[4])
{
	m_Context->ClearRenderTargetView(m_RTView.Get(), Color);
	m_Context->ClearDepthStencilView(m_DSView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
}

void CDevice::Present()
{
	m_SwapChain->Present(0, 0);
}

ID3D11Device* CDevice::GetDevice()
{
	return m_Device.Get();
}

ID3D11DeviceContext* CDevice::GetContext()
{
	return m_Context.Get();
}

CConstBuffer* CDevice::GetConstBuffer(CB_TYPE _type)
{
	return m_arrCB[(UINT)_type];
}

int CDevice::CreateSwapChain()
{
	// SwapChain 생성 구조체
	DXGI_SWAP_CHAIN_DESC tDesc = {};

	// SWapChain이 관리하는 Buffer(RenderTarget) 의 구성 정보
	tDesc.BufferCount = 1;
	tDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	tDesc.BufferDesc.Width = (UINT)m_vRenderResolution.x;
	tDesc.BufferDesc.Height = (UINT)m_vRenderResolution.y;
	tDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	tDesc.BufferDesc.RefreshRate.Denominator = 1;
	tDesc.BufferDesc.RefreshRate.Numerator = 60;
	tDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	tDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	tDesc.Flags = 0;

	tDesc.SampleDesc.Count = 1;
	tDesc.SampleDesc.Quality = 0;

	tDesc.Windowed = true; // 창모드
	tDesc.OutputWindow = m_hRenderWnd; // SwapChain의 출력 윈도우 지정

	// 스왑체인 생성기능을 가진 Factory에 접근한다
	ComPtr<IDXGIDevice>		pIdxgiDevice = nullptr;
	ComPtr<IDXGIAdapter>	pAdapter = nullptr;
	ComPtr<IDXGIFactory>	pFactory = nullptr;

	m_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)pIdxgiDevice.GetAddressOf());
	pIdxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pAdapter.GetAddressOf());
	pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)pFactory.GetAddressOf());

	// SwapChain 생성
	if (FAILED(pFactory->CreateSwapChain(m_Device.Get(), &tDesc, m_SwapChain.GetAddressOf())))
	{
		return E_FAIL;
	}
	return S_OK;
}

int CDevice::CreateTargetView()
{
	/*
	ID3D11Resource; 부모

	- ID3D11Buffer; 자식
	- ID3D11Texture2D; 자식
	*/

	// 렌더타겟 텍스쳐를 스왑체인으로부터 얻어온다.
	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)m_RTTex.GetAddressOf());

	// 렌더 타겟 뷰
	m_Device->CreateRenderTargetView(m_RTTex.Get(), nullptr, m_RTView.GetAddressOf());

	// View ?
	// RenderTargetView
	// DepthStencilView
	// ShaderResourceView
	// UnorderedAccessView

	// DepthStencilTexture 생성
	D3D11_TEXTURE2D_DESC Desc = {};

	// 픽셀 포맷은 Depth -> 3bytes Stencil -> 1bytes
	Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	// DepthStencilState 텍스처 해상도는 반드시 RenderTargetTexture 와 동일해야한다.
	Desc.Width = (UINT)m_vRenderResolution.x;
	Desc.Height = (UINT)m_vRenderResolution.y;

	// DepthStencil 용도(깊이 표현 -> z축)의 Texture
	Desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	// CPU 접근 불가
	Desc.CPUAccessFlags = 0;
	Desc.Usage = D3D11_USAGE_DEFAULT;

	// 샘플링
	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;

	// 저퀼리티 버전의 사본 생성여부 (거리가 멀면 high 퀄리티로 만들 필요가 없음)
	Desc.MipLevels = 1;
	Desc.MiscFlags = 0;

	Desc.ArraySize = 1;

	if (FAILED(m_Device->CreateTexture2D(&Desc, nullptr, m_DSTex.GetAddressOf())))
	{
		return E_FAIL;
	}

	// DepthStencilView 생성
	m_Device->CreateDepthStencilView(m_DSTex.Get(), nullptr, m_DSView.GetAddressOf());

	// OM(Output Merge State)에 RenderTargetTexture 와 DepthStencilTexture를 전달한다.
	m_Context->OMSetRenderTargets(1, m_RTView.GetAddressOf(), m_DSView.Get());

	return S_OK;
}

int CDevice::CreateConstBuffer()
{
	m_arrCB[(UINT)CB_TYPE::TRANSFORM] = new CConstBuffer;
	m_arrCB[(UINT)CB_TYPE::TRANSFORM]->Create(sizeof(tTransform), 1);


	return S_OK;
}