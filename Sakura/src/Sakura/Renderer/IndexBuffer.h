#pragma once

#include "Sakura/Core.h"
#include "Sakura/Renderer/GraphicsContext.h"

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

		virtual uint16 GetCount() = 0;

		static std::shared_ptr<IndexBuffer> Create(const IndexBufferSpecification& spec, const GraphicsContext& context);
	};

}