#include "skpch.h"
#include "DirectXTexture.h"

#include <stb/stb_image.h>

namespace Sakura
{
	std::shared_ptr<Texture> Texture::Create(const TextureSpecification& spec, std::shared_ptr<RendererContext> context)
	{
		return std::make_shared<DirectXTexture>(spec, std::static_pointer_cast<DirectXContext>(context));
	}

	DirectXTexture::DirectXTexture(const TextureSpecification& spec, std::shared_ptr<DirectXContext> context)
		: m_Spec(spec), m_Context(context)
	{
		int width, height, channels;
		stbi_uc* data = stbi_load(m_Spec.TexturePath.c_str(), &width, &height, &channels, STBI_rgb_alpha);
		
		m_Width = width;
		m_Height = height;

		D3D11_TEXTURE2D_DESC textureDesc = {};
		textureDesc.Width = m_Width;
		textureDesc.Height = m_Height;
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1;
		textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.SampleDesc.Quality = 0;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags = 0;
		textureDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA textureData;
		textureData.pSysMem = data;
		textureData.SysMemPitch = m_Width * sizeof(stbi_uc) * 4;
		textureData.SysMemSlicePitch = 0;

		Microsoft::WRL::ComPtr<ID3D11Texture2D> Texture;
		m_Context->m_Device->CreateTexture2D(&textureDesc, &textureData, &Texture);

		//stbi_image_free(data);

		// create the resource view on the texture
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Format = textureDesc.Format;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.Texture2D.MipLevels = -1;

		m_Context->m_Device->CreateShaderResourceView(Texture.Get(), &srvDesc, &m_TextureView);

		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

		m_Context->m_Device->CreateSamplerState(&samplerDesc, &m_Sampler);
	}

	void DirectXTexture::Bind()
	{
		m_Context->m_DeviceContext->PSSetShaderResources(m_Spec.Slot, 1, m_TextureView.GetAddressOf());
		m_Context->m_DeviceContext->PSSetSamplers(m_Spec.Slot, 1, m_Sampler.GetAddressOf());
	}

	void DirectXTexture::Unbind()
	{
	}

}

