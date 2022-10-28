#pragma once

#include "Sakura/Renderer/IndexBuffer.h"
#include "Platform/DirectX/DirectXContext.h"

#include <d3d11.h>
#include <wrl.h>

namespace Sakura
{
	class DirectXIndexBuffer : public IndexBuffer
	{
	public:
		DirectXIndexBuffer(const IndexBufferSpecification& spec, std::shared_ptr<DirectXContext> context);

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual uint32_t GetCount() const override { return m_Spec.Count; }

	private:
		IndexBufferSpecification m_Spec;
		std::shared_ptr<DirectXContext> m_Context;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_Buffer;
	};
}