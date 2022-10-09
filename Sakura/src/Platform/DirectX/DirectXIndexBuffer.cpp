#include "skpch.h"
#include "DirectXIndexBuffer.h"

namespace Sakura
{
	std::shared_ptr<IndexBuffer> IndexBuffer::Create(const IndexBufferSpecification& spec, std::shared_ptr<RendererContext> context)
	{
		return std::make_shared<DirectXIndexBuffer>(spec, std::static_pointer_cast<DirectXContext>(context));
	}

	DirectXIndexBuffer::DirectXIndexBuffer(const IndexBufferSpecification& spec, std::shared_ptr<DirectXContext> context)
		: m_Spec(spec), m_Context(context)
	{
		D3D11_BUFFER_DESC IndexBufferDesc = { };
		IndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		IndexBufferDesc.ByteWidth = sizeof(uint16_t) * m_Spec.Count;
		IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		IndexBufferDesc.CPUAccessFlags = 0;
		IndexBufferDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA IndexData;
		IndexData.pSysMem = m_Spec.Data;
		IndexData.SysMemPitch = 0;
		IndexData.SysMemSlicePitch = 0;

		m_Context->m_Device->CreateBuffer(&IndexBufferDesc, &IndexData, &m_Buffer);
	}

	void DirectXIndexBuffer::Bind()
	{
		m_Context->m_DeviceContext->IASetIndexBuffer(m_Buffer.Get(), DXGI_FORMAT_R16_UINT, 0);
	}

	void DirectXIndexBuffer::Unbind()
	{
	}
}