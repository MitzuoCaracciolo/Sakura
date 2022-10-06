#pragma once

#include "Sakura/Core.h"
#include "Sakura/Renderer/VertexLayout.h"
#include "Sakura/Renderer/GraphicsContext.h"

#include <string>
#include <memory>

namespace Sakura
{
	struct ShaderSpecification
	{
		std::string vShaderFilepath;
		std::string pShaderFilepath;
	};

	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual const VertexLayout& GetLayout() const = 0;

		static std::shared_ptr<Shader> Create(const ShaderSpecification& spec, GraphicsContext& context);
	};
}
