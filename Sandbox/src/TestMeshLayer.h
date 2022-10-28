#pragma once
#include "Sakura.h"

class TestMeshLayer : public Sakura::Layer
{
public:
	TestMeshLayer(std::shared_ptr<Sakura::Window> context);

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate() override;
	virtual void OnEvent(Sakura::Event& event) override;

private:
	std::shared_ptr<Sakura::Window> m_Window;

	std::unique_ptr<Sakura::SceneRenderer> m_SceneRenderer;
	std::shared_ptr<Sakura::Mesh> m_Mesh;
};
