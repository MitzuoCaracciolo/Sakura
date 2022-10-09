#pragma once
#include "Sakura/Core.h"
#include "Sakura/Renderer/RendererContext.h"

#include <memory>

namespace Sakura
{
	struct ConstantBufferSpecification
	{
		void* Data;
		uint32 Size;
		uint32 Slot;
		// Maybe later add a ConstantBuffer Layout
	};

	class ConstantBuffer
	{
	public:
		virtual ~ConstantBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void Update(const void* data, uint32 size, uint32 offset) = 0;

		virtual uint32 GetSlot() const = 0;

		static std::shared_ptr<ConstantBuffer> Create(const ConstantBufferSpecification& spec, std::shared_ptr<RendererContext> context);
	};
}