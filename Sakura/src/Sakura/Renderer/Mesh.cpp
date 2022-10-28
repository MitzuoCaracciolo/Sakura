#include "skpch.h"
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

namespace Sakura
{
	Mesh::Mesh(const std::string& filepath, std::shared_ptr<RendererContext> context)
	{
		Assimp::Importer imp;
		const auto pScene = imp.ReadFile(filepath.c_str(),
			aiProcess_Triangulate |
			aiProcess_JoinIdenticalVertices |
			aiProcess_MakeLeftHanded | 
			aiProcess_FlipWindingOrder |
			aiProcess_GenNormals |
			aiProcess_ValidateDataStructure
		);

		uint32_t vertexCount = 0;
		uint32_t indexCount = 0;

		for (size_t i = 0; i < pScene->mNumMeshes; i++)
		{
			const auto& mesh = *pScene->mMeshes[i];

			Submesh submesh = {};
			submesh.BaseVertex = vertexCount;
			submesh.BaseIndex = indexCount;
			submesh.VertexCount = mesh.mNumVertices;
			submesh.IndexCount = mesh.mNumFaces * 3;
			submesh.MeshName = mesh.mName.C_Str();

			m_Submeshes.emplace_back(std::move(submesh));

			vertexCount += mesh.mNumVertices;
			indexCount += mesh.mNumFaces * 3;

			for (size_t j = 0; j < mesh.mNumVertices; j++)
			{
				Vertex vertex;
				vertex.Position = { mesh.mVertices[j].x, mesh.mVertices[j].y, mesh.mVertices[j].z };
				vertex.Normal = { mesh.mNormals[j].x, mesh.mNormals[j].y, mesh.mNormals[j].z };

				m_StaticVertices.emplace_back(std::move(vertex));
			}

			for (size_t j = 0; j < mesh.mNumFaces; j++)
			{
				Index index = { mesh.mFaces[j].mIndices[0], mesh.mFaces[j].mIndices[1], mesh.mFaces[j].mIndices[2] };
				m_Indices.emplace_back(std::move(index));
			}
		}

		VertexBufferSpecification vBufferSpec = {};
		vBufferSpec.Data = m_StaticVertices.data();
		vBufferSpec.Size = vertexCount;
		vBufferSpec.Layout = { { "Position", LayoutType::Float3D }, { "Normal", LayoutType::Float3D } };

		m_VertexBuffer = VertexBuffer::Create(vBufferSpec, context);

		IndexBufferSpecification iBufferSpec = {};
		iBufferSpec.Data = m_Indices.data();
		iBufferSpec.Count = indexCount;

		m_IndexBuffer = IndexBuffer::Create(iBufferSpec, context);

		BuildNodeHierarchy(*pScene->mRootNode, m_Root);
	}

	void Mesh::BuildNodeHierarchy(const aiNode& assimpNode, Node& node)
	{
		node.Tag = assimpNode.mName.C_Str();
		node.LocalTransform = Mat4FromAssimpMat4(assimpNode.mTransformation);
		node.SubmeshIndex = assimpNode.mNumMeshes > 0 ? assimpNode.mMeshes[0] : -1;

		for (size_t i = 0; i < assimpNode.mNumChildren; i++)
		{
			auto& childNode = node.Childs.emplace_back();
			BuildNodeHierarchy(*assimpNode.mChildren[i], childNode);
		}
	}

	glm::mat4 Mesh::Mat4FromAssimpMat4(const aiMatrix4x4& matrix)
	{
		glm::mat4 result;
		//the a,b,c,d in assimp is the row ; the 1,2,3,4 is the column
		result[0][0] = matrix.a1; result[1][0] = matrix.a2; result[2][0] = matrix.a3; result[3][0] = matrix.a4;
		result[0][1] = matrix.b1; result[1][1] = matrix.b2; result[2][1] = matrix.b3; result[3][1] = matrix.b4;
		result[0][2] = matrix.c1; result[1][2] = matrix.c2; result[2][2] = matrix.c3; result[3][2] = matrix.c4;
		result[0][3] = matrix.d1; result[1][3] = matrix.d2; result[2][3] = matrix.d3; result[3][3] = matrix.d4;
		return result;
	}

}

