#include "TestLayer.h"

TestLayer::TestLayer(Sakura::GraphicsContext& context)
	: m_Context(context)
{
}

void TestLayer::OnAttach()
{
	float vertices[] = {
		 -0.5f,  0.5f,
		  0.5f,  0.5f,
		  0.5f, -0.5f,
		 -0.5f, -0.5f
	};

	uint16_t indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	float model[4][4] = {
		{ 1.0f, 0.0f, 0.0f, 0.5f },
		{ 0.0f, 1.0f, 0.0f, 0.5f },
		{ 0.0f, 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f } 
	};

	Sakura::VertexBufferSpecification vBufferSpec;
	vBufferSpec.Data = vertices;
	vBufferSpec.Size = sizeof(vertices);
	vBufferSpec.Layout = { { "POSITION", Sakura::LayoutType::Float2D } };

	m_VertexBuffer = Sakura::VertexBuffer::Create(vBufferSpec, m_Context);

	Sakura::IndexBufferSpecification iBufferSpec;
	iBufferSpec.Data = indices;
	iBufferSpec.Count = std::size(indices);

	m_IndexBuffer = Sakura::IndexBuffer::Create(iBufferSpec, m_Context);

	Sakura::ConstantBufferSpecification cBufferSpec;
	cBufferSpec.Data = model;
	cBufferSpec.Size = sizeof(model);
	cBufferSpec.Slot = 0;

	m_ConstantBuffer = Sakura::ConstantBuffer::Create(cBufferSpec, m_Context);

	Sakura::ShaderSpecification shaderSpec;
	shaderSpec.vShaderFilepath = "assets\\shaders\\VertexShader.hlsl";
	shaderSpec.pShaderFilepath = "assets\\shaders\\PixelShader.hlsl";

	m_Shader = Sakura::Shader::Create(shaderSpec, m_Context);
}

void TestLayer::OnDetach()
{
}

void TestLayer::OnUpdate()
{
	m_Context.SetPrimitiveTopology();

	m_VertexBuffer->Bind();
	m_IndexBuffer->Bind();
	m_ConstantBuffer->Bind();
	m_Shader->Bind();

	m_Context.SetRenderTarget();
	m_Context.Draw(m_IndexBuffer->GetCount());
}

void TestLayer::OnEvent(Sakura::Event& event)
{
}
