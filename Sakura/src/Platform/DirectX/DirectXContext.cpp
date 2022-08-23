#include "skpch.h"
#include "DirectXContext.h"

namespace Sakura
{
	std::unique_ptr<GraphicsContext> GraphicsContext::Create(const GraphicsSpecification& spec)
	{
		return std::make_unique<DirectXContext>(spec);
	}

	DirectXContext::DirectXContext(const GraphicsSpecification& spec)
		: m_ViewportWidth(spec.Width), m_ViewportHeight(spec.Height)
	{
		DXGI_SWAP_CHAIN_DESC SwapChainDescription = { };
		SwapChainDescription.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		SwapChainDescription.SampleDesc.Count = 1;
		SwapChainDescription.SampleDesc.Quality = 0;
		SwapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		SwapChainDescription.BufferCount = 2;
		SwapChainDescription.OutputWindow = (HWND)spec.WindowHandle;
		SwapChainDescription.Windowed = TRUE;
		SwapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;

		D3D11CreateDeviceAndSwapChain(
			0, D3D_DRIVER_TYPE_HARDWARE, 0,
			D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_DEBUG,
			nullptr, 0,
			D3D11_SDK_VERSION, &SwapChainDescription,
			&m_SwapChain, &m_Device,
			0, &m_DeviceContext
		);

		Microsoft::WRL::ComPtr<ID3D11Texture2D> BackBuffer;
		m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &BackBuffer);

		m_Device->CreateRenderTargetView(BackBuffer.Get(), 0, &m_BackBuffer);
		m_DeviceContext->OMSetRenderTargets(1, m_BackBuffer.GetAddressOf(), 0);

		D3D11_VIEWPORT Viewport = { };
		Viewport.TopLeftX = 0;
		Viewport.TopLeftY = 0;
		Viewport.Width = (FLOAT)m_ViewportWidth;
		Viewport.Height = (FLOAT)m_ViewportHeight;

		m_DeviceContext->RSSetViewports(1, &Viewport);
	}

	DirectXContext::~DirectXContext()
	{
	}

	void DirectXContext::ClearBackBuffer(float red, float green, float blue)
	{
		float Color[] = { red, green, blue, 1.0f };
		m_DeviceContext->ClearRenderTargetView(m_BackBuffer.Get(), Color);
	}

	void DirectXContext::SwapBackBuffer()
	{
		m_DeviceContext->OMSetRenderTargets(1, m_BackBuffer.GetAddressOf(), 0);
		m_SwapChain->Present(0, 0);
	}
}
