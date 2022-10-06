#include "TestLayer.h"

TestLayer::TestLayer(Sakura::Window& window)
	: m_Window(window)
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

	auto& graphics = m_Window.GetContext();

	Sakura::VertexBufferSpecification vBufferSpec;
	vBufferSpec.Data = vertices;
	vBufferSpec.Size = sizeof(vertices);
	vBufferSpec.Layout = { { "POSITION", Sakura::LayoutType::Float2D } };

	m_VertexBuffer = Sakura::VertexBuffer::Create(vBufferSpec, graphics);

	Sakura::IndexBufferSpecification iBufferSpec;
	iBufferSpec.Data = indices;
	iBufferSpec.Count = std::size(indices);

	m_IndexBuffer = Sakura::IndexBuffer::Create(iBufferSpec, graphics);

	Sakura::ConstantBufferSpecification cBufferSpec;
	cBufferSpec.Data = model;
	cBufferSpec.Size = sizeof(model);
	cBufferSpec.Slot = 0;

	m_ConstantBuffer = Sakura::ConstantBuffer::Create(cBufferSpec, graphics);

	Sakura::ShaderSpecification shaderSpec;
	shaderSpec.vShaderFilepath = "assets\\shaders\\VertexShader.hlsl";
	shaderSpec.pShaderFilepath = "assets\\shaders\\PixelShader.hlsl";

	m_Shader = Sakura::Shader::Create(shaderSpec, graphics);
}

void TestLayer::OnDetach()
{
}

void TestLayer::OnUpdate()
{
	auto& graphics = m_Window.GetContext();

	graphics.SetPrimitiveTopology();

	m_VertexBuffer->Bind();
	m_IndexBuffer->Bind();
	m_ConstantBuffer->Bind();
	m_Shader->Bind();

	graphics.SetRenderTarget();
	graphics.Draw(m_IndexBuffer->GetCount());
}

void TestLayer::OnEvent(Sakura::Event& event)
{
}
