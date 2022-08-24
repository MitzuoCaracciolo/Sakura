#pragma once

#include "Sakura/Core.h"

#include <memory>

namespace Sakura
{
	struct GraphicsSpecification
	{
		void* WindowHandle;
		uint32 Width;
		uint32 Height;
	};

	class GraphicsContext
	{
	public:
		virtual ~GraphicsContext() = default;

		virtual void ClearBackBuffer(float red, float green, float blue) = 0;
		virtual void SwapBackBuffer() = 0;

		static std::unique_ptr<GraphicsContext> Create(const GraphicsSpecification& spec);
	};
}

