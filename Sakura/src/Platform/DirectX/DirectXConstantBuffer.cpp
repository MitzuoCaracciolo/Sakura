#include "skpch.h"
#include "DirectXConstantBuffer.h"

namespace Sakura
{
	std::shared_ptr<ConstantBuffer> ConstantBuffer::Create(const ConstantBufferSpecification& spec, std::shared_ptr<RendererContext> context)
	{
		return std::make_shared<DirectXConstantBuffer>(spec, std::static_pointer_cast<DirectXContext>(context));
	}

	DirectXConstantBuffer::DirectXConstantBuffer(const ConstantBufferSpecification& spec, std::shared_ptr<DirectXContext> context)
		: m_Spec(spec), m_Context(context)
	{
		D3D11_BUFFER_DESC constantBufferDesc = { };
		constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		constantBufferDesc.ByteWidth = m_Spec.Size;
		constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		constantBufferDesc.MiscFlags = 0u;

		D3D11_SUBRESOURCE_DATA constantBufferData = {};
		constantBufferData.pSysMem = m_Spec.Data;
		constantBufferData.SysMemPitch = 0;
		constantBufferData.SysMemSlicePitch = 0;

		m_Context->m_Device->CreateBuffer(&constantBufferDesc, &constantBufferData, &m_Buffer);
	}

	void DirectXConstantBuffer::Bind()
	{
		m_Context->m_DeviceContext->VSSetConstantBuffers(m_Spec.Slot, 1, m_Buffer.GetAddressOf());
	}

	void DirectXConstantBuffer::Unbind()
	{
	}

	void DirectXConstantBuffer::Update(const void* data, uint32 size, uint32 offset)
	{
		D3D11_MAPPED_SUBRESOURCE mappedSubResource = { };
		m_Context->m_DeviceContext->Map(m_Buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubResource);
		memcpy((uint8*)mappedSubResource.pData + offset, data, size);
		m_Context->m_DeviceContext->Unmap(m_Buffer.Get(), 0);
	}
}