#pragma once

#include "Sakura/Renderer/RendererContext.h"

#include <Windows.h>
#include <d3d11.h>
#include <wrl.h>

namespace Sakura
{
	class DirectXContext : public RendererContext
	{
	public:
		DirectXContext(const RendererContextSpecification& spec);
		virtual ~DirectXContext();

		virtual void ClearBackBuffer(float red, float green, float blue) override;
		virtual void SwapBackBuffer() override;
		virtual void SetRenderTarget() override;
		virtual void SetPrimitiveTopology() override;
		virtual void Draw(uint16 count) override;

	private:
		uint32 m_ViewportWidth;
		uint32 m_ViewportHeight;

		Microsoft::WRL::ComPtr<ID3D11Device> m_Device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_DeviceContext;
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_BackBuffer;

		friend class DirectXVertexBuffer;
		friend class DirectXIndexBuffer;
		friend class DirectXConstantBuffer;
		friend class DirectXShader;
		friend class DirectXTexture;
	};
}

