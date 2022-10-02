#pragma once

#include "Sakura/Core.h"
#include "Sakura/Renderer/VertexLayout.h"
#include "Sakura/Renderer/GraphicsContext.h"

#include <memory>

namespace Sakura
{
	struct VertexBufferSpecification
	{
		void* Data;
		uint32 Size;
		VertexLayout Layout;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void SetData(const void* data, uint32 size) = 0;

		virtual void SetLayout(VertexLayout& layout) = 0;
		virtual VertexLayout& GetLayout() = 0;

		static std::shared_ptr<VertexBuffer> Create(const VertexBufferSpecification& spec, const GraphicsContext& context);
	};
}

