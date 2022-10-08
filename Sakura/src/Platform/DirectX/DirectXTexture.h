#pragma once
#include "Sakura/Renderer/Texture.h"
#include "Platform/DirectX/DirectXContext.h"

#include <d3d11.h>
#include <wrl.h>
#include <memory>

namespace Sakura
{
	class DirectXTexture : public Texture
	{
	public:
		DirectXTexture(const TextureSpecification& spec, DirectXContext& context);

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual uint32 GetSlot() const { return m_Spec.Slot; }
		virtual uint32 GetWidth() const { return m_Width; }
		virtual uint32 GetHeight() const { return m_Height; }

	private:
		TextureSpecification m_Spec;
		uint32 m_Width;
		uint32 m_Height;
		DirectXContext& m_Context;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_TextureView;
		Microsoft::WRL::ComPtr<ID3D11SamplerState> m_Sampler;
	};
}