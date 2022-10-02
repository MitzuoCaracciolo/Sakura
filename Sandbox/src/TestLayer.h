#pragma once
#include "Sakura.h"

class TestLayer : public Sakura::Layer
{
public:
	TestLayer(Sakura::GraphicsContext& context);

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate() override;
	virtual void OnEvent(Sakura::Event& event) override;

private:
	Sakura::GraphicsContext& m_Context;

	std::shared_ptr<Sakura::VertexBuffer> m_VertexBuffer;
	std::shared_ptr<Sakura::IndexBuffer> m_IndexBuffer;
	std::shared_ptr<Sakura::Shader> m_Shader;
};

