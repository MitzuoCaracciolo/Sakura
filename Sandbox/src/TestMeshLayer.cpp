#include "TestMeshLayer.h"

TestMeshLayer::TestMeshLayer(std::shared_ptr<Sakura::Window> window)
	: m_Window(window)
{
	m_SceneRenderer = std::make_unique<Sakura::SceneRenderer>(m_Window->GetContext());
	m_Mesh = std::make_shared<Sakura::Mesh>("assets\\models\\suzanne.obj", m_Window->GetContext());
}

void TestMeshLayer::OnAttach()
{
}

void TestMeshLayer::OnDetach()
{
}

void TestMeshLayer::OnUpdate()
{
	m_SceneRenderer->BeginScene();
	m_SceneRenderer->SubmitMesh(*m_Mesh);
	m_SceneRenderer->EndScene();
}

void TestMeshLayer::OnEvent(Sakura::Event& event)
{
}
