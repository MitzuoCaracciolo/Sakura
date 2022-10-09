#pragma once
#include "Sakura/Renderer/ConstantBuffer.h"
#include "Platform/DirectX/DirectXContext.h"

#include <d3d11.h>
#include <wrl.h>
#include <memory>

namespace Sakura
{
	class DirectXConstantBuffer : public ConstantBuffer
	{
	public:
		DirectXConstantBuffer(const ConstantBufferSpecification& spec, std::shared_ptr<DirectXContext> context);

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void Update(const void* data, uint32 size, uint32 offset) override;

		virtual uint32 GetSlot() const override { return m_Spec.Slot; }

	private:
		ConstantBufferSpecification m_Spec;
		std::shared_ptr<DirectXContext> m_Context;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_Buffer;
	};
}