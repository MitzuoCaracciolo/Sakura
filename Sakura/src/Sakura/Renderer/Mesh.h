#pragma once

#include "Sakura/Renderer/RendererContext.h"
#include "Sakura/Renderer/VertexBuffer.h"
#include "Sakura/Renderer/IndexBuffer.h"

#include <glm/glm.hpp>
#include <assimp/scene.h>

#include <vector>
#include <memory>

namespace Sakura
{
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
	};

	struct Index
	{
		uint32_t V1, V2, V3;
	};

	struct Submesh
	{
		uint32_t BaseVertex;
		uint32_t BaseIndex;
		uint32_t IndexCount;
		uint32_t VertexCount; //We don't actually need this for drawing
		std::string MeshName;
	};

	struct Node
	{
		std::string Tag;
		size_t SubmeshIndex;
		glm::mat4 LocalTransform { 1.0 };
		std::vector<Node> Childs;
	};

	class Mesh
	{
	public:
		Mesh(const std::string& filepath, std::shared_ptr<RendererContext> context);

		const Node& GetRoot() const { return m_Root; }
		Node& GetRoot() { return m_Root; }

		Submesh& GetSubmesh(uint32_t index) { return m_Submeshes[index]; }
		const Submesh& GetSubmesh(uint32_t index) const { return m_Submeshes[index]; }

		VertexBuffer& GetVertexBuffer() const { return *m_VertexBuffer; }
		IndexBuffer& GetIndexBuffer() const { return *m_IndexBuffer; }

	private:
		void BuildNodeHierarchy(const aiNode& assimpNode, Node& parentNode);
		static glm::mat4 Mat4FromAssimpMat4(const aiMatrix4x4& matrix);

	private:
		Node m_Root; 
		std::vector<Submesh> m_Submeshes;

		std::vector<Vertex> m_StaticVertices;
		std::vector<Index> m_Indices;

		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};
}