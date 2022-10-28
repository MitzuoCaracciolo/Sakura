#pragma once

#include "Sakura/Core.h"
#include "Sakura/Renderer/RendererContext.h"
#include "Sakura/Renderer/Shader.h"
#include "Sakura/Renderer/VertexBuffer.h"
#include "Sakura/Renderer/IndexBuffer.h"
#include "Sakura/Renderer/ConstantBuffer.h"
#include "Sakura/Renderer/Mesh.h"

#include <glm/glm.hpp>

#include <memory>

namespace Sakura
{
	struct CBuffer
	{
		glm::mat4 Transform;
	};

	class SceneRenderer
	{
	public:
		SceneRenderer(std::shared_ptr<RendererContext> context);

		void BeginScene();
		void SubmitMesh(const Mesh& mesh);
		void EndScene();

	private:
		void TransverseNodeHierarchy(const Node& node, glm::mat4 AccumulatedTransform, const Mesh& mesh);

	private:
		std::shared_ptr<RendererContext> m_Context;
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<ConstantBuffer> m_VSConstantBuffer;
	};
}