#pragma once
#include "Sakura/Renderer/Shader.h"
#include "Platform/DirectX/DirectXContext.h"

#include <wrl.h>
#include <d3d11.h>
#include <d3dcompiler.h>

namespace Sakura
{
	class DirectXShader : public Shader
	{
	public:
		DirectXShader(const ShaderSpecification& spec, const DirectXContext& context);

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual VertexLayout& GetLayout() override { return m_Layout; };

	private:
		HRESULT CompileShader(LPCWSTR srcFile, LPCSTR entryPoint, LPCSTR profile, ID3DBlob** blob);
		HRESULT CreateInputLayoutFromVertexShader(ID3DBlob* pVShaderBlob, ID3D11Device* pD3DDevice, ID3D11InputLayout** pInputLayout);

		static LayoutType GetLayoutType(DXGI_FORMAT format);

	private:
		VertexLayout m_Layout;
		ShaderSpecification m_Spec;
		const DirectXContext& m_Context;
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VShader;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PShader;
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_InputLayout;
	};
}