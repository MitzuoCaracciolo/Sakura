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

		virtual VertexLayout& GetLayout() = 0;

		static std::shared_ptr<Shader> Create(const ShaderSpecification& spec, const GraphicsContext& context);
	};
}
