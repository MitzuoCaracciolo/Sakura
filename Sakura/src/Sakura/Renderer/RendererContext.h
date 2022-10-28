#pragma once

#include "Sakura/Core.h"

#include <memory>

namespace Sakura
{
	struct RendererContextSpecification
	{
		void* WindowHandle;
		uint32 Width;
		uint32 Height;
	};

	class RendererContext
	{
	public:
		virtual ~RendererContext() = default;

		virtual void ClearBackBuffer(float red, float green, float blue) = 0;
		virtual void SwapBackBuffer() = 0;
		virtual void SetRenderTarget() = 0;
		virtual void SetPrimitiveTopology() = 0;
		virtual void Draw(uint32_t count, uint32_t baseIndex, uint32_t baseVertex) = 0;

		static std::shared_ptr<RendererContext> Create(const RendererContextSpecification& spec);
	};
}

