#pragma once
#include "skpch.h"
#include "DirectXShader.h"

#include <locale>
#include <codecvt>

namespace Sakura
{
	std::shared_ptr<Shader> Shader::Create(const ShaderSpecification& spec, std::shared_ptr<RendererContext> context)
	{
		return std::make_shared<DirectXShader>(spec, std::static_pointer_cast<DirectXContext>(context));
	}

	DirectXShader::DirectXShader(const ShaderSpecification& spec, std::shared_ptr<DirectXContext> context)
		: m_Spec(spec), m_Context(context)
	{
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

        Microsoft::WRL::ComPtr<ID3DBlob> vBlob;
        std::wstring vShaderFilepath = converter.from_bytes(m_Spec.vShaderFilepath);
        HRESULT hr = CompileShader(vShaderFilepath.c_str(), "main", "vs_4_0_level_9_1", vBlob.GetAddressOf());
        if (FAILED(hr))
        {
            SAKURA_CORE_ERROR("Failed compiling Vertex Shader %08X\n", hr);
            return;
        }

        Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
        std::wstring pShaderFilepath = converter.from_bytes(m_Spec.pShaderFilepath);
        hr = CompileShader(pShaderFilepath.c_str(), "main", "ps_4_0_level_9_1", pBlob.GetAddressOf());
        if (FAILED(hr))
        {
            SAKURA_CORE_ERROR("Failed compiling Pixel Shader %08X\n", hr);
            return;
        }

        m_Context->m_Device->CreateVertexShader(vBlob->GetBufferPointer(), vBlob->GetBufferSize(), 0, &m_VShader);
        CreateInputLayoutFromVertexShader(vBlob.Get(), context->m_Device.Get(), &m_InputLayout);
        m_Context->m_Device->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), 0, &m_PShader);
	}

	void DirectXShader::Bind()
	{
        m_Context->m_DeviceContext->IASetInputLayout(m_InputLayout.Get());
        m_Context->m_DeviceContext->VSSetShader(m_VShader.Get(), 0, 0);
        m_Context->m_DeviceContext->PSSetShader(m_PShader.Get(), 0, 0);
	}

	void DirectXShader::Unbind()
	{
	}

	HRESULT DirectXShader::CompileShader(LPCWSTR srcFile, LPCSTR entryPoint, LPCSTR profile, ID3DBlob** blob)
	{
        if (!srcFile || !entryPoint || !profile || !blob)
            return E_INVALIDARG;

        *blob = nullptr;

        UINT flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

        ID3DBlob* shaderBlob = nullptr;
        ID3DBlob* errorBlob = nullptr;
        HRESULT hr = D3DCompileFromFile(srcFile, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
            entryPoint, profile,
            flags, 0, &shaderBlob, &errorBlob);
        if (FAILED(hr))
        {
            if (errorBlob)
            {
                SAKURA_CORE_ERROR((char*)errorBlob->GetBufferPointer());
                errorBlob->Release();
            }

            if (shaderBlob)
                shaderBlob->Release();

            return hr;
        }

        *blob = shaderBlob;

        return hr;
	}
    HRESULT DirectXShader::CreateInputLayoutFromVertexShader(ID3DBlob* pVShaderBlob, ID3D11Device* pD3DDevice, ID3D11InputLayout** pInputLayout)
    {
        // Reflect shader info
        ID3D11ShaderReflection* pVertexShaderReflection = nullptr;
        HRESULT hr = S_OK;
        if (FAILED(D3DReflect(pVShaderBlob->GetBufferPointer(), pVShaderBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&pVertexShaderReflection)))
        {
            return S_FALSE;
        }

        // get shader description
        D3D11_SHADER_DESC shaderDesc;
        pVertexShaderReflection->GetDesc(&shaderDesc);

        // Read input layout description from shader info
        unsigned int byteOffset = 0;
        std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
        for (unsigned int i = 0; i < shaderDesc.InputParameters; ++i)
        {
            D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
            pVertexShaderReflection->GetInputParameterDesc(i, &paramDesc);

            // create input element desc
            D3D11_INPUT_ELEMENT_DESC elementDesc;
            elementDesc.SemanticName = paramDesc.SemanticName;
            elementDesc.SemanticIndex = paramDesc.SemanticIndex;
            elementDesc.InputSlot = 0;
            elementDesc.AlignedByteOffset = byteOffset;
            elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
            elementDesc.InstanceDataStepRate = 0;

            // determine DXGI format
            if (paramDesc.Mask == 1)
            {
                if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32_UINT;
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32_SINT;
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
                byteOffset += 4;
            }
            else if (paramDesc.Mask <= 3)
            {
                if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
                byteOffset += 8;
            }
            else if (paramDesc.Mask <= 7)
            {
                if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
                byteOffset += 12;
            }
            else if (paramDesc.Mask <= 15)
            {
                if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
                byteOffset += 16;
            }

            //save element desc
            inputLayoutDesc.push_back(elementDesc);
            //agnostic input layout
            m_Layout.PushElement(elementDesc.SemanticName, GetLayoutType(elementDesc.Format));
        }

        // Try to create Input Layout
        hr = pD3DDevice->CreateInputLayout(&inputLayoutDesc[0], inputLayoutDesc.size(), pVShaderBlob->GetBufferPointer(), pVShaderBlob->GetBufferSize(), pInputLayout);

        //Free allocation shader reflection memory
        pVertexShaderReflection->Release();

        return hr;
    }
    LayoutType DirectXShader::GetLayoutType(DXGI_FORMAT format)
    {
        switch (format)
        {
            case DXGI_FORMAT_R32G32_FLOAT:    return LayoutType::Float2D;
            case DXGI_FORMAT_R32G32B32_FLOAT: return LayoutType::Float3D;
            default:                          return LayoutType::None;
        }
    }
}