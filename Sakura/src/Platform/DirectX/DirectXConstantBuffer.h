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
		DirectXConstantBuffer(const ConstantBufferSpecification& spec, const DirectXContext& context);

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void Update(const void* data, uint32 size, uint32 offset) override;

		virtual const void* GetData() override { return m_Spec.Data; }
		virtual uint32 GetSize() override { return m_Spec.Size; }
		virtual uint32 GetSlot() override { return m_Spec.Slot; }

	private:
		ConstantBufferSpecification m_Spec;
		const DirectXContext& m_Context;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_Buffer;
	};
}