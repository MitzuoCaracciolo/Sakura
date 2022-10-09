#pragma once

#include "Sakura/Core.h"
#include "Sakura/Renderer/RendererContext.h"

namespace Sakura
{
	struct IndexBufferSpecification
	{
		uint16* Data;
		uint16 Count;
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual uint16 GetCount() const = 0;

		static std::shared_ptr<IndexBuffer> Create(const IndexBufferSpecification& spec, std::shared_ptr<RendererContext> context);
	};

}