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

		virtual const VertexLayout& GetLayout() const = 0;
		virtual void SetLayout(VertexLayout& layout) = 0;

		static std::shared_ptr<VertexBuffer> Create(const VertexBufferSpecification& spec, GraphicsContext& context);
	};
}

