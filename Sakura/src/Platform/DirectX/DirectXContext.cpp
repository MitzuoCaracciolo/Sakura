#include "skpch.h"
#include "DirectXContext.h"

namespace Sakura
{
	std::shared_ptr<RendererContext> RendererContext::Create(const RendererContextSpecification& spec)
	{
		return std::make_unique<DirectXContext>(spec);
	}

	DirectXContext::DirectXContext(const RendererContextSpecification& spec)
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

		D3D11_DEPTH_STENCIL_DESC dsDesc = {};
		dsDesc.DepthEnable = TRUE;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

		m_Device->CreateDepthStencilState(&dsDesc, &m_DepthStencilState);

		m_DeviceContext->OMSetDepthStencilState(m_DepthStencilState.Get(), 1);

		D3D11_TEXTURE2D_DESC depthStencilDesc;
		depthStencilDesc.Width = m_ViewportWidth;
		depthStencilDesc.Height = m_ViewportHeight;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.CPUAccessFlags = 0;
		depthStencilDesc.MiscFlags = 0;

		Microsoft::WRL::ComPtr<ID3D11Texture2D> mDepthStencilBuffer;
		m_Device->CreateTexture2D(&depthStencilDesc, 0, &mDepthStencilBuffer);

		m_Device->CreateDepthStencilView(mDepthStencilBuffer.Get(), 0, &m_DepthStencilView);
	}

	DirectXContext::~DirectXContext()
	{
	}

	void DirectXContext::ClearBackBuffer(float red, float green, float blue)
	{
		float Color[] = { red, green, blue, 1.0f };
		m_DeviceContext->ClearRenderTargetView(m_BackBuffer.Get(), Color);
		m_DeviceContext->ClearDepthStencilView(m_DepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
	}

	void DirectXContext::SwapBackBuffer()
	{
		m_DeviceContext->OMSetRenderTargets(1, m_BackBuffer.GetAddressOf(), 0);
		m_SwapChain->Present(0, 0);
	}

	void DirectXContext::SetRenderTarget() 
	{
		m_DeviceContext->OMSetRenderTargets(1, m_BackBuffer.GetAddressOf(), m_DepthStencilView.Get());
	}

	void DirectXContext::SetPrimitiveTopology() 
	{
		m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	void DirectXContext::Draw(uint32_t count, uint32_t baseIndex, uint32_t baseVertex) 
	{
		m_DeviceContext->DrawIndexed(count, baseIndex, baseVertex);
	}
}
