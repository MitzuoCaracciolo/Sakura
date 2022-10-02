#pragma once

#include "Sakura/Renderer/VertexBuffer.h"
#include "Platform/DirectX/DirectXContext.h"

#include <d3d11.h>
#include <wrl.h>

namespace Sakura
{
	class DirectXVertexBuffer : public VertexBuffer
	{
	public:
		DirectXVertexBuffer(const VertexBufferSpecification& spec, const DirectXContext& context);

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void SetData(const void* data, uint32 byteSize) override;

		virtual void SetLayout(VertexLayout& layout) override;
		virtual VertexLayout& GetLayout() override { return m_Spec.Layout; }

	private:
		VertexBufferSpecification m_Spec;
		const DirectXContext& m_Context;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_Buffer;
	};
}

