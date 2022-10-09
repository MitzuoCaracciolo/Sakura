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
		DirectXVertexBuffer(const VertexBufferSpecification& spec, std::shared_ptr<DirectXContext> context);

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual const VertexLayout& GetLayout() const override { return m_Spec.Layout; }
		virtual void SetLayout(VertexLayout& layout) override;

	private:
		VertexBufferSpecification m_Spec;
		std::shared_ptr<DirectXContext> m_Context;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_Buffer;
	};
}

