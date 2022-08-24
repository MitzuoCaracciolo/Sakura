#include "skpch.h"
#include "DirectXVertexBuffer.h"

namespace Sakura
{
	std::shared_ptr<VertexBuffer> VertexBuffer::Create(const VertexBufferSpecification& spec, const GraphicsContext& context)
	{
		return std::make_shared<DirectXVertexBuffer>(spec, dynamic_cast<const DirectXContext&>(context));
	}

	DirectXVertexBuffer::DirectXVertexBuffer(const VertexBufferSpecification& spec, const DirectXContext& context)
		: m_Spec(spec), m_Context(context)
	{
		D3D11_BUFFER_DESC VertexBufferDesc = { };
		VertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		VertexBufferDesc.ByteWidth = m_Spec.Size;
		VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		VertexBufferDesc.CPUAccessFlags = 0;
		VertexBufferDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA VertexData;
		VertexData.pSysMem = m_Spec.Data;
		VertexData.SysMemPitch = 0;
		VertexData.SysMemSlicePitch = 0;

		context.m_Device->CreateBuffer(&VertexBufferDesc, &VertexData, &m_Buffer);
	}

	void DirectXVertexBuffer::Bind()
	{
		UINT stride = m_Spec.Layout.GetStride();
		UINT offset = 0;
		m_Context.m_DeviceContext->IASetVertexBuffers(0, 1, m_Buffer.GetAddressOf(), &stride, &offset);
	}

	void DirectXVertexBuffer::Unbind()
	{
	}

	void DirectXVertexBuffer::SetData(const void* data, uint32 size)
	{
		memcpy(m_Spec.Data, data, size);
		m_Spec.Size = size;
	}

	void DirectXVertexBuffer::SetLayout(VertexLayout& layout)
	{
		m_Spec.Layout = layout;
	}
}
