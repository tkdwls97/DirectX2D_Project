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
	// ��� ������ 
	m_hRenderWnd = _hWnd;

	// ���� �ػ�
	m_vRenderResolution = _vResolution;

	// ��ġ �ʱ�ȭ
	D3D_FEATURE_LEVEL eLevel = D3D_FEATURE_LEVEL_11_0;

	if (FAILED(D3D11CreateDevice(nullptr
		, D3D_DRIVER_TYPE_HARDWARE, nullptr
		, D3D11_CREATE_DEVICE_DEBUG
		, nullptr, 0, D3D11_SDK_VERSION
		, m_Device.GetAddressOf(), &eLevel, m_Context.GetAddressOf())))
	{
		MessageBox(nullptr, L"Device, Context ���� ����", L"Device �ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}

	// ����ü�� ����
	if (FAILED(CreateSwapChain()))
	{
		MessageBox(nullptr, L"SwapChain ���� ����", L"Device �ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}

	// ����Ÿ��, ����Ÿ�� ��, ���� ���ٽ� Ÿ��, ���� ���ٽ� �� ����
	if (FAILED(CreateTargetView()))
	{
		MessageBox(nullptr, L"Ÿ�� �� View ���� ����", L"Device �ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}

	// ViewPort ����
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
		MessageBox(nullptr, L"������� ���� ����", L"Device �ʱ�ȭ ����", MB_OK);
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


int CDevice::CreateSwapChain()
{
	// SwapChain ���� ����ü
	DXGI_SWAP_CHAIN_DESC tDesc = {};

	// SWapChain�� �����ϴ� Buffer(RenderTarget) �� ���� ����
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

	tDesc.Windowed = true; // â���
	tDesc.OutputWindow = m_hRenderWnd; // SwapChain�� ��� ������ ����

	// ����ü�� ��������� ���� Factory�� �����Ѵ�
	ComPtr<IDXGIDevice>		pIdxgiDevice = nullptr;
	ComPtr<IDXGIAdapter>	pAdapter = nullptr;
	ComPtr<IDXGIFactory>	pFactory = nullptr;

	m_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)pIdxgiDevice.GetAddressOf());
	pIdxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pAdapter.GetAddressOf());
	pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)pFactory.GetAddressOf());

	// SwapChain ����
	if (FAILED(pFactory->CreateSwapChain(m_Device.Get(), &tDesc, m_SwapChain.GetAddressOf())))
	{
		return E_FAIL;
	}
	return S_OK;
}

int CDevice::CreateTargetView()
{
	/*
	ID3D11Resource; �θ�

	- ID3D11Buffer; �ڽ�
	- ID3D11Texture2D; �ڽ�
	*/

	// ����Ÿ�� �ؽ��ĸ� ����ü�����κ��� ���´�.
	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)m_RTTex.GetAddressOf());

	// ���� Ÿ�� ��
	m_Device->CreateRenderTargetView(m_RTTex.Get(), nullptr, m_RTView.GetAddressOf());

	// View ?
	// RenderTargetView
	// DepthStencilView
	// ShaderResourceView
	// UnorderedAccessView

	// DepthStencilTexture ����
	D3D11_TEXTURE2D_DESC Desc = {};

	// �ȼ� ������ Depth -> 3bytes Stencil -> 1bytes
	Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	// DepthStencilState �ؽ�ó �ػ󵵴� �ݵ�� RenderTargetTexture �� �����ؾ��Ѵ�.
	Desc.Width = (UINT)m_vRenderResolution.x;
	Desc.Height = (UINT)m_vRenderResolution.y;

	// DepthStencil �뵵(���� ǥ�� -> z��)�� Texture
	Desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	// CPU ���� �Ұ�
	Desc.CPUAccessFlags = 0;
	Desc.Usage = D3D11_USAGE_DEFAULT;

	// ���ø�
	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;

	// ������Ƽ ������ �纻 �������� (�Ÿ��� �ָ� high ����Ƽ�� ���� �ʿ䰡 ����)
	Desc.MipLevels = 1;
	Desc.MiscFlags = 0;

	Desc.ArraySize = 1;

	if (FAILED(m_Device->CreateTexture2D(&Desc, nullptr, m_DSTex.GetAddressOf())))
	{
		return E_FAIL;
	}

	// DepthStencilView ����
	m_Device->CreateDepthStencilView(m_DSTex.Get(), nullptr, m_DSView.GetAddressOf());

	// OM(Output Merge State)�� RenderTargetTexture �� DepthStencilTexture�� �����Ѵ�.
	m_Context->OMSetRenderTargets(1, m_RTView.GetAddressOf(), m_DSView.Get());

	return S_OK;
}

int CDevice::CreateConstBuffer()
{
	m_arrCB[(UINT)CB_TYPE::TRANSFORM] = new CConstBuffer;
	m_arrCB[(UINT)CB_TYPE::TRANSFORM]->Create(sizeof(tTransform), 1);


	return S_OK;
}