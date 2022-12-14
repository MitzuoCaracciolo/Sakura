#pragma once
#include "Sakura.h"

class TestLayer : public Sakura::Layer
{
public:
	TestLayer(std::shared_ptr<Sakura::Window> context);

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate() override;
	virtual void OnEvent(Sakura::Event& event) override;

private:
	std::shared_ptr<Sakura::Window> m_Window;

	std::shared_ptr<Sakura::VertexBuffer> m_VertexBuffer;
	std::shared_ptr<Sakura::IndexBuffer> m_IndexBuffer;
	std::shared_ptr<Sakura::ConstantBuffer> m_ConstantBuffer;
	std::shared_ptr<Sakura::Texture> m_Texture;
	std::shared_ptr<Sakura::Shader> m_Shader;
};

