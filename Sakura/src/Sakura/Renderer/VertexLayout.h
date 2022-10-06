#pragma once

#include "Sakura/Core.h"

#include <vector>

namespace Sakura
{
	enum class LayoutType
	{
		None = 0, Float2D, Float3D
	};

	static uint32 LayoutTypeSize(LayoutType type)
	{
		switch (type)
		{
		case LayoutType::Float2D: return sizeof(float) * 2;
		case LayoutType::Float3D: return sizeof(float) * 3;
		}

		return 0;
	}

	struct VertexLayoutElement
	{
		std::string Name;
		LayoutType Type;
		uint32 Size;
		uint32 Offset;

		VertexLayoutElement(std::string name, LayoutType type)
			: Name(name), Type(type), Size(LayoutTypeSize(type)), Offset(0)
		{}
	};

	class VertexLayout
	{
	public:
		VertexLayout()
			: m_Stride(0)
		{ }
			
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

		void PushElement(std::string name, LayoutType type)
		{
			VertexLayoutElement element(name, type);

			element.Offset = m_Stride;
			m_Stride += element.Size;
			m_Elements.emplace_back(element);
		}

		std::vector<VertexLayoutElement>& GetElements() { return m_Elements; }
		uint32 GetStride() const { return m_Stride; }

		std::vector<VertexLayoutElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<VertexLayoutElement>::iterator end() { return m_Elements.end(); }

	private:
		std::vector<VertexLayoutElement> m_Elements;
		uint32 m_Stride;
	};
}