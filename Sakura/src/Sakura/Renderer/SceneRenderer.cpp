#include "skpch.h"
#include "SceneRenderer.h"

#include <glm/ext/matrix_transform.hpp>

namespace Sakura
{
	SceneRenderer::SceneRenderer(std::shared_ptr<RendererContext> context)
		: m_Context(context)
	{
		// Steps for the configuration:
		// 1. Configure RenderPass (This involves having both a Framebuffer and RenderPass configuration)
		// 2. Configure the Primitive Topology
		// 3. Configure the Shader and the VertexLayout used for that Shader (This aliviates the need for ShaderReflection {it's messy})
		// 4. Set up the constant buffer used to submit data to the GPU for use on the shader

		ShaderSpecification shaderSpec;
		shaderSpec.vShaderFilepath = "..\\Sakura\\assets\\shaders\\VertexShader.hlsl";
		shaderSpec.pShaderFilepath = "..\\Sakura\\assets\\shaders\\PixelShader.hlsl";
		shaderSpec.Layout = { { "Position", LayoutType::Float3D }, { "Normal", LayoutType::Float3D } };

		m_Shader = Shader::Create(shaderSpec, m_Context);

		glm::mat4 identity{ 1.0f };

		ConstantBufferSpecification cBufferSpec = {};
		cBufferSpec.Data = &identity;
		cBufferSpec.Size = sizeof(CBuffer);
		cBufferSpec.Slot = 0;

		m_VSConstantBuffer = ConstantBuffer::Create(cBufferSpec, m_Context);
	}

	void SceneRenderer::BeginScene()
	{
		m_Context->SetPrimitiveTopology();
		m_Context->SetRenderTarget();

		m_Shader->Bind();
		m_VSConstantBuffer->Bind();
	}


	void SceneRenderer::SubmitMesh(const Mesh& mesh)
	{
		const auto& rootNode = mesh.GetRoot();
		glm::mat4 transform{ 1.0f };
		transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, 1.0f));
		transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));
		for (const auto& child : rootNode.Childs)
		{	
			TransverseNodeHierarchy(child, transform, mesh);
		}
	}

	void SceneRenderer::EndScene()
	{

	}

	void SceneRenderer::TransverseNodeHierarchy(const Node& node, glm::mat4 AccumulatedTransform, const Mesh& mesh)
	{
		uint32_t submeshIndex = node.SubmeshIndex;
		Submesh submesh = mesh.GetSubmesh(submeshIndex);
		
		glm::mat4 transform = node.LocalTransform * AccumulatedTransform;
		m_VSConstantBuffer->Update(&transform, sizeof(CBuffer), 0);

		mesh.GetVertexBuffer().Bind();
		mesh.GetIndexBuffer().Bind();

		m_Context->Draw(submesh.IndexCount, submesh.BaseIndex, submesh.BaseVertex);

		for (const auto& child : node.Childs)
		{
			TransverseNodeHierarchy(child, transform, mesh);
		}
	}
}

