#pragma once
#include "Sakura/Core.h"
#include "Sakura/Renderer/RendererContext.h"

#include <string>
#include <memory>

namespace Sakura
{
	struct TextureSpecification
	{
		std::string TexturePath;
		uint32 Slot;
		//Later add information about filtering of texture
		//Also could initialize with some premade data 
	};

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual uint32 GetSlot() const = 0;
		virtual uint32 GetWidth() const = 0;
		virtual uint32 GetHeight() const = 0;

		static std::shared_ptr<Texture> Create(const TextureSpecification& spec, RendererContext& context);
	};
}