#pragma once

#include "Sakura/Core.h"

#include <vector>

namespace Sakura
{
	enum class LayoutType
	{
		None = 0, Position2D, Position3D, Color3D
	};

	static uint32 LayoutTypeSize(LayoutType type)
	{
		switch (type)
		{
		case LayoutType::Position2D: return sizeof(float) * 2;
		case LayoutType::Position3D: return sizeof(float) * 3;
		case LayoutType::Color3D: return sizeof(float) * 3;
		}

		return 0;
	}

	struct VertexLayoutElement
	{
		const char* Name;
		LayoutType Type;
		uint32 Size;
		uint32 Offset;

		VertexLayoutElement(const char* name, LayoutType type)
			: Name(name), Type(type), Size(LayoutTypeSize(type)), Offset(0)
		{}
	};

	class VertexLayout
	{
	public:
		VertexLayout(const std::initializer_list<VertexLayoutElement>& elements)
			: m_Elements(elements)
		{
			uint32 offset = 0;
			m_Stride = 0;
			for (auto& element : this->m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}

		std::vector<VertexLayoutElement>& GetElements() { return m_Elements; }
		uint32 GetStride() { return m_Stride; }

		std::vector<VertexLayoutElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<VertexLayoutElement>::iterator end() { return m_Elements.end(); }

	private:
		std::vector<VertexLayoutElement> m_Elements;
		uint32 m_Stride;
	};
}