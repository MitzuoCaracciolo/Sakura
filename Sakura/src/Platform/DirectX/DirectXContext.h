#pragma once

#include "Sakura/Renderer/GraphicsContext.h"

#include <Windows.h>
#include <d3d11.h>
#include <wrl.h>

namespace Sakura
{
	class DirectXContext : public GraphicsContext
	{
	public:
		DirectXContext(const GraphicsSpecification& spec);
		virtual ~DirectXContext();

		virtual void ClearBackBuffer(float red, float green, float blue);
		virtual void SwapBackBuffer();

	private:
		uint32 m_ViewportWidth;
		uint32 m_ViewportHeight;

		Microsoft::WRL::ComPtr<ID3D11Device> m_Device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_DeviceContext;
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_BackBuffer;

		friend class DirectXVertexBuffer;
		friend class DirectXIndexBuffer;
		friend class DirectXShader;
	};
}

